#ifndef AREA_SCREEN_FILE
#define AREA_SCREEN_FILE

//#include "screen.h"

void printFastTravelScreen(const int aShards[MAX_SHARDS]);
void printAreaMap(const Player* pPlayer, const Area* pHead);

void printTiles(const Area* pFloor);
void checkTileColor(const int nTile);
void printTileContent(const int nTile);
#endif