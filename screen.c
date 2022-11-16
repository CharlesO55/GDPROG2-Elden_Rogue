#include "screen.h"

void printTitleScreen(){
	printf("\n\n  ▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮");
	printf("\n  ▮                               ▮");
	printf("\n  ▮         ELDEN   ROGUE         ▮");
	printf("\n  ▮                               ▮");
	printf("\n  ▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮");

	printf("\n\t1. START");
	printf("\n\t2. CONTINUE");
	printf("\n\t0. EXIT");
}


void printCharCreationScreen(string25 strName, int nLevel, string25 strClass){
	printf("\n\n  ▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮");
	printf("\n  ▮ CHARACTER CREATOR               ▮");
	printf("\n  ▮ Name: "); printf("%s", strName); printSpaces(PLAYER_NAME_MAX_CHARS - (int)strlen(strName)); printf(" ▮");
	printf("\n  ▮ Level: "); printf("%d", nLevel); printf("  Class: ");  printf("%s", strClass); printSpaces(10 - (int)strlen(strClass)); printf("▮");
	printf("\n  ▮                                 ▮");
	printf("\n  ▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮");

	printf("\n\t1. ENTER NAME");
	printf("\n\t2. SELECT CLASS");
	printf("\n\t3. CONFIRM");
	printf("\n\t0. EXIT");
}

void printJobSelectorScreen(JobClass sJob){
	printf("\n\n  ▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮");
	printf("\n  ▮ JOB CLASS SELECTOR              ▮");
	printf("\n  ▮ Job Class: "); printf("%s", sJob.strJob);	printSpaces(PLAYER_NAME_MAX_CHARS - (int)strlen(sJob.strJob)); printf(" ▮");
	printf("\n  ▮     Level: "); printf("%d", sJob.nLevel);		printSpaces(10 - calcDigits(sJob.nLevel)); printf(" ▮");
	printf("\n  ▮    Health: "); printf("%d", sJob.nHealth);	printSpaces(10 - calcDigits(sJob.nHealth)); printf(" ▮");
	printf("\n  ▮ Endurance: "); printf("%d", sJob.nEdurance);	printSpaces(10 - calcDigits(sJob.nEndurance)); printf(" ▮");
	printf("\n  ▮                                 ▮");
	printf("\n  ▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮");

	printf("\n\tENTER JOB NUMBER: ");
	printf("\n\t0. EXIT");
}

int calcDigits(int nNum){
	int nDigit = 0;
	while (nNum > 0){
		nNum /= 10;
		nDigit++;
	}
	return nDigit;
}

void printSpaces(int nSpaces){
	int i;
	for (i = 0; i < nSpaces; i++){
		printf(" ");
	}
}
/*
void printWeaponShopScreen(){

}*/