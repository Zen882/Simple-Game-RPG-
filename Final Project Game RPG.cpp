#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>

bool isNew = false;

typedef struct{
	int numberList;
	char name[50];
	int level;
	int damage;
	int upgradeDamage;
	int price;
	float cooldown;
	bool isCooldown;
}skills;

typedef struct{
	int numberList;
	char name[50];
	int damage;
	int price;
}weapons;

typedef struct{
	int numberList;
	weapons weapon;
	bool isEquip;
}inventory;

typedef struct{
	char name[50];
	int maxHealth;
	int damage;
	skills *skill;
	weapons *weapon;
	int skillCount;
	int weaponCount;
}classes;

typedef struct{
	char name[50];
	classes _classes;
	int level;
	int hp;
	int exp;
	int gold;
	int expRequire;
	inventory invent[10];
	int inventoryCount;
	skills playerSkill[3];
	int playerSkillCount;
}player;

typedef struct{
	char name[50];
	int maxHealth;
	int expGained;
	int goldGained;
	int damage;
	int hpGrowth;
	int damageGrowth;
}monsters;

skills skill_archer[] = {
	{1, "Fire Arrow", 1, 25, 20, 100, 3.5, false},
	{2, "Focus Attack", 1, 30, 20, 150, 5.5, false},
	{3, "Piercing Attack", 1, 35, 20, 200, 7.5, false}
};

skills skill_warrior[] = {
	{1, "Divine Slash", 1, 25, 20, 100, 3.5, false},
	{2, "Helix", 1, 30, 20, 150, 5.5, false},
	{3, "Cut End", 1, 35, 20, 200, 7.5, false}
};

skills skill_wizard[] = {
	{1, "Fireball", 1, 25, 20, 100, 3.5, false},
	{2, "Lightning Bolt", 1, 30, 20, 150, 5.5, false},
	{3, "Meteorite", 1, 35, 20, 200, 7.5, false}
};

weapons weapon_archer[] = {
	{1, "Iron Bow", 30, 100},
	{2, "Silver Bow", 50, 250},
	{3, "Golden Bow", 100, 400},
	{4, "Glass Bow", 125, 500},
	{5, "Ebony Bow", 150, 800}
};

weapons weapon_warrior[] = {
	{1, "Iron Axe", 30, 100},
	{2, "Silver Axe", 50, 250},
	{3, "Golden Axe", 100, 400},
	{4, "Glass Axe", 125, 500},
	{5, "Ebony Axe", 150, 700},
	{6, "Iron Sword", 35, 110},
	{7, "Silver Sword", 55, 270},
	{8, "Golden Sword", 110, 420},
	{9, "Glass Sword", 130, 600},
	{10, "Ebony Sword", 160, 800},
	{11, "Iron Dagger", 25, 70},
	{12, "Silver Dagger", 40, 100},
	{13, "Golden Dagger", 80, 300},
	{14, "Glass Dagger", 115, 400},
	{15, "Ebony Dagger", 125, 500}
};

weapons weapon_wizard[] = {
	{1, "Fireball Staff", 30, 100},
	{2, "Ice Spike Staff", 50, 250},
	{3, "Lightning Bolt Staff", 100, 400},
	{4, "Summon Flame Monster Staff", 0, 250},
	{5, "Summon Ice Monster Staff", 0, 350},
	{6, "Summon Lightning Monster Staff", 0, 500},
	{7, "Invicible Staff", 0, 250},
	{8, "Flame Storm Staff", 400, 1000},
	{9, "Blizzard Staff", 400, 1000},
	{10, "Lightning Storm Staff", 400, 1000}
};

classes _classes[] = {
	{"Archer", 150, 5, skill_archer, weapon_archer, sizeof(skill_archer) / sizeof(skills) , sizeof(weapon_archer) / sizeof(weapons)},
	{"Warrior", 200, 10, skill_warrior, weapon_warrior, sizeof(skill_archer) / sizeof(skills), sizeof(weapon_warrior) / sizeof(weapons)},
	{"Wizard", 125, 15, skill_wizard, weapon_wizard, sizeof(skill_wizard) / sizeof(skills) ,sizeof(weapon_wizard) / sizeof(weapons)}
};

