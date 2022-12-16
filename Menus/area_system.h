#ifndef AREA_SYSTEM_FILE
#define AREA_SYSTEM_FILE

#define TILE_INVALID			-1
#define TILE_EMPTY				0
#define TILE_FAST_TRAVEL		1
#define TILE_SPAWN				2
#define TILE_BOSS				3
#define TILE_UP					4
#define TILE_DOWN				5
#define TILE_LOCKED_FAST_TRAVEL 6
#define TILE_CREDITS			7
#define TILE_UP1				8
#define TILE_DOWN1				9

#define TOTAL_AREAS 6

#include "floor_tiles.h"

void getFastTravelMenu(Player* pPlayer);
	int checkAreaUnlocked(const int aShards[MAX_SHARDS]);

Area* initArea(const int nArea);
	void createFloor(const int nArea, const int nFloor, Area* pFloor);
	void connectFloors(const int nArea, Area* pHead);
	int findTile(const Area* pFloor, const int nTarget);

void getAreaPlay(Player* pPlayer, const int nAreaChoice/*Area* pHead*/);
	void movePlayer(const Area* pFloor, const int nAction, int* pPlayerPos);
	//void interactTile(Area *pCurrentFloor, int* pPlayerPos, int* pQuit, Player* pPlayer);
	void interactTile(Area** pFloorAddress, Area *pCurrentFloor, int* pPlayerPos, int* pQuit, Player* pPlayer);
		void getTreasure(int* pRunes, const int nArea);
		void setCommonEnemy(const int nArea, Enemy* pEnemy);
		int getBossWarning();
		void setBossEnemy(const int nIndex, Enemy* pEnemy);
		void changeFloor(Area** pCurrentFloor, int* pPlayerPos, const int nTileType);

#endif