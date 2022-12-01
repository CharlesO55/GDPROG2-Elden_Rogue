#ifndef STRUCT_FILE
#define STRUCT_FILE

#include "config.h"



typedef struct JobTag{
    string10 strJob;
    int nLevel;
    int nHealth, nEndurance, nDexterity, nStrength, nIntelligence, nFaith;
    int* pStats[NUMBER_OF_STATS];
} JobClass;


typedef struct WeaponTag{
    string25 strWeaponName;
    int nIdentifier;
    int nRuneCost;
    int nDexCost;
    int aStats[NUMBER_OF_STATS];	//HP, END, DEX, STR, INT, FTH
} Weapon;


typedef struct EquipmentTag{
    Weapon sEquipedWeapon;
    int* pWeaponInventory;
    int nPotions;
} Equpment;


typedef struct PlayerTag{
    string25 strPlayerName;
    int nRunes;
    int aShards[MAX_SHARDS];
    //int nProgress[][];
    JobClass sJob;
    Equpment sEquipment;
} Player;


//FUNCTIONS
void setPlayerStats(Player* pPlay, string25 strNewName, int nNewRunes, int aNewShards[MAX_SHARDS], JobClass sNewJob);

JobClass* getAllJobs();
    void setJobStats(JobClass *sJob, int nLVL, int nHP, int nEND, int nDEX, int nSTR, int nINT, int nFTH, string10 strJobName);


Weapon* getAllWeapons();
    void setWeaponStats(Weapon* pWeapon, const int nIndex);


#endif