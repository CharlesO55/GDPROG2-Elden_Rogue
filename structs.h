#ifndef STRUCT_FILE
#define STRUCT_FILE

#include "config.h"



typedef struct JobTag{
    string10 strJob;    //Job class name
    int nLevel;         //Current level
    int nHealth, nEndurance, nDexterity, nStrength, nIntelligence, nFaith;  //Job stats
    int* pStats[NUMBER_OF_STATS];   //Array of Pointers to the stats. Same as accessing JobClass.nHealth or JobClass->pStats[0]
} JobClass;


typedef struct WeaponTag{
    string25 strWeaponName;
    int nIdentifier;    //Weapon type
    int nRuneCost;      //Purchase cost
    int nDexCost;       //Equip prerequesite
    int aStats[NUMBER_OF_STATS];	//HP, END, DEX, STR, INT, FTH
} Weapon;


typedef struct EquipmentTag{
    int nPotions;    //Potion counter
    int nInventoryUsedSlots, nInventoryCapacity;    //Dynamic array size counters
    Weapon* pWeaponInventory;   //Index 0 - Equipped weapon
} Equipment;


typedef struct PlayerTag{
    string25 strPlayerName; //Player username
    int nRunes;             //Player currency
    int aShards[MAX_SHARDS];//Static list of shards (levels cleared)
    JobClass sJob;          //Chosen job
    Equipment sEquipment;   //Chosen equipment
} Player;


typedef struct AreaTag{
    int nRow;       //Row size
    int nCol;       //Col size
    int nArea;  //Area index
    int nFloor; //Floor index
    int nCurHP;
    int nMaxHP;
    string25 strAreaName;   //Name of area
    struct AreaTag* pNext;  //Linking to next floor
    struct AreaTag* pPrev;  //Linking to prev floor
    int* pTiles;   //Tiles content
} Area;


//FUNCTIONS
void setPlayerStats(Player* pPlay, string25 strNewName, int nNewRunes, int aNewShards[MAX_SHARDS], JobClass sNewJob);

JobClass* getAllJobs();
    void setJobStats(JobClass *sJob, int nLVL, int nHP, int nEND, int nDEX, int nSTR, int nINT, int nFTH, string10 strJobName);


Weapon* getAllWeapons();
    void setWeaponStats(Weapon* pWeapon, const int nIndex);


#endif