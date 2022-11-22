#include "navigation.h"
//HANDLES MENU NAVIGATION

/*	Opens Character creation menu, Load saves, and Returning to main()
*/
void getTitleScreen(){
	Player sPlayer;

	int nChoice;
	do {
		printTitleScreen();

		scanIntChoice(&nChoice, 0, 2);

		switch(nChoice){
			case 1:	//New game
				prompt(2);
				getCharCreationScreen(&sPlayer);
				break;
			case 2:	//Continue
				prompt(2);
				break;
			case 0:	//Exit
				prompt(0);
				return;
			default:
				prompt(102);
		}
	} while (nChoice);
}




void getCharCreationScreen(Player* pPlayer){
	int nChoice;
	int nValid = INVALID;
	string25 strTempName = "";

	//INIT A DEFAULT EMPTY JOB
	JobClass sTempJob;
	setJobStats(&sTempJob, 0, 0, 0, 0, 0, 0, 0, "");
	
	//CHAR CREATION
	do {
		printCharCreationScreen(strTempName, sTempJob.nLevel, sTempJob.strJob);
		scanIntChoice(&nChoice, 0, 3);
		switch(nChoice){
			case 1:	//Enter name
				printf("SPEAK THY NAME: ");
				scanString(strTempName, PLAYER_NAME_MAX_CHARS);
				break;

			case 2:	//Select class
				prompt(2);
				selectJobClass(&sTempJob);
				break;

			case 3:	//Confirm
				if ((int)strlen(strTempName) && sTempJob.nLevel){
					//FINALIZE PLAYER STATS
					int aEmptyShards[MAX_SHARDS] = {0, 0, 0, 0, 0, 0};
					setPlayerStats(pPlayer, strTempName, 0, aEmptyShards, sTempJob);

					prompt(2);
					getRoundTable(pPlayer);
					nValid = VALID;		//Allow the loop to end
				}
				else {	//Missing fields
					prompt(101);
				}
				break;
			case 0: //Exit
				//reset player job if needed
				prompt(1);
				nValid = VALID;
				break;
			default:
				prompt(102);
		}
	} while (!nValid);	//Repeat until not exited
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
			free(pJobList);	//Free the initialized job lists
			return;
		default:
			prompt(102);
		}
	} while (nChoice);
}



void getRoundTable(Player* pPlayer){
	int nChoice = VALID;
	int nValid = INVALID;

	do {
		printRoundTableScreen(*pPlayer);
		scanIntChoice(&nChoice, 0, 5);
		switch(nChoice){
		case 1:	//Fast travel
			prompt(2);
			break;
		case 2:	//Level up
			prompt(2);
			getLevelingMenu(pPlayer);
			break;
		case 3:	//Inventory
			prompt(2);
			break;
		case 4:	//Shop
			prompt(2);
			break;
		case 5:	//Save
			prompt(2);
			break;
		case 0:	//Return to title
			prompt(1);
			nValid = VALID;
			break;
		default:
			prompt(102);
		}
	} while (!nValid);
}



void getLevelingMenu(Player* pPlayer){
	int nChoice;
	do {
		//printLevelingScreen();
		scanIntChoice(&nChoice, 0, 6);
	} while (nChoice);
}