monsters m[] = {
	{"Goblin", 100, 60, 15, 10, 0, 0},
	{"Orc", 200, 40, 35, 20, 0, 0},
	{"Dragon", 400, 80, 50, 35, 0, 0}
};

void classPlayer(char input_c[], player *character){
	if(strcmp(input_c, "Archer") == 0){
		character->_classes = _classes[0];
		for(int i = 0; i < character->_classes.skillCount; i++){
			character->playerSkill[i] = character->_classes.skill[i];
		}
	} else if(strcmp(input_c, "Warrior") == 0){
		character->_classes = _classes[1];
		for(int i = 0; i < character->_classes.skillCount; i++){
			character->playerSkill[i] = character->_classes.skill[i];
		}
	} else{
		character->_classes = _classes[2];
		for(int i = 0; i < character->_classes.skillCount; i++){
			character->playerSkill[i] = character->_classes.skill[i];
		}
	}
	return;
}

void createCharacter(player *character){
		char inputClass[20];
		printf("Enter Your Name Character: ");
		scanf("%[^\n]", character->name); getchar();
		do {
			printf("Choose Your Classes[Archer, Warrior, Wizard]: ");
			scanf("%19s", inputClass); getchar();
			if(strcmp(inputClass, "Archer") != 0 && strcmp(inputClass, "Warrior") != 0 && strcmp(inputClass, "Wizard") != 0){
				printf("Please enter the exact same text as this [Archer, Warrior, Wizard]\n");
				printf("Press any key to continue...");
				getchar();
			}
		}while(strcmp(inputClass, "Archer") != 0 && strcmp(inputClass, "Warrior") != 0 && strcmp(inputClass, "Wizard") != 0);
			classPlayer(inputClass, character);
			character->hp = character->_classes.maxHealth;
			character->level = 1;
			character->exp = 0;
			character->gold = 10000;
			character->expRequire = 60;
			character->playerSkillCount = sizeof(character->playerSkill) / sizeof(character->playerSkill[0]);
		return;
}

void monsterSelection(int chooseMonster, monsters *monster){
	switch(chooseMonster){
		case 1:
			*monster = m[0];
			break;
		case 2:
			*monster = m[1];
			break;
		case 3:
			*monster = m[2];
			break;
	}
	return;
}

void resetCharacter(player *character){
	for(int i = 0; i < sizeof(m) / sizeof(m[0]); i++){
		m[i].hpGrowth = 0;
		m[i].damageGrowth = 0;
	}
		classPlayer(character->_classes.name, character);
		character->hp = character->_classes.maxHealth;
		character->level = 1;
		character->exp = 0;
		character->gold = 0;
		character->expRequire = 60;
	
}

void playerLevelUp(player *character){
		character->hp = character->_classes.maxHealth;
		character->exp = 0;
		character->level++;
		character->expRequire *= 2;
		character->_classes.maxHealth += 50;
		character->hp += 50;
		character->gold += 100;
		character->_classes.damage += 5;
		return;
}

void monsterLevelUp(){
	for(int i = 0; i < sizeof(m) / sizeof(m[0]); i++){
		m[i].hpGrowth += 50;
		m[i].damageGrowth += 10;
	}		
}

void levelUp(player *character){
	if(character->exp >= character->expRequire){
		playerLevelUp(character);
		monsterLevelUp();
		printf("Congratulation You are Level Up: %d", character->level);
	} else{
		return;
	}
}

void damageFight(player *character, monsters *monster){
		character->hp -= monster->damage;
		monster->maxHealth -= character->_classes.damage;
}

