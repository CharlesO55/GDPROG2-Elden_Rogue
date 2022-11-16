#include "logic.h"



void getTitleScreen(){
	int nChoice = VALID;
	do {
		printTitleScreen();

		scanIntChoice(&nChoice, 0, 2);

		switch(nChoice){
			case 1:
				getCharCreationScreen();
				break;
			case 2:
				printf("\nCONTINUE");
				break;
			case 0:
				prompt(0);
				return;
			default:
				prompt(102);
		}
	} while (nChoice);
}




void getCharCreationScreen(){
	int nChoice = VALID;
	string25 strPlayerName = "";

	//INIT A DEFAULT EMPTY JOB
	JobClass sPlayerJob;
	setJobStats(&sPlayerJob, 0, 0, 0, 0, 0, 0, 0, "");
	
	//CHAR CREATION
	do {
		printCharCreationScreen(strPlayerName, sPlayerJob.nLevel, sPlayerJob.strJob);
		scanIntChoice(&nChoice, 0, 3);

		switch(nChoice){
			case 1:	//Enter name
				printf("SPEAK THY NAME: ");
				scanString(strPlayerName, PLAYER_NAME_MAX_CHARS);
				break;
			case 2:	//Select class
				selectJobClass(&sPlayerJob);
				break;
			case 3:	//Confirm
				//go to game
				break;
			case 0: //Exit
				prompt(1);
				return;
			default:
				prompt(102);
		}
	} while (!nChoice || nChoice != 3);	//Repeat until not confirmed or exited
}


void selectJobClass(JobClass *sPlayerJob){
	int nChoice = VALID;
	strcpy(sPlayerJob->strJob, "JOH");
	sPlayerJob->nLevel = 1300;

	JobClass *pJobList = initJobClasses();

	do{
		printJobSelectorScreen(sPlayerJob);
		scanIntChoice(&nChoice, 0, TOTAL_CLASSES);

		switch(nChoice){
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			sPlayerJob = pJobList[nChoice-1];
			break;
		case 0: //Exit
			prompt(1);
			return;
		default:
			prompt(102);
		}

	} while (nChoice);
}