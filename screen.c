#include "screen.h"

void printTitleScreen(){
	printf("\n\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);
	printf("\n  ▮"); printSymbols(BARS_WIDTH - 2, SPACE_SYMBOL); printf("▮");
	printf("\n  ▮          ELDEN   ROGUE"); printSymbols(BARS_WIDTH - 2 - (int)strlen("          ELDEN   ROGUE"), SPACE_SYMBOL); printf("▮");
	printf("\n  ▮"); printSymbols(BARS_WIDTH - 2, SPACE_SYMBOL); printf("▮");
	printf("\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);

	printf("\n\t1. START");
	printf("\n\t2. CONTINUE");
	printf("\n\t0. EXIT");
}


void printCharCreationScreen(const string25 strName, const int nLevel, const string25 strClass){
	printf("\n\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);
	printHeader("CHARACTER CREATOR");
	printf("\n  ▮ Name: "); printf("%s", strName); printSymbols(PLAYER_NAME_MAX_CHARS - (int)strlen(strName), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮ Level: "); printf("%d", nLevel); printSymbols(3- calcDigits(nLevel), SPACE_SYMBOL); printf("  Class: ");  printf("%s", strClass); printSymbols(13 - (int)strlen(strClass), SPACE_SYMBOL); printf("▮");
	printf("\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);

	printf("\n\t1. ENTER NAME");
	printf("\n\t2. SELECT CLASS");
	printf("\n\t3. CONFIRM CHARACTER");
	printf("\n\t0. CANCEL");
}

void printJobSelectorScreen(const JobClass sJob){
	printf("\n\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);
	printHeader("JOB CLASS SELECTOR");
	printf("\n  ▮    Job Class : %s", sJob.strJob);			   printSymbols(BARS_WIDTH - 19 - (int)strlen(sJob.strJob), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮        Level : %d", sJob.nLevel); 		   printSymbols(BARS_WIDTH - 19 - calcDigits(sJob.nLevel), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮       Health : %d", sJob.nHealth);	       printSymbols(BARS_WIDTH - 19 - calcDigits(sJob.nHealth), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮    Endurance : %d", sJob.nEndurance);    printSymbols(BARS_WIDTH - 19 - calcDigits(sJob.nEndurance), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮    Dexterity : %d", sJob.nDexterity);    printSymbols(BARS_WIDTH - 19 - calcDigits(sJob.nDexterity), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮     Strength : %d", sJob.nStrength);	   printSymbols(BARS_WIDTH - 19 - calcDigits(sJob.nStrength), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮ Intelligence : %d", sJob.nIntelligence); printSymbols(BARS_WIDTH - 19 - calcDigits(sJob.nIntelligence), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮        Faith : %d", sJob.nFaith);		   printSymbols(BARS_WIDTH - 19 - calcDigits(sJob.nFaith), SPACE_SYMBOL); printf(" ▮");
	printf("\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);

	printf("\nSELECT JOB CLASS: ");
	printf("\n\t1. VAGABDOND");
	printf("\n\t2. SAMURAI");
	printf("\n\t3. WARRIOR");
	printf("\n\t4. HERO");
	printf("\n\t5. ASTROLOGER");
	printf("\n\t6. PROPHET");
	printf("\n\t0. CONFIRM CLASS");
}

int calcDigits(int nNum){
	if (nNum == 0){
		return 1;
	}

	int nDigit = 0;
	while (nNum > 0){
		nNum /= 10;
		nDigit++;
	}
	return nDigit;
}

void printSymbols(const int nAmount, const int nSymbol){
	int i;
	for (i = 0; i < nAmount; i++){
		switch(nSymbol){
		case BAR_SYMBOL: 
			printf("▮");
			break;
		case SPACE_SYMBOL: 
			printf(" ");
			break;
		default:
			printf("");
		}
	}
}



void printRoundTableScreen(const Player sPlayer){
	printf("\n\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);
	printHeader("ROUNDTABLE HOLD");
	printf("\n  ▮ Name: %s", sPlayer.strPlayerName); printSymbols(BARS_WIDTH - (int)strlen(sPlayer.strPlayerName) - 4 - 6, SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮ Level: %d", sPlayer.sJob.nLevel); printSymbols(7 - calcDigits(sPlayer.sJob.nLevel), SPACE_SYMBOL); 
		printf("Class: %s", sPlayer.sJob.strJob);	 printSymbols(BARS_WIDTH - 25 - (int)strlen(sPlayer.sJob.strJob), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮ Runes: %d", sPlayer.nRunes); printSymbols(7 - calcDigits(sPlayer.nRunes), SPACE_SYMBOL);
		printf("Shards: "); printShards(sPlayer.aShards); /*printSymbols(sPlayer.nShards, SHARD_SYMBOL); printSymbols(MAX_SHARDS - sPlayer.nShards, EMPTY_SHARD_SYMBOL); */printSymbols(3, SPACE_SYMBOL); printf(" ▮");
	printf("\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);

	printf("\n\nSELECT ACTION:");
	printf("\n\t1. FAST TRAVEL");
	printf("\n\t2. LEVEL UP");
	printf("\n\t3. INVENTORY");
	printf("\n\t4. SHOP");
	printf("\n\t5. SAVE");
	printf("\n\t0. QUIT TO TITLE");
}


	void printShards(const int aShards[MAX_SHARDS]){
		int i;
		for (i = 0; i < MAX_SHARDS; i++){
			if (aShards[i] != 0)	//Active
				printf("▲");
			else{
				printf("△");
			}
		}
	}


void printLevelingScreen(const Player sPlayer, const int nRuneCost){
	printf("\n\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);
	printHeader("LEVEL UP");
	printf("\n  ▮ Level: %d", sPlayer.sJob.nLevel); printSymbols(BARS_WIDTH - (int)strlen("▮ Level: ") - calcDigits(sPlayer.sJob.nLevel), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮ Runes: %d", sPlayer.nRunes); printSymbols(7 - calcDigits(sPlayer.nRunes), SPACE_SYMBOL); 
		if(checkLevelUp(10, nRuneCost, sPlayer.nRunes) == INVALID){printf("\033[0;31m");} printf(" Rune Cost: %d", nRuneCost); printf("\033[0m"); printSymbols(5 - calcDigits(nRuneCost), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮       Health : %d", sPlayer.sJob.nHealth);	       printSymbols(BARS_WIDTH - (int)strlen("▮       Health : ") - calcDigits(sPlayer.sJob.nHealth), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮    Endurance : %d", sPlayer.sJob.nEndurance);    printSymbols(BARS_WIDTH - (int)strlen("▮    Endurance : ") - calcDigits(sPlayer.sJob.nEndurance), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮    Dexterity : %d", sPlayer.sJob.nDexterity);    printSymbols(BARS_WIDTH - (int)strlen("▮    Dexterity : ") - calcDigits(sPlayer.sJob.nDexterity), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮     Strength : %d", sPlayer.sJob.nStrength);	   printSymbols(BARS_WIDTH - (int)strlen("▮     Strength : ") - calcDigits(sPlayer.sJob.nStrength), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮ Intelligence : %d", sPlayer.sJob.nIntelligence); printSymbols(BARS_WIDTH - (int)strlen("▮ Intelligence : ") - calcDigits(sPlayer.sJob.nIntelligence), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮        Faith : %d", sPlayer.sJob.nFaith);		   printSymbols(BARS_WIDTH - (int)strlen("▮        Faith : ") - calcDigits(sPlayer.sJob.nFaith), SPACE_SYMBOL); printf(" ▮");
	printf("\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);
	

	printf("\n\nSELECT ACTION:");
	printf("\n\t1. LEVEL HEALTH");
	printf("\n\t2. LEVEL ENDURANCE");
	printf("\n\t3. LEVEL DEXTERITY");
	printf("\n\t4. LEVEL STRENGTH");
	printf("\n\t5. LEVEL INTELLIGENCE");
	printf("\n\t6. LEVEL FAITH");
	printf("\n\t0. RETURN TO ROUNDTABLE HOLD");
}



void printInventoryScreen(const Weapon aWeapons[], const int nPage, const int nDex, const char strEquipped[]){
	printf("\n\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);
	printHeader("INVENTORY");
	printf("\n  ▮ EQUIPPED: %s", strEquipped); printSymbols(BARS_WIDTH - (int)strlen("▮ EQUIPPED: ") - (int)strlen(strEquipped), SPACE_SYMBOL); printf(" ▮");
	printf("\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);

	displayWeapons(aWeapons);

	printf(UWHITE); printf("\nPAGE %d EQUIPMENT: ", nPage);	printSymbols(15, SPACE_SYMBOL); printf("DEX REQ");
	printf(COLOR_RESET);
	int i;
	for (i = 0; i < 4; i++){
		if(nDex < aWeapons[i].nDexCost){ printf(RED);}
		printf("\n\t%d. %s ", i + 1, aWeapons[i].strWeaponName);	
		printSymbols(25 - (int)strlen(aWeapons[i].strWeaponName), SPACE_SYMBOL);	
		printf("%d", aWeapons[i].nDexCost);
		printf(COLOR_RESET);
	} 
	printf("\n\t5. UNEQUIP WEAPON");
	printf("\n6. PREV PAGE");
	printf("\n7. NEXT PAGE");
	printf("\n0. RETURN TO ROUNDTABLE HOLD");
}

void printShopOpening(const string25 strName, const int nRunes){
	printf("\n\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);
	printf("\n  ▮ "); printf(UWHITE); printf("SHOP MENU"); printf(COLOR_RESET); printSymbols(BARS_WIDTH - (int)strlen("▮ SHOP MENU"), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮ Hello, %s", strName); printSymbols(BARS_WIDTH - (int)strlen("▮ Hello,") - strlen(strName), SPACE_SYMBOL); printf("▮");
	printf("\n  ▮ Runes: %d", nRunes); printSymbols(BARS_WIDTH - (int)strlen("▮ Runes: ") - calcDigits(nRunes), SPACE_SYMBOL); printf(" ▮");
	printf("\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);
	
	printf("\n\nSELECT ACTION:");
	printf("\n\t1. BUY WEAPONS");
	printf("\n\t2. SELL WEAPONS");
	printf("\n\t0. RETURN TO ROUNDTABLE HOLD");
}
	
	void printShopBuyScreen(const int nRunes){
		stringMax strDialogue;
		strcpy(strDialogue, CONFIG_ShopDialogue[generateRNG(0, (sizeof(CONFIG_ShopDialogue) / sizeof(string25)) - 1)]);

		printf("\n\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);
		printHeader("BUY WEAPONS");
		printf("\n  ▮ Runes: %d", nRunes); printSymbols(BARS_WIDTH - (int)strlen("▮ Runes: ") - calcDigits(nRunes), SPACE_SYMBOL); printf(" ▮");
		printf("\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);
		printf(BLUE); printf("\n[SHOPKEEPER]: %s", strDialogue); printf(COLOR_RESET);
		
		printf("\n\nWHA'CHA BUYING?");
		printf("\n\t1. BUY SWORDS");
		printf("\n\t2. BUY KATANAS");
		printf("\n\t3. BUY WHIPS");
		printf("\n\t4. BUY GREATSWORDS");
		printf("\n\t5. BUY STAVES");
		printf("\n\t6. BUY SEALS");
		printf("\n\t0. RETURN");
	}

		void printShopBuyWeapons(const Weapon aWeapons[], const int nWeaponType, const int nRunes){
			displayWeapons(aWeapons);

			printf(UWHITE);
			printf("\n   %s", CONFIG_WeaponTypes[nWeaponType-1]);
			printSymbols(26 - (int)strlen(CONFIG_WeaponTypes[nWeaponType-1]), SPACE_SYMBOL);
			printf("RUNE COST   DEX REQ");
			printf(COLOR_RESET);


			int i;			
			for (i = 0; i < TOTAL_WEAPONS_TYPES_CHOICES; i++){
				if(nRunes < aWeapons[i].nRuneCost){ printf(RED);}
				printf("\n%d. %s ", i + 1, aWeapons[i].strWeaponName);	
				printSymbols(25 - (int)strlen(aWeapons[i].strWeaponName), SPACE_SYMBOL);	
				printf("%d", aWeapons[i].nRuneCost);
				printSymbols(12 - calcDigits(aWeapons[i].nRuneCost), SPACE_SYMBOL);
				printf("%d", aWeapons[i].nDexCost);
			}
			printf(COLOR_RESET);
			printf("\n0. CHECK OTHER WEAPONS");
		}

	void displayWeapons(const Weapon aWeapons[]){
						//4 weapons //3 lines each
		int nLines = 2;
		char strStore[4][nLines][WEAPON_ICON_WIDTH+1];

		int i, j;
		for (i = 0; i < 4; i++){
			int nNameLen = (int)strlen(aWeapons[i].strWeaponName);
			for (j = 0; j < nLines; j++){
				strncpy(strStore[i][j], aWeapons[i].strWeaponName + (WEAPON_ICON_WIDTH * j), WEAPON_ICON_WIDTH);
				
				if(strStore[i][j][0] == ' '){ strcpy(strStore[i][j], strStore[i][j] + 1);  }
				if(j * WEAPON_ICON_WIDTH > nNameLen) {strcpy(strStore[i][j], "        "); }

				fillText(strStore[i][j], WEAPON_ICON_WIDTH);
				strStore[i][j][WEAPON_ICON_WIDTH] = '\0';
			}
		}
		

		printf("\n\n"); printSymbols(WEAPON_ICON_WIDTH*4+5, BAR_SYMBOL);
		printf("\n▮"); printf("1"); printSymbols(WEAPON_ICON_WIDTH-1, SPACE_SYMBOL); printf("▮");
						printf("2"); printSymbols(WEAPON_ICON_WIDTH-1, SPACE_SYMBOL); printf("▮");
						printf("3"); printSymbols(WEAPON_ICON_WIDTH-1, SPACE_SYMBOL); printf("▮");
						printf("4"); printSymbols(WEAPON_ICON_WIDTH-1, SPACE_SYMBOL); printf("▮");
		for (j = 0; j < nLines; j++){
			printf("\n▮%s▮%s▮%s▮%s▮", strStore[0][j], strStore[1][j], strStore[2][j], strStore[3][j]);
		}

		printf("\n"); printSymbols(WEAPON_ICON_WIDTH*4+5, BAR_SYMBOL);
		printf("\n");
		string10 strWords[NUMBER_OF_STATS] = { " HP", "END", "DEX", "STR", "INT", "FTH" };

		for (i = 0; i < NUMBER_OF_STATS; i++){
			for (j = 0; j < 4; j++){
				 printStatLine(aWeapons[j].aStats[i], strWords[i]);
			} printf("▮\n");
		}

		printSymbols(WEAPON_ICON_WIDTH*4+5, BAR_SYMBOL);
	}

void fillText(char strText[], const int nSize){
	while((int)strlen(strText) < nSize){
		strcat(strText, " ");
	}
}

void printStatLine(const int nNum, const char strText[]){
	printf("▮  %s : %d", strText, nNum); printSymbols(WEAPON_ICON_WIDTH - calcDigits(nNum) - 5 - (int)strlen(strText), SPACE_SYMBOL);
}

void printHeader(const stringMax strName){
	printf("\n  ▮ "); printf(UWHITE); printf("%s", strName); printf(COLOR_RESET); printSymbols(BARS_WIDTH - (int)strlen(strName) - 4, SPACE_SYMBOL); printf(" ▮");
}