void isEndFight(player *character, monsters *monster, bool *condition) {
		if(character->hp <= 0){
			printf("You Lose\n");
			resetCharacter(character);
			printf("\n");
			printf("Press any key to continue...");
			getchar();
			*condition = false;
		} else if(monster->maxHealth <= 0){
			character->exp += monster->expGained;
			character->gold += monster->goldGained;
			printf("You Won, You Gain %d Exp dan %d Gold\n", monster->expGained, monster->goldGained);
			levelUp(character);
			printf("\n");
			printf("Press any key to continue...");
			getchar();
			*condition = false;
		}else {
			
		}
		
		return;
}

void skillCooldown(player *character, monsters *monster, int i, float cooldown[]){
	if(character->playerSkill[i].isCooldown){
			printf("Skill is Cooldown\n");
			printf("Press any key to continue...");
			getchar();
		}else{
			monster->maxHealth -= character->playerSkill[i].damage;
			character->playerSkill[i].isCooldown = true;
	}
}

void cooldownDecreased(player *character, float cooldown[]){
	for (int i = 0; i < character->playerSkillCount; i++){
		if(character->playerSkill[i].isCooldown){
			cooldown[i] -= 1;
			if(cooldown[i] <= 0){
				cooldown[i] = character->playerSkill[i].cooldown;
				character->playerSkill[i].isCooldown = false;
			}
		}else{
			
		}
	}
}

void resetCooldown(player *character){
	for(int i = 0; i < character->playerSkillCount; i++){
		character->playerSkill[i].isCooldown = false;
	}
}

void fightMonster(player *character, monsters *monster){
	int chooseFight;
	bool condition = true;
	int i;
	float cooldown[3] = {character->playerSkill[0].cooldown, character->playerSkill[1].cooldown, character->playerSkill[2].cooldown};
	do{
		system("cls");
		printf("%s\n", character->name);
		printf("Health: %d\n", character->hp);
		printf("Damage: %d\n", character->_classes.damage);
		printf("\n");
		printf("\n");
		printf("%s\n", monster->name);
		printf("Health: %d\n", monster->maxHealth);
		printf("Damage: %d\n", monster->damage);
		printf("\n");
		printf("1. Fight\n");
		(character->playerSkill[0].isCooldown) ? printf("2. %s | Cooldown: %.1f Second\n", character->playerSkill[0].name, cooldown[0]) : printf("2. %s\n", character->playerSkill[0].name);
		(character->playerSkill[1].isCooldown) ? printf("3. %s | Cooldown: %.1f Second\n", character->playerSkill[1].name, cooldown[1]) : printf("3. %s\n", character->playerSkill[1].name);
		(character->playerSkill[2].isCooldown) ? printf("4. %s | Cooldown: %.1f Second\n", character->playerSkill[2].name, cooldown[2]) : printf("4. %s\n", character->playerSkill[2].name);
		printf("5. Run\n");
		printf(">> ");
		scanf("%d", &chooseFight); getchar();
		switch(chooseFight){
			case 1:
				damageFight(character, monster);
				cooldownDecreased(character, cooldown);
				isEndFight(character, monster, &condition);
				break;
			case 2:
				skillCooldown(character, monster, 0, cooldown);
				isEndFight(character, monster, &condition);
				break;
			case 3:
				skillCooldown(character, monster, 1, cooldown);
				isEndFight(character, monster, &condition);
				break;
			case 4:
				skillCooldown(character, monster, 2, cooldown);
				isEndFight(character, monster, &condition);
				break;
			case 5:
				break;
		}
		
		if(chooseFight < 0 || chooseFight > 5){
			printf("Input Number on The List\n");
			printf("Press any key to continue...");
			getchar(); 
		}
	}while(chooseFight > 0 && chooseFight < 5 && condition || chooseFight < 0 || chooseFight > 5);
	resetCooldown(character);
	return;
}

