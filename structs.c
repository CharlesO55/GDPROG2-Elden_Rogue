#include "structs.h"

void setPlayerStats(Player* pPlay, string25 strNewName, int nNewRunes, int aNewShards[MAX_SHARDS], JobClass sNewJob){
    strcpy(pPlay->strPlayerName, strNewName);
    pPlay->nRunes = nNewRunes;
    pPlay->sJob = sNewJob;

    pPlay->sEquipment.nInventoryCapacity = STARTING_INVENTORY_SIZE;
    pPlay->sEquipment.nInventoryUsedSlots = 0;
    pPlay->sEquipment.pWeaponInventory = malloc(sizeof(Weapon) * STARTING_INVENTORY_SIZE);

    int i;
    for (i = 0; i < STARTING_INVENTORY_SIZE; i++){
    	setWeaponStats(pPlay->sEquipment.pWeaponInventory+i, EMPTY);
    }

    for (i = 0; i < MAX_SHARDS; i++){
        pPlay->aShards[i] = aNewShards[i];
    }
}


	void repackageStats(Player* pPlayer){
	    pPlayer->sJob.pStats[0] = &(pPlayer->sJob.nLevel);
	    pPlayer->sJob.pStats[1] = &(pPlayer->sJob.nHealth);
	    pPlayer->sJob.pStats[2] = &(pPlayer->sJob.nEndurance);
	    pPlayer->sJob.pStats[3] = &(pPlayer->sJob.nDexterity);
	    pPlayer->sJob.pStats[4] = &(pPlayer->sJob.nStrength);
	    pPlayer->sJob.pStats[5] = &(pPlayer->sJob.nIntelligence);
	    pPlayer->sJob.pStats[6] = &(pPlayer->sJob.nFaith);
	}


/*
    INITIALIZES BEGINNING STATS OF THE JOBS
    @aJobList - Memory allocated array containing copied data of job instances
    RETURNS ADDRESS OF ARRAY OF JOB INSTANCES LIST
*/
JobClass* getAllJobs(){
    //INSTANCE THE JOBclasses STRUCTS
    JobClass *pAllJobs = malloc(sizeof(JobClass) * TOTAL_CLASSES);

    //uwaaaghhhh. Where are class constructors when you need rhemmmmm
   	int i;
   	for (i = 0; i < TOTAL_CLASSES; i++){
   		setJobStats(pAllJobs+i, 
   			CONFIG_JobStats[i][0], 
   			CONFIG_JobStats[i][1], 
   			CONFIG_JobStats[i][2], 
   			CONFIG_JobStats[i][3], 
   			CONFIG_JobStats[i][4],
   			CONFIG_JobStats[i][5],
   			CONFIG_JobStats[i][6],
   			CONFIG_JobName[i]);
   	}

    return pAllJobs;
}

	/*
	    ALTERS JOB CLASS VARIABLES VALUE
	    @sJob - JobClass instance to be altered (instance address)
	    @nLVL, nHP, nEND, nDEX, nSTR, nINT, nFTH - Int values to be assigned (>= 0)
	    @strJobName - String name of the job (10 char)
	*/
	void setJobStats(JobClass *sJob, int nLVL, int nHP, int nEND, int nDEX, int nSTR, int nINT, int nFTH, string10 strJobName){
	    sJob->nLevel = nLVL;     //Change struct variable value via pointer
	    sJob->nHealth = nHP;
	    sJob->nEndurance = nEND;
	    sJob->nDexterity = nDEX;
	    sJob->nStrength = nSTR;
	    sJob->nIntelligence = nINT;
	    sJob->nFaith = nFTH;
	    strcpy(sJob->strJob, strJobName);
	}


Weapon* getAllWeapons(){
	int nTotalWeapons = TOTAL_WEAPONS_TYPES_CHOICES * TOTAL_WEAPONS_TYPES;
	Weapon* pAllWeapon = malloc(sizeof(Weapon) * nTotalWeapons);

	int i;
	for (i = 0; i < nTotalWeapons; i++){
		setWeaponStats(pAllWeapon+i, i);
	}
	return pAllWeapon;
}


	void setWeaponStats(Weapon* pWeapon, int nIndex){
		pWeapon->nIdentifier = nIndex;
		int i;

		if(nIndex == EMPTY){
			strcpy(pWeapon->strWeaponName, "EMPTY");
    		pWeapon->nRuneCost = 0;
   	 		pWeapon->nDexCost = 0;

   	 		for (i = 0; i < NUMBER_OF_STATS; i++){
    			pWeapon->aStats[i] = 0;
    		} 
    		return;
		}


		int nRow = nIndex / TOTAL_WEAPONS_TYPES_CHOICES;
		int nCol = nIndex % TOTAL_WEAPONS_TYPES_CHOICES;

		strcpy(pWeapon->strWeaponName, CONFIG_WeaponName[nRow][nCol]);
    	pWeapon->nRuneCost = CONFIG_WeaponRuneCost[nRow][nCol];
   	 	pWeapon->nDexCost = CONFIG_WeaponDexterityReq[nRow][nCol];

    	
    	for (i = 0; i < NUMBER_OF_STATS; i++){
    		pWeapon->aStats[i] = CONFIG_WeaponStats[nRow][nCol][i];
    	}
	}


void resetHealth(Player* pPlayer){
	pPlayer->nCurHP = 100 * ((pPlayer->sJob.nHealth + pPlayer->sEquipment.pWeaponInventory->aStats[0]) / 2);
	//printf("HP: %d from %d and %d\n", pPlayer->nCurHP, pPlayer->sJob.nHealth, pPlayer->sEquipment.pWeaponInventory->aStats[0]);
}