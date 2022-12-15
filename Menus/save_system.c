#include "save_system.h"


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
	if (fopen(strFileName, "rb") != 0){
		printf("\nOVERWRITE EXISTING SAVE FILE?\n\t1. YES      0. NO");
		scanIntChoice(&nChoice, 0, 1);
		fclose(fp);
		if (!nChoice) {return;}
	}


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


	//CLOSE THE FILE
	fclose(fp);
}



int loadSave(Player* pPlayer){
	printf("\nEnter save name:");
	stringMax loadName;
	scanString(loadName, 26);

	//FILE PATH
	stringMax strFileName = "Menus/Saves/";
	strcat(strFileName, loadName);
	strcat(strFileName, ".dat");


	//FILE FIND
	FILE *fp;
	if (fopen(strFileName, "rb") == 0){
		printf("\nNO MATCHING FILE FOUND");
		return INVALID;
	}
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



	//CLOSE
	fclose(fp);
	printf("\nSAVE FILE LOADED.");
	return VALID;
}


void getLoadCharacter(Player* pPlayer){
	if(loadSave(pPlayer)){
		repackageStats(pPlayer);
		prompt(2);
		getRoundTable(pPlayer);
	}
	return;
}