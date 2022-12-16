#include "save_system.h"

/*Present save options
	@param pPlayer - Player to pass
*/
void getSaveMenu(Player* pPlayer){
	int nChoice;

	do {
		printf("\n  SELECT ACTION: ");
		printf("\n\t1. SAVE");
		printf("\n\t2. LOAD");
		printf("\n\t0. RETURN");

		scanIntChoice(&nChoice, 0, 2);

		switch(nChoice){
			case 0:
				break;
			case 1:
				getSave(pPlayer);
				break;
			case 2:
				loadSave(pPlayer);
				break;
			default:
				prompt(102);
		}
	}while(nChoice);
}


/*Saves the player data when successful
	@param pPlayer - Player values to save
*/
void getSave(Player* pPlayer){
	printf("\n  Save file will be based off your charcter name.");
	printf("\n\tPROCEED? 1. YES		0. NO");
	
	int nChoice;
	scanIntChoice(&nChoice, 0, 1);

	if (!nChoice){
		return;
	}

	//FILE PATH
	FILE *fp;
	stringMax strFileName = "Menus/Saves/";
	strcat(strFileName, pPlayer->strPlayerName);
	strcat(strFileName, ".dat");

	
	
	//IF EXISITNG FILE NAME
	fp = fopen(strFileName, "rb");
	if (fp != 0){
		printf("\nOVERWRITE EXISTING SAVE FILE?\n\t1. YES      0. NO");
		scanIntChoice(&nChoice, 0, 1);
		fclose(fp);
		if (!nChoice) {return;}
	}

	int i;
	//PACK
	int aJobStats[NUMBER_OF_STATS + 1] = { 
		*(pPlayer->sJob.pStats[0]), 
		*(pPlayer->sJob.pStats[1]),
		*(pPlayer->sJob.pStats[2]),
		*(pPlayer->sJob.pStats[3]),
		*(pPlayer->sJob.pStats[4]),
		*(pPlayer->sJob.pStats[5]),
		*(pPlayer->sJob.pStats[6])
	};
	//CREATE
	fp = fopen(strFileName, "wb");

	//WRITE
	fwrite(&(pPlayer->strPlayerName), sizeof(pPlayer->strPlayerName), 1, fp);
	fwrite(&(pPlayer->nRunes), sizeof(int), 1, fp);
	fwrite(&(pPlayer->aShards), sizeof(int), MAX_SHARDS, fp);
	fwrite(&(pPlayer->sJob.strJob), sizeof(pPlayer->sJob.strJob), 1, fp);
	fwrite(&(aJobStats), sizeof(int), 7, fp);
	fwrite(&(pPlayer->sEquipment.nInventoryUsedSlots), sizeof(int), 1, fp);
	fwrite(&(pPlayer->sEquipment.nInventoryCapacity), sizeof(int), 1, fp);
	for (i = 0; i < pPlayer->sEquipment.nInventoryCapacity; i++){
		fwrite(&(pPlayer->sEquipment.pWeaponInventory[i].nIdentifier), sizeof(int), 1, fp);
	}


	//CLOSE THE FILE
	fclose(fp);
	prompt(10);
}


/*Load saved data files when possible
	@param pPlayer - Player values to alter
	@return INVALID - Unsuccessful
			VALID - Succesfully loaded character
*/
int loadSave(Player* pPlayer){
	printf("\nEnter save name:");
	stringMax loadName;
	scanString(loadName, 26);

	//FILE PATH
	stringMax strFileName = "Menus/Saves/";
	strcat(strFileName, loadName);
	strcat(strFileName, ".dat");


	int i;
	//FILE FIND
	FILE *fp;

	//NO FILE FOUND
	if (fopen(strFileName, "rb") == 0){
		prompt(118);
		return INVALID;
	}

	//OPEN
	fp = fopen(strFileName, "rb");

	//READ
	fread(&(pPlayer->strPlayerName), sizeof(pPlayer->strPlayerName), 1, fp);
	fread(&(pPlayer->nRunes), sizeof(int), 1, fp);
	fread(&(pPlayer->aShards), sizeof(int), MAX_SHARDS, fp);
	fread(&(pPlayer->sJob.strJob), sizeof(pPlayer->sJob.strJob), 1, fp);
	fread(&(pPlayer->sJob.nLevel), sizeof(int), 1, fp);
	fread(&(pPlayer->sJob.nHealth), sizeof(int), 1, fp);
	fread(&(pPlayer->sJob.nEndurance), sizeof(int), 1, fp);
	fread(&(pPlayer->sJob.nDexterity), sizeof(int), 1, fp);
	fread(&(pPlayer->sJob.nStrength), sizeof(int), 1, fp);
	fread(&(pPlayer->sJob.nIntelligence), sizeof(int), 1, fp);
	fread(&(pPlayer->sJob.nFaith), sizeof(int), 1, fp);
	fread(&(pPlayer->sEquipment.nInventoryUsedSlots), sizeof(int), 1, fp);
	fread(&(pPlayer->sEquipment.nInventoryCapacity), sizeof(int), 1, fp);
	pPlayer->sEquipment.pWeaponInventory = malloc(sizeof(Weapon) * pPlayer->sEquipment.nInventoryCapacity);
	for (i = 0; i < pPlayer->sEquipment.nInventoryCapacity; i++){
		fread(&(pPlayer->sEquipment.pWeaponInventory[i].nIdentifier), sizeof(int), 1, fp);
		setWeaponStats(pPlayer->sEquipment.pWeaponInventory+i, pPlayer->sEquipment.pWeaponInventory[i].nIdentifier);
	}

	//CLOSE
	fclose(fp);

	prompt(9);
	return VALID;
}


/*Loads the character from scratch and begins game if successful
	@param pPlayer - Player to initialized loaded data
*/
void getLoadCharacter(Player* pPlayer){
	//BEGIN GAME WHEN SUCCSEFUL
	if(loadSave(pPlayer)){
		repackageStats(pPlayer);
		prompt(2);
		getRoundTable(pPlayer);
	}
	return;
}