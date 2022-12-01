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
					setPlayerStats(pPlayer, strTempName, 1000, aEmptyShards, sTempJob);
					repackageStats(pPlayer);
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

	JobClass *pJobList = getAllJobs();

	do{
		printJobSelectorScreen(*pPlayerJob);
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
			getInventoryMenu(pPlayer->sEquipment.pWeaponInventory);
			break;
		case 4:	//Shop
			prompt(2);
			getShopMenu(pPlayer);
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
	int nRuneCost;

	do {
		nRuneCost = calcRuneCost((pPlayer->sJob.nLevel));

		printLevelingScreen(*pPlayer, nRuneCost);
		scanIntChoice(&nChoice, 0, 6);

		if(nChoice != 0){
			levelUp(pPlayer, nRuneCost, nChoice);
		}
		
	} while (nChoice);
	prompt(1);
}

	int calcRuneCost(const int nLevel){
		return (nLevel * 100 / 2);
	}

	void levelUp(Player* pPlayer, const int nRuneCost, const int nChoice){
		int nSuccess = checkLevelUp(*(pPlayer->sJob.pStats[nChoice]), nRuneCost, pPlayer->nRunes);

		if (nSuccess) {
			pPlayer->nRunes -= nRuneCost;
			*(pPlayer->sJob.pStats[0]) += 1;
			*(pPlayer->sJob.pStats[nChoice]) += 1;
			prompt(3);
		}
		else if(nSuccess == INVALID){
			prompt(103);
		}
		else if(nSuccess == INVALID2){
			prompt(104);
		}
	}

		int checkLevelUp(const int nStatLevel, const int nRuneCost, const int nRunes){
			if (nRunes < nRuneCost){ return INVALID; }

			if(nStatLevel >= 50){ return INVALID2; }

			return VALID;
		}


void getInventoryMenu(int* pInventory){
	int nChoice;
	int nPage = 0;
	do {
		printInventoryScreen(pInventory, nPage);
		scanIntChoice(&nChoice, 0, 3);

		switch(nChoice){
			case 1:
				break;
			case 2:
				nPage--;
				break;
			case 3:
				if (nPage)
				nPage++;
				break;
			case 0:
				prompt(1);
				break;
			default:
				prompt(102);
			}
	} while(nChoice);	
}


void getShopMenu(Player* pPlayer){
	int nChoice;
	Weapon* pAllWeapons = getAllWeapons();
	do{
		printShopOpening(pPlayer->strPlayerName, pPlayer->nRunes);
		scanIntChoice(&nChoice, 0, 2);

		switch(nChoice){
			case 1:
				//Buy weapons
				break;
			case 2:
				//Sell weapons
				break;
			case 0:
				prompt(1);
				break;
			default:
				prompt(102);
		}
	} while(nChoice);
	free(pAllWeapons);
}