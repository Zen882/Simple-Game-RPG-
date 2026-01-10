#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>

typedef struct{
	char name[50];
	int maxHealth;
	int damage;
}classes;

typedef struct{
	char name[50];
	int hp;
	int expGained;
	int goldGained;
	int damage;
}monster;

typedef struct{
	char name[50];
	classes _classes;
	int hp;
	int level;
	int exp;
	int gold;
}player;

typedef struct{
	int expRequire;
}levelUpRequire;

int isNew = false;

classes _classes[] = {
	{"Archer", 150, 5},
	{"Warrior", 200, 10},
	{"Wizard", 125, 15}
};

monster m[] = {
	{"Goblin", 100, 60, 15, 10},
	{"Orc", 200, 40, 35, 20},
	{"Dragon", 400, 80, 50, 35}
};

void classPlayer(char input_c[], player *character){
	if(strcmp(input_c, "Archer") == 0){
		character->_classes = _classes[0];
	} else if(strcmp(input_c, "Warrior") == 0){
		character->_classes = _classes[1];
	} else{
		character->_classes = _classes[2];
	}
	
	return;
}

void monsterSelection(int chooseMonster, monster *monsters){
	switch(chooseMonster){
		case 1:
			*monsters = m[0];
			break;
		case 2:
			*monsters = m[1];
			break;
		case 3:
			*monsters = m[2];
			break;
	}
	return;
}

void createCharacter(player *character, levelUpRequire *l){
	char class_player[20];
		printf("Enter Your Name Character: ");
		scanf("%[^\n]", character->name); getchar();
		do {
			printf("Choose Your Classes[1.Archer, 2.Warrior, 3.Wizard]: ");
			scanf("%s", &class_player); getchar();
		}while(strcmp(class_player, "Archer") != 0 && strcmp(class_player, "Warrior") != 0 && strcmp(class_player, "Wizard") != 0);
			classPlayer(class_player, character);
			character->hp = character->_classes.maxHealth;
			character->level = 1;
			character->exp = 0;
			character->gold = 0;
			l->expRequire = 60;
			
		return;
}

void resetCharacter(player *character, levelUpRequire *l){
		character->hp = character->_classes.maxHealth;
		character->level = 1;
		character->exp = 0;
		character->gold = 0;
		l->expRequire = 60;
}

void levelUp(player *character, levelUpRequire *l){
	if(character->exp >= l->expRequire){
		character->hp = character->_classes.maxHealth;
		character->exp = 0;
		character->level++;
		l->expRequire *= 2;
		character->_classes.maxHealth += 50;
		character->hp += 50;
		character->gold += 100;
		character->_classes.damage += 5;
		printf("Congratulation You are Level Up: %d", character->level);
	} else{
		return;
	}
}

bool fight(player *character, monster *monsters, levelUpRequire *l) {
		bool condition = true;
		character->hp -= monsters->damage;
		monsters->hp -= character->_classes.damage;
		if(character->hp <= 0){
			printf("Kamu Lose\n");
			resetCharacter(character, l);
			printf("\n");
			printf("Press any key to continue...");
			getchar();
			condition = false;
		} else if(monsters->hp <= 0){
			character->exp += monsters->expGained;
			character->gold += monsters->goldGained;
			printf("You Won, You Gain %d Exp dan %d Gold\n", monsters->expGained, monsters->goldGained);
			levelUp(character, l);
			printf("\n");
			printf("Press any key to continue...");
			getchar();
			condition = false;
		}
		
		return condition;
}

void fightMonster(player *character, monster *monsters, levelUpRequire *l){
	int chooseFight;
	bool condition;
	do{
		system("cls");
		printf("%s\n", character->name);
		printf("Health: %d\n", character->hp);
		printf("Damage: %d\n", character->_classes.damage);
		printf("\n");
		printf("\n");
		printf("%s\n", monsters->name);
		printf("Health: %d\n", monsters->hp);
		printf("Damage: %d\n", monsters->damage);
		printf("\n");
		printf("1. Fight\n");
		printf("2. Run\n");
		printf(">> ");
		scanf("%d", &chooseFight); getchar();
		switch(chooseFight){
			case 1:
				 condition = fight(character, monsters, l);
				break;
			case 2:
				break;
		}
	}while(chooseFight == 1 && condition == true);
	
	return;
}

void fightMenu(player *character, levelUpRequire *l){
	monster monsters;
	int chooseMonster;
	system("cls");
	printf("1. Goblin\n");
	printf("2. Orc\n");
	printf("3. Dragon\n");
	printf(">> ");
	scanf("%d", &chooseMonster);
	getchar();
	switch (chooseMonster){
		case 1:
			monsterSelection(chooseMonster, &monsters);
			fightMonster(character, &monsters, l);
			break;
		case 2:
			monsterSelection(chooseMonster, &monsters);
			fightMonster(character, &monsters, l);
			break;
		case 3:
			monsterSelection(chooseMonster, &monsters);
			fightMonster(character, &monsters, l);
			break;
	}
}

void buyHealth(player *character){
	if(character->hp >= character->_classes.maxHealth){
		printf("Your Health is Full\n");
		character->hp = character->_classes.maxHealth;
		printf("Press any key to continue...");
		getchar();
	} else if(character->gold < 20){
		printf("Your Money is not Enough\n");
		printf("Press any key to continue...");
		getchar();
	}
	else{
		character->hp += 50;
		character->gold -= 20;
	} 
	
	
	
	return;
}

void saveGame(player *character, levelUpRequire *l){
	FILE *fp;
	fp = fopen("account.txt", "w");
	fprintf(fp, "%s#%s#%d#%d#%d#%d#%d#%d#%d#", 
			character->name,
			character->_classes.name,
			character->exp,
			character->level,
			character->gold,
			character->hp,
			character->_classes.damage,
			character->_classes.maxHealth,
			l->expRequire);
			
	fclose(fp);
	return;
}

void loadAccount(player *character, levelUpRequire *l){
	FILE *fp;
	fp = fopen("account.txt", "r");
	if(fp == NULL){
		isNew = true;
		return;
	} else {
		fscanf(fp, "%[^#]#%[^#]#%d#%d#%d#%d#%d#%d#%d#",
			&character->name,
			&character->_classes.name,
			&character->exp,
			&character->level,
			&character->gold,
			&character->hp,
			&character->_classes.damage,
			&character->_classes.maxHealth,
			&l->expRequire);
			fclose(fp);
	}
}
	
int main(){
	
	player character;
	levelUpRequire level;
	loadAccount(&character, &level);

	int chooseFirstMenu;
	int chooseMainMenu;
	
		printf("1. Start New Game\n");
		if(!isNew) printf("2. Continue Game\n");
		printf("3. Exit\n");
		printf(">> ");
		scanf("%d", &chooseFirstMenu); getchar();
		
		switch(chooseFirstMenu){
			case 1:
				createCharacter(&character, &level);
				break;
			case 2:
				break;
			case 3:
				break;
		}
		
	if(chooseFirstMenu < 3){
		do{
			system("cls");
			printf("Name: %s\n", character.name);
			printf("%s\n", character._classes.name);
			printf("Level: %d\n", character.level);
			printf("Health: %d/%d\n", character.hp, character._classes.maxHealth);
			printf("Exp: %d/%d\n", character.exp, level.expRequire);
			printf("Gold: %d\n", character.gold);
			printf("Damage: %d\n", character._classes.damage);
			printf("1. Fight\n");
			printf("2. Buy Heal\n");
			printf("3. Save Game\n");
			printf("4. Exit\n");
			scanf("%d", &chooseMainMenu); getchar();
				switch(chooseMainMenu){
					case 1:
			       		fightMenu(&character, &level);
						break;
					case 2:
						buyHealth(&character);
						break;
					case 3:
						saveGame(&character, &level);
						printf("Save Successfully...\n");
						printf("Press any key to continue...");
						getchar();
						break;
					case 4:
						break;
				}
			
			} while(chooseMainMenu != 4);
			
	} else{
		
	}
	
	
	return 0;
}
