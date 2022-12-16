#ifndef STRUCT_FILE
#define STRUCT_FILE

#include "config.h"



typedef struct JobTag{
    string10 strJob;    //Job class name
    int nLevel;         //Current level
    int nHealth, nEndurance, nDexterity, nStrength, nIntelligence, nFaith;  //Job stats
    int* pStats[NUMBER_OF_STATS+1];   //Array of Pointers to the stats. Same as accessing JobClass.nHealth or JobClass->pStats[1]
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
    int nCurHP;            //HP active in floor
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
    struct AreaTag* pNext1; //Other floors
    struct AreaTag* pPrev1; //Other floors
    int* pTiles;   //Tiles content
} Area;

typedef struct EnemyTag{
    int nType;
    int nHP;
    int nCurHP;
    int aAtkRange[2];
    float aDefenses[3];
    stringMax strEnemyName;
    string25 aSprites[5];
} Enemy;




//FUNCTIONS
void setPlayerStats(Player* pPlayer, const string25 strNewName, const int nNewRunes, const int aNewShards[MAX_SHARDS], const JobClass sNewJob);
//void setPlayerStats(Player* pPlay, string25 strNewName, int nNewRunes, int aNewShards[MAX_SHARDS], JobClass sNewJob);
void resetHealth(Player* pPlayer);

JobClass* getAllJobs();
    void setJobStats(JobClass *sJob, const int nLVL, const int nHP, const int nEND, const int nDEX, const int nSTR, const int nINT, const int nFTH, const string10 strJobName);
    //void setJobStats(JobClass *sJob, int nLVL, int nHP, int nEND, int nDEX, int nSTR, int nINT, int nFTH, string10 strJobName);


Weapon* getAllWeapons();
    void setWeaponStats(Weapon* pWeapon, const int nIndex);


#endif