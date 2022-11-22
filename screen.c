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


void printCharCreationScreen(string25 strName, int nLevel, string25 strClass){
	printf("\n\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);
	printf("\n  ▮ CHARACTER CREATOR               ▮");
	printf("\n  ▮ Name: "); printf("%s", strName); printSymbols(PLAYER_NAME_MAX_CHARS - (int)strlen(strName), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮ Level: "); printf("%d", nLevel); printSymbols(3- calcDigits(nLevel), SPACE_SYMBOL); printf("  Class: ");  printf("%s", strClass); printSymbols(13 - (int)strlen(strClass), SPACE_SYMBOL); printf("▮");
	printf("\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);

	printf("\n\t1. ENTER NAME");
	printf("\n\t2. SELECT CLASS");
	printf("\n\t3. CONFIRM");
	printf("\n\t0. CANCEL");
}

void printJobSelectorScreen(JobClass *pJob){
	printf("\n\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);
	printf("\n  ▮ JOB CLASS SELECTOR              ▮");
	printf("\n  ▮    Job Class : %s", pJob->strJob);			   printSymbols(BARS_WIDTH - 19 - (int)strlen(pJob->strJob), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮        Level : %d", pJob->nLevel); 		   printSymbols(BARS_WIDTH - 19 - calcDigits(pJob->nLevel), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮       Health : %d", pJob->nHealth);	       printSymbols(BARS_WIDTH - 19 - calcDigits(pJob->nHealth), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮    Endurance : %d", pJob->nEndurance);    printSymbols(BARS_WIDTH - 19 - calcDigits(pJob->nEndurance), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮    Dexterity : %d", pJob->nDexterity);    printSymbols(BARS_WIDTH - 19 - calcDigits(pJob->nDexterity), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮     Strength : %d", pJob->nStrength);	   printSymbols(BARS_WIDTH - 19 - calcDigits(pJob->nStrength), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮ Intelligence : %d", pJob->nIntelligence); printSymbols(BARS_WIDTH - 19 - calcDigits(pJob->nIntelligence), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮        Faith : %d", pJob->nFaith);		   printSymbols(BARS_WIDTH - 19 - calcDigits(pJob->nFaith), SPACE_SYMBOL); printf(" ▮");
	printf("\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);

	printf("\n\tSELECT JOB CLASS: ");
	printf("\n\t\t1. VAGABDOND");
	printf("\n\t\t2. SAMURAI");
	printf("\n\t\t3. WARRIOR");
	printf("\n\t\t4. HERO");
	printf("\n\t\t5. ASTROLOGER");
	printf("\n\t\t6. PROPHET");
	printf("\n\t0. RETURN TO CREATOR");
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

void printSymbols(int nAmount, int nSymbol){
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



void printRoundTableScreen(Player sPlayer){
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
	printf("\n\t0. QUIT GAME");
}


void printShards(int aShards[MAX_SHARDS]){
	int i;
	for (i = 0; i < MAX_SHARDS; i++){
		if (aShards[i] != 0)	//Active
			printf("▲");
		else{
			printf("△");
		}
	}
}