void fightMenu(player *character){
	monsters monster;
	int chooseMonster;
	do{
	system("cls");
	printf("1. Goblin\n");
	printf("2. Orc\n");
	printf("3. Dragon\n");
	printf(">> ");
	scanf("%d", &chooseMonster);
	getchar();
	switch (chooseMonster){
		case 1:
			monsterSelection(chooseMonster, &monster);
			if(character->level > 1){
				monster.maxHealth += monster.hpGrowth;
				monster.damage += monster.damageGrowth;
			}
			fightMonster(character, &monster);
			break;
		case 2:
			monsterSelection(chooseMonster, &monster);
			if(character->level > 1){
				monster.maxHealth += monster.hpGrowth;
				monster.damage += monster.damageGrowth;
			}
			fightMonster(character, &monster);
			break;
		case 3:
			monsterSelection(chooseMonster, &monster);
			if(character->level > 1){
				monster.maxHealth += monster.hpGrowth;
				monster.damage += monster.damageGrowth;;
			}
			fightMonster(character, &monster);
			break;
		}
		
		if(chooseMonster < 0 || chooseMonster > 3){
			printf("Input Number on The List\n");
			printf("Press any key to continue...");
			getchar(); 
		}
	}while(chooseMonster < 0 || chooseMonster > 3);
	
}

void buyHealth(player *character){
	character->hp += 50;
	character->gold -= 25;
	if(character->hp > character->_classes.maxHealth){
		character->hp = character->_classes.maxHealth;
	}
	return;
}

void upgrade(player *character, int j){
	if(character->playerSkill[j].level < 5 && character->gold >= character->playerSkill[j].price){
	character->gold -= character->playerSkill[j].price;
	character->playerSkill[j].damage += character->playerSkill[j].upgradeDamage;
	character->playerSkill[j].level++;
	character->playerSkill[j].cooldown -= 0.5;
	character->playerSkill[j].price += 100;
	character->playerSkill[j].upgradeDamage += 50;
	printf("You Upgrade %s\n", character->playerSkill[j].name);
	printf("Press any key to continue...\n");
	getchar();
	
	}else if(character->gold < character->playerSkill[j].price){
		printf("Your Money is Not Enough\n");
		printf("Press any key to continue...\n");
		getchar();
	}
	 else{
		printf("Your Level is Maximum\n");
		printf("Press any key to continue...\n");
		getchar();
	}
	return;
}

void upgradeSkill(player *character){
	int selectSkill;
	int selectUpgrade;
	
	do{
		system("cls");
		for (int i = 0; i < character->playerSkillCount; i++){
			skills s = character->playerSkill[i];
			printf("%d. %s | Level: %d | Damage: %d | Price: %d | Cooldown: %.1f Second\n",
				s.numberList,
				s.name,
				s.level,
				s.damage,
				s.price,
				s.cooldown
		);
	}
	
	printf("0. Back\n");
	printf(">> ");
	scanf("%d", &selectSkill); getchar();
	for(int j = 0; j < character->playerSkillCount; j++){
		if(selectSkill == character->playerSkill[j].numberList){
			printf("%s\n", character->playerSkill[j].name);
			printf("1. Upgrade\n");
			printf("2. Back\n");
			scanf("%d", &selectUpgrade); getchar();
			switch(selectUpgrade){
				case 1:
					upgrade(character, j);
					break;
				case 2:
					break;
				}
			}
		}
		
		if(selectSkill < 0 || selectSkill >= character->playerSkillCount){
			printf("Input Number on The List\n");
			printf("Press any key to continue...");
			getchar(); 
		} 
	}while(selectSkill >= 1 && selectSkill <= character->playerSkillCount || selectSkill < 0 || selectSkill >= character->playerSkillCount);
	return;
}

void checkWeapon(player *character, int i, bool *condition){
	for(int j = 0; j <= character->inventoryCount; j++){
		if(strcmp(character->_classes.weapon[i].name, character->invent[j].weapon.name) == 0){
				printf("You Already Buy This Weapon\n");
				printf("Press any key to continue...\n");
				getchar();
				*condition = true;
		}		
	}
}

void addWeapon(player *character, int i){
		character->gold -= character->_classes.weapon[i].price;
		character->invent[character->inventoryCount].weapon = character->_classes.weapon[i];
		character->invent[character->inventoryCount].isEquip = false;
		character->inventoryCount += 1;
		printf("You Buy %s\n", character->_classes.weapon[i].name);
		printf("Press any key to continue...\n");
		getchar();
}

void weaponShop(player *character){
	int select;
	bool condition;
	do{
		system("cls");
		condition = false;
		int high = character->_classes.weaponCount - 1;
		int low = 0;
		printf("=== Weapon Shop ===\n");
	for(int i = 0; i < character->_classes.weaponCount; i++){
		weapons w = character->_classes.weapon[i];
		printf("%d. %s | Damage: %d | Price: %d\n",
			w.numberList,
			w.name,
			w.damage,
			w.price
		);	
	}
		printf("0. Back\n\n");	
		printf("Enter Number to Buy a Weapons : ");
		scanf("%d", &select); getchar();
		while(low <= high){
			int mid = (low+high)/2;
			if(select == character->_classes.weapon[mid].numberList && character->gold >= character->_classes.weapon[mid].price
				 && character->inventoryCount < 10){
				 	checkWeapon(character, mid, &condition);
					if(condition == false){
						addWeapon(character, mid);
					} 
					break;	
			}else if(select < character->_classes.weapon[mid].numberList){
				high = mid-1;
			}else if(select > character->_classes.weapon[mid].numberList){
				low = mid+1;
			}else if(character->gold < character->_classes.weapon[mid].price){
				printf("You Don't Have Enough Gold\n");
				printf("Press any key to continue...\n");
				getchar();
				condition = true;
			} else if(character->inventoryCount >= 10){
				printf("Your Inventrory is Full\n");
				printf("Press any key to continue...\n");
				getchar();
			} else{
				
			}
				
		}
		
			if(select > character->_classes.weaponCount || select < 0){
				printf("Please Enter the number on the List\n");
				printf("Press any key to continue...\n");
				getchar();
			}
			
			
	}while(select > character->_classes.weaponCount || select < 0 || condition);
	
	return;
}

void equipWeapon(player *character, int j){
		character->_classes.damage += character->invent[j].weapon.damage;
		character->invent[j].isEquip = true;
		return;
}

void unequipWeapon(player *character, int j){
		character->_classes.damage -= character->invent[j].weapon.damage;
		character->invent[j].isEquip = false;
		return;
}

void sell(player *character, int j){
	if(character->invent[j].isEquip == true){
		character->_classes.damage -= character->invent[j].weapon.damage;
		character->gold += character->invent[j].weapon.price;
		character->invent[j].isEquip = false;
		for (int i = j; i <= character->inventoryCount - 1; i++){
			character->invent[i].weapon = character->invent[i + 1].weapon;
		}
		character->inventoryCount--;
	} else {
		character->gold += character->invent[j].weapon.price;
		for (int i = j; i <= character->inventoryCount - 1; i++){
			character->invent[i].weapon = character->invent[i + 1].weapon;
			
		}
		character->inventoryCount--;
		
	}
	return;
}

void inventoryCharacter(player *character){
	int chooseWeapon;
	int selectOption;
	int number = 1;
	char equip[20];
	system("cls");
	printf("=====Invetory=====\n");
	if(character->inventoryCount <= 0){
		printf("There is no Weapon in the Inventory\n");
		printf("Press any key to continue...");
		getchar();
	} else{
		for(int i = 0; i < character->inventoryCount; i++){
		character->invent[i].numberList = number;
		printf("%d. %s | Damage %d | Price %d\n", character->invent[i].numberList, character->invent[i].weapon.name, character->invent[i].weapon.damage, character->invent[i].weapon.price);
		number++;
	}
	printf("0. Back\n\n");
	printf("Select Weapon to Equip or Sell: ");
	scanf("%d", &chooseWeapon);
	system("cls");
	for(int j = 0; j < character->inventoryCount; j++){
		if(chooseWeapon == character->invent[j].numberList){
			if(character->invent[j].isEquip == false){
				strcpy(equip, "Equip");
			} else {
				strcpy(equip, "Unequip");
			}
			printf("Do You Want To Equip %s or Sell\n", character->invent[j].weapon.name);
			printf("1. %s\n", equip);
			printf("2. Sell\n");
			scanf("%d", &selectOption); getchar();
			switch(selectOption){
				case 1:
					for(int i = 0; i < character->inventoryCount; i++){
						if(character->invent[i].isEquip == true && character->invent[j].isEquip == false){
							unequipWeapon(character, i);
						}
					}
					if(character->invent[j].isEquip == false){
							equipWeapon(character, j);
						} else{
							unequipWeapon(character, j);
						}	
					
					break;
				case 2:
					sell(character, j);
					break;
				}		
			}
		}
	}
	return;
}

void saveGame(player *character){
	FILE *fp;
	fp = fopen("account.dat", "wb");
	fwrite(&character, sizeof(player), 1, fp);
	fwrite(m, sizeof(monsters), sizeof(m) / sizeof(m[0]), fp);
	fclose(fp);
	return;
}

void loadAccount(player *character){
	FILE *fp;
	fp = fopen("account.dat", "rb");
	if(fp == NULL){
		isNew = true;
		return;
	} else {
			fread(&character, sizeof(player), 1, fp);
			fread(m, sizeof(monsters), sizeof(m) / sizeof(m[0]), fp);
			fclose(fp);
	}
}

int main(){
	player character;
	int chooseFirstMenu;
	int chooseMainMenu;
	int number = 2;
	loadAccount(&character);
	do{
		system("cls");
		printf("1. Start New Game\n");
			if(!isNew){
			printf("2. Continue Game\n");
			number += 1;
		} 
		printf("%d. Exit\n", number);
		printf(">> ");
		scanf("%d", &chooseFirstMenu); getchar();
		if(chooseFirstMenu == 1){
			createCharacter(&character);
		} else if(chooseFirstMenu < 1 || chooseFirstMenu > 2){
			printf("Input Number on The List\n");
			printf("Press any key to continue...");
			getchar(); 
		}else{
			
		}
			
	}while(chooseFirstMenu < 1 || chooseFirstMenu > 2);
	
	if(chooseFirstMenu != number){
		do{
			system("cls");
			printf("Name: %s\n", character.name);
			printf("%s\n", character._classes.name);
			printf("Level: %d\n", character.level);
			printf("Health: %d/%d\n", character.hp, character._classes.maxHealth);
			printf("Exp: %d/%d\n", character.exp, character.expRequire);
			printf("Gold: %d\n", character.gold);
			printf("Damage: %d\n", character._classes.damage);
			printf("1. Fight\n");
			printf("2. Buy Health Potion\n");
			printf("3. Skill\n");
			printf("4. Weapon Shop\n");
			printf("5. Inventory\n");
			printf("6. Save Game\n");
			printf("7. Exit\n");
			printf(">> ");
			scanf("%d", &chooseMainMenu); getchar();
				switch(chooseMainMenu){
					case 1:
			       		fightMenu(&character);
						break;
					case 2:
						if (character.hp == character._classes.maxHealth){
							printf("Your HP is Full\n");
							printf("Press any key to continue...");
							getchar();
						} else{
							buyHealth(&character);
						}	
						break;
					case 3:
						upgradeSkill(&character);
						break;
					case 4:
						weaponShop(&character);
						break;
					case 5:
						inventoryCharacter(&character);
						break;
					case 6:
						saveGame(&character);
						printf("Save Successfully...\n");
						printf("Press any key to continue...");
						getchar();
						break;
					case 7:
						break;
				}
			
			} while(chooseMainMenu != 7);
			
	} else{
		
	}
	
	return 0;
}
