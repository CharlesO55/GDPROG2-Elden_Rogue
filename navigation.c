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
					setPlayerStats(pPlayer, strTempName, STARTER_RUNES, aEmptyShards, sTempJob);
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
			getInventoryMenu(&(pPlayer->sEquipment), pPlayer->sJob.nDexterity);
			break;
		case 4:	//Shop
			prompt(2);
			getShopOpen(pPlayer);
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


void getInventoryMenu(Equipment* pEquipment, const int nDex){
	int nChoice;
	int nPage = 0;
	Weapon sTempWep;
	int nIndex;
	do {
											//1-4: 4 weapons inventory							//0: Equipped
		printInventoryScreen((pEquipment->pWeaponInventory+(nPage*4+1)), nPage, nDex, pEquipment->pWeaponInventory->strWeaponName);
		scanIntChoice(&nChoice, 0, 7);

		switch(nChoice){
			case 1:
			case 2:
			case 3:
			case 4:
						//1-4: 4 weapons in inventory
				nIndex = nPage*4 + nChoice;
				sTempWep = *(pEquipment->pWeaponInventory+(nIndex));
				
				if (sTempWep.nIdentifier == EMPTY){	prompt(108); break; }

				if (nDex >= sTempWep.nDexCost){	
					setWeaponStats((pEquipment->pWeaponInventory+(nIndex)), pEquipment->pWeaponInventory->nIdentifier);
					setWeaponStats(pEquipment->pWeaponInventory, sTempWep.nIdentifier);
					//*(pEquipment->pWeaponInventory) = sTempWep;
					prompt(5);
				}

				else{ prompt(110); }
				break;
			case 5:
				if (pEquipment->pWeaponInventory->nIdentifier != EMPTY){
					addWeapon(pEquipment, pEquipment->pWeaponInventory->nIdentifier);	//Readd the weapon to list
					setWeaponStats(pEquipment->pWeaponInventory, EMPTY);	//Reset to empty
					prompt(6);
				}
				else{ prompt(109); }
				break;
			case 6:
				if (nPage > 0){nPage--;}
				else {prompt(107);}
				break;
			case 7:
				if (nPage < (int)(pEquipment->nInventoryCapacity / 4)-1){nPage++;}
				else {prompt(107);}
				break;
			case 0:
				prompt(1);
				break;
			default:
				prompt(102);
			}
	} while(nChoice);	
}


void getShopOpen(Player* pPlayer){
	int nChoice;
	Weapon* pAllWeapons = getAllWeapons();
	do{
		printShopOpening(pPlayer->strPlayerName, pPlayer->nRunes);
		scanIntChoice(&nChoice, 0, 2);

		switch(nChoice){
			case 1:
				//Buy weapons
				getShopBuyMenu(pPlayer, pAllWeapons);
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

	void getShopBuyMenu(Player* pPlayer, Weapon* pAllWeapons){
		int nChoice;
		do{
			printShopBuyScreen(pPlayer->nRunes);
			scanIntChoice(&nChoice, 0, TOTAL_WEAPONS_TYPES);
			if(nChoice){
				getShopBuyWeapons(pPlayer, pAllWeapons+((nChoice-1)*TOTAL_WEAPONS_TYPES_CHOICES), nChoice);
			}
		} while(nChoice);
		prompt(1);
	}

		void getShopBuyWeapons(Player* pPlayer, const Weapon aWeapons[], const int nWeaponType){
			int nChoice;
			do{
				printShopBuyWeapons(aWeapons, nWeaponType, pPlayer->nRunes);
				scanIntChoice(&nChoice, 0, TOTAL_WEAPONS_TYPES_CHOICES);
				
				if (nChoice != 0 && checkWeaponPurchase(*pPlayer, aWeapons[nChoice-1].nRuneCost, aWeapons[nChoice-1].nDexCost)){
					//setWeaponStats(pPlayer->sEquipment.pWeaponInventory+0, aWeapons[nChoice-1].nIdentifier);
					
					addWeapon(&(pPlayer->sEquipment), aWeapons[nChoice-1].nIdentifier);

					pPlayer->nRunes -= aWeapons[nChoice-1].nRuneCost;
					prompt(4);
				}
			}while(nChoice);
			prompt(1);
		}


			int checkWeaponPurchase(const Player sPlayer, const int nRuneCost, const int nDexCost){
				if (sPlayer.nRunes < nRuneCost){
					prompt(103);
					return 0;
				} /*	//DEXTERITY REQ NOT PART OF WEAPON PURCHASE
				if (sPlayer.sJob.nDexterity < nDexCost){
					prompt(105);
					return 0;
				}*/
				return 1;
			}

			void addWeapon(Equipment* pEquipment, const int nIdentifier){
				int i;
				//Expand dynamic array if already at limit
				if (pEquipment->nInventoryUsedSlots >= pEquipment->nInventoryCapacity){
					pEquipment->nInventoryCapacity += 4;
					pEquipment->pWeaponInventory = realloc(pEquipment->pWeaponInventory, (pEquipment->nInventoryCapacity * sizeof(Weapon)));
					
					//Set new slots to empty so we can detect them
					for(i = pEquipment->nInventoryCapacity - 4; i < pEquipment->nInventoryCapacity; i++){
						setWeaponStats(pEquipment->pWeaponInventory + i, EMPTY);
					}
				}

				int nSelected = findEmptySlot(pEquipment->pWeaponInventory, pEquipment->nInventoryCapacity);

				if (nSelected != -1){
					setWeaponStats(pEquipment->pWeaponInventory + nSelected, nIdentifier);
					pEquipment->nInventoryUsedSlots += 1;
					return;
				}

				prompt(106);
			}



			int findEmptySlot(const Weapon* pInventory, const int nElements){
				int i = 1;	//Excluding first slot[0] for equipped items only
				while(i < nElements){
					if (pInventory[i].nIdentifier == EMPTY) {printf("\nEMPTY FOUND\n"); return i;}
					i++;
				}
				printf("\nno EMPTY FOUND\n");
				return -1;
			}