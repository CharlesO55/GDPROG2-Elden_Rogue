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

#define TOTAL_AREAS 6

#include "floor_tiles.h"

void getFastTravelMenu(Player* pPlayer);
	int checkAreaUnlocked(const int aShards[MAX_SHARDS]);

Area* initArea(const int nArea);
	void createFloor(const int nArea, const int nFloor, Area* pFloor);


#endif