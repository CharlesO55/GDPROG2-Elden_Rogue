#include "screen.h"

void printTitleScreen(){
	printf("\n  "); printSymbols(BARS_WIDTH);
	printf("\n  ▮                                 ▮");
	printf("\n  ▮          ELDEN   ROGUE          ▮");
	printf("\n  ▮                                 ▮");
	printf("\n  "); printSymbols(BARS_WIDTH);

	printf("\n\t1. START");
	printf("\n\t2. CONTINUE");
	printf("\n\t0. EXIT");
}


void printCharCreationScreen(string25 strName, int nLevel, string25 strClass){
	printf("\n\n  "); printSymbols(BARS_WIDTH);
	printf("\n  ▮ CHARACTER CREATOR               ▮");
	printf("\n  ▮ Name: "); printf("%s", strName); printSpaces(PLAYER_NAME_MAX_CHARS - (int)strlen(strName)); printf(" ▮");
	printf("\n  ▮ Level: "); printf("%d", nLevel); printSpaces(3- calcDigits(nLevel)); printf("  Class: ");  printf("%s", strClass); printSpaces(13 - (int)strlen(strClass)); printf("▮");
	printf("\n  "); printSymbols(BARS_WIDTH);

	printf("\n\t1. ENTER NAME");
	printf("\n\t2. SELECT CLASS");
	printf("\n\t3. CONFIRM");
	printf("\n\t0. CANCEL");
}

void printJobSelectorScreen(JobClass *pJob){
	printf("\n\n  "); printSymbols(BARS_WIDTH);
	printf("\n  ▮ JOB CLASS SELECTOR              ▮");
	printf("\n  ▮    Job Class : %s", pJob->strJob);			   printSpaces(BARS_WIDTH - 19 - (int)strlen(pJob->strJob)); printf(" ▮");
	printf("\n  ▮        Level : %d", pJob->nLevel); 		   printSpaces(BARS_WIDTH - 19 - calcDigits(pJob->nLevel)); printf(" ▮");
	printf("\n  ▮       Health : %d", pJob->nHealth);	       printSpaces(BARS_WIDTH - 19 - calcDigits(pJob->nHealth)); printf(" ▮");
	printf("\n  ▮    Endurance : %d", pJob->nEndurance);    printSpaces(BARS_WIDTH - 19 - calcDigits(pJob->nEndurance)); printf(" ▮");
	printf("\n  ▮    Dexterity : %d", pJob->nDexterity);    printSpaces(BARS_WIDTH - 19 - calcDigits(pJob->nDexterity)); printf(" ▮");
	printf("\n  ▮     Strength : %d", pJob->nStrength);	   printSpaces(BARS_WIDTH - 19 - calcDigits(pJob->nStrength)); printf(" ▮");
	printf("\n  ▮ Intelligence : %d", pJob->nIntelligence); printSpaces(BARS_WIDTH - 19 - calcDigits(pJob->nIntelligence)); printf(" ▮");
	printf("\n  ▮        Faith : %d", pJob->nFaith);		   printSpaces(BARS_WIDTH - 19 - calcDigits(pJob->nFaith)); printf(" ▮");
	printf("\n  "); printSymbols(BARS_WIDTH);

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

void printSymbols(int nSymbols){
	int i;
	for (i = 0; i < nSymbols; i++){
		printf("▮");
	}
}

void printSpaces(int nSpaces){
	int i;
	for (i = 0; i < nSpaces; i++){
		printf(" ");
	}
}



void printRoundTableScreen(JobClass pJob){
	printf("\n\n  "); printSymbols(BARS_WIDTH);
	printf("\n  ▮ ROUNDTABLE HOLD          ▮");/*
	printf("\n  ▮ Name: %s", strName); printSpaces(PLAYER_NAME_MAX_CHARS - (int)strlen(strName)); printf(" ▮");
	printf("\n  ▮ Level: %d", nLevel); printSpaces(3- calcDigits(nLevel)); printf("  Class: ");  printf("%s", strClass); printSpaces(13 - (int)strlen(strClass)); printf("▮");
	printf("\n  ▮ Runes: "); printf("   Shards: %d"); printSpaces(3); printf(" ▮");*/
	printf("\n  "); printSymbols(BARS_WIDTH);
}
/*
void printWeaponShopScreen(){

}*/