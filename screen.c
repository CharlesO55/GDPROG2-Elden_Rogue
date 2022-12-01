#include "screen.h"

void printTitleScreen(){
	printf("\n\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);
	printf("\n  ▮                                 ▮");
	printf("\n  ▮          ELDEN   ROGUE          ▮");
	printf("\n  ▮                                 ▮");
	printf("\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);

	printf("\n\t1. START");
	printf("\n\t2. CONTINUE");
	printf("\n\t0. EXIT");
}


void printCharCreationScreen(const string25 strName, const int nLevel, const string25 strClass){
	printf("\n\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);
	printf("\n  ▮ CHARACTER CREATOR               ▮");
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
	printf("\n  ▮ JOB CLASS SELECTOR              ▮");
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
		/*case SHARD_SYMBOL: 
			printf("▲");
			break;
		case EMPTY_SHARD_SYMBOL: 
			printf("△");
			break;*/
		default:
			printf("");
		}
	}
}



void printRoundTableScreen(const Player sPlayer){
	printf("\n\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);
	printf("\n  ▮ ROUNDTABLE HOLD"); printSymbols(BARS_WIDTH - (int)strlen("ROUNDTABLE HOLD") - 4, SPACE_SYMBOL); printf(" ▮");
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
	printf("\n  ▮ LEVEL UP"); printSymbols(BARS_WIDTH - (int)strlen("▮ LEVEL UP"), SPACE_SYMBOL); printf(" ▮");
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



void printInventoryScreen(int* pInventory, int nPage){

}

void printShopOpening(const string25 strName, const int nRunes){
	printf("\n\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);
	printf("\n  ▮ SHOP MENU"); printSymbols(BARS_WIDTH - (int)strlen("▮ SHOP MENU"), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮ Hello, %s", strName); printSymbols(BARS_WIDTH - (int)strlen("▮ Hello,") - strlen(strName), SPACE_SYMBOL); printf("▮");
	printf("\n  ▮ Runes: %d", nRunes); printSymbols(BARS_WIDTH - (int)strlen("▮ Runes: ") - calcDigits(nRunes), SPACE_SYMBOL); printf(" ▮");
	printf("\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);
	
	printf("\n\nSELECT ACTION:");
	printf("\n\t1. BUY WEAPONS");
	printf("\n\t2. SELL WEAPONS");
	printf("\n\t0. RETURN TO ROUNDTABLE HOLD");
}