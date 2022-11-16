#include "logic.h"



void getTitleScreen(){
	int nChoice;
	do {
		printTitleScreen();

		scanIntChoice(&nChoice, 0, 2);

		switch(nChoice){
			case 1:
				getCharCreationScreen();
				prompt(2);
				break;
			case 2:
				prompt(2);
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
	int nChoice;
	int nValid = INVALID;
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
				prompt(2);
				selectJobClass(&sPlayerJob);
				break;
			case 3:	//Confirm
				if ((int)strlen(strPlayerName) && sPlayerJob.nLevel){
					prompt(2);
					getRoundTable(&sPlayerJob);
					nValid = VALID;
				}
				else {
					prompt(101);
				}
				break;
			case 0: //Exit
				//reset player job if needed
				prompt(1);
				return;
			default:
				prompt(102);
		}
	} while (!nChoice || !nValid);	//Repeat until not exited
}


void selectJobClass(JobClass *pPlayerJob){
	int nChoice = VALID;

	JobClass *pJobList = initJobClasses();

	do{
		printJobSelectorScreen(pPlayerJob);
		scanIntChoice(&nChoice, 0, TOTAL_CLASSES);

		switch(nChoice){
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			setJobStats(pPlayerJob, 
				pJobList[nChoice-1].nLevel, 
				pJobList[nChoice-1].nHealth, 
				pJobList[nChoice-1].nEndurance, 
				pJobList[nChoice-1].nDexterity, 
				pJobList[nChoice-1].nStrength, 
				pJobList[nChoice-1].nIntelligence, 
				pJobList[nChoice-1].nFaith, 
				pJobList[nChoice-1].strJob);
			break;
		case 0: //Exit
			prompt(1);
			free(pJobList);
			return;
		default:
			prompt(102);
		}
	} while (nChoice);
}


void getRoundTable(JobClass *pJob){
	printRoundTableScreen(*pJob);
}