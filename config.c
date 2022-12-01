#include "config.h"

/*
    INITIALIZES BEGINNING STATS OF THE JOBS
    @aJobList - Memory allocated array containing copied data of job instances
    RETURNS ADDRESS OF ARRAY OF JOB INSTANCES LIST
*/
JobClass* initJobClasses(){
    //INSTANCE THE JOBclasses STRUCTS
    JobClass *pJobList = malloc(sizeof(JobClass) * TOTAL_CLASSES);

    //uwaaaghhhh. Where are class constructors when you need rhemmmmm
    setJobStats((pJobList+0), 9, 15, 11, 13, 14, 9, 9, "VAGABOND");
    setJobStats((pJobList+1), 9, 12, 13, 15, 12, 9, 8, "SAMURAI");
    setJobStats((pJobList+2), 8, 11, 11, 16, 10, 10, 8, "WARRIOR");
    setJobStats((pJobList+3), 7, 14, 12, 9, 16, 7, 8, "HERO");
    setJobStats((pJobList+4), 6, 9, 9, 12, 8, 16, 7, "ASTROLOGER");
    setJobStats((pJobList+5), 7, 10, 8, 10, 11, 7, 16, "PROPHET");

    return pJobList;
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


void setPlayerStats(Player* pPlay, string25 strNewName, int nNewRunes, int aNewShards[MAX_SHARDS], JobClass sNewJob){
    strcpy(pPlay->strPlayerName, strNewName);
    pPlay->nRunes = nNewRunes;
    pPlay->sJob = sNewJob;

    int i;
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