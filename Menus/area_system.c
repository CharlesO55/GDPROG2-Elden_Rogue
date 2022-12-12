#include "area_system.h"
#include "area_screen.c"
#include "battle_system.c"
#include "Configurations/enemy_stats.h"

void getFastTravelMenu(Player* pPlayer){
	int nChoice;
	int nValid = VALID;
	Area* pHead;
	
	resetHealth(pPlayer);
	pPlayer->sEquipment.nPotions = 8;	//Reset potions when entering new area


	do{
		printFastTravelScreen(pPlayer->aShards);
		scanIntChoice(&nChoice, 0, 6);
		
		switch (nChoice){
			case 1:
			case 2:
			case 3:
			case 4:				
				pHead = initArea(nChoice-1);
				prompt(2);
				getAreaPlay(pPlayer, pHead);

				nValid = VALID;
				break;
			case 5:
				if (checkAreaUnlocked(pPlayer->aShards)){	//Clear at least 2 areas
					nValid = VALID;
					prompt(2);
				}
				else
					{prompt(111); nValid = INVALID;}
				break;
			case 6:
				if (pPlayer->aShards[4] == VALID){		//Clear area 4
					nValid = VALID;
					prompt(2);
				}
				else 
					{prompt(111); nValid = INVALID;}
				break;
			case 0:
				nValid = VALID;
				prompt(1);
				break;
			default:
				prompt(102);
		}
	} while (!nValid);
}


/*
Count the shards and return whether min is met
	@aShards - Array of shard values
	@return VALID/INVALID - If shard values meet min value
*/
int checkAreaUnlocked(const int aShards[MAX_SHARDS]){
	int nTotal = 0;
	int i;

	for (i = 0; i < MAX_SHARDS; i++){
		if(aShards[i] == VALID)
			{ nTotal++; }
	}

	if (nTotal >= 2)
		{ return VALID; }

	return INVALID;
}


Area* initArea(const int nArea){
	Area* pHead = malloc(sizeof(nArea) * aFLOORS[nArea]);

	int i;
	for (i = 0; i < aFLOORS[nArea]; i++){
		createFloor(nArea, i, pHead+i);
	}

	printf("finished area\n");
	for (i = 0; i < 21; i++){
		printf("%d ", pHead->pTiles[i]);
	}
	return pHead;
}

void createFloor(const int nArea, const int nFloor, Area* pFloor){
	int i, j;
	pFloor->pPrev = NULL;
	pFloor->pNext = NULL;
	pFloor->nArea = nArea;
	pFloor->nFloor = nFloor;
	pFloor->nRow = aROWS[nArea][nFloor];
	pFloor->nCol = aCOLS[nArea][nFloor];
	strcpy(pFloor->strAreaName, aAREA_NAMES[nArea]);
	pFloor->pTiles = malloc(sizeof(int) * pFloor->nRow * pFloor->nCol);
	printf("ASSIGNING TILES\n");
	for (i = 0; i < pFloor->nRow; i++){
		for (j = 0; j < pFloor->nCol; j++){
			int nIndex = pFloor->nCol * i + j;
			printf("[%d-%d] %d WORK\n", i, j, aALL_AREA_TILES[nArea][nFloor][nIndex]);
			pFloor->pTiles[nIndex] = aALL_AREA_TILES[nArea][nFloor][nIndex];
		}
		printf("%d-%d-%d COL\n", pFloor->nArea, pFloor->nFloor, i);
	}
	
	printf("created floor\n");
}



void getAreaPlay(Player* pPlayer, Area* pHead){
	printf("STARTING AREA");
	//int i;
	int nAction;
	int nQuit = INVALID;
	Area* pCurrentFloor = pHead;

	int nPlayerPos = findTile(pCurrentFloor, TILE_FAST_TRAVEL);
	

	do {
		printAreaMap(pPlayer, pCurrentFloor, nPlayerPos);
		scanPlayerControl(&nAction);

		switch(nAction){
			case UP:
			case DOWN:
			case LEFT:
			case RIGHT:
				movePlayer(pCurrentFloor, nAction, &nPlayerPos);
				break;
			case INTERACT:
				interactTile(pCurrentFloor, &nPlayerPos, &nQuit, pPlayer);
				break;
			case QUIT:
				nQuit = VALID;
				prompt(1);
				break;
			default:
				prompt(102);
		}
	} while (!nQuit);
	/*
	for (i = 0; i < aFLOORS[pCurrentFloor->nArea]; i++){
		printAreaMap(pPlayer, pHead+i);
	}*/
	free(pCurrentFloor);
	free(pHead);
	printf("FREED HEAD\n");
}


/*
Finds and Returns the index of the desired tile
	@pFloor - The current floor to scan
	@nTarget - The tile value to compare
	@return (i) - Position
	@return (-1) - No matching tile found
*/
int findTile(const Area* pFloor, const int nTarget){
	int i;
	int nSize = pFloor->nRow * pFloor->nCol;
	for (i = 0; i < nSize; i++){
		if (pFloor->pTiles[i] == nTarget)
			{return i;}
	}
	prompt(112);
	return -1;
}


/*
Changes the player position if possible
	@pFloor - The current floor
	@nAction - The direction player wants to move in
	@pPlayerPos - Player position to alter
*/
void movePlayer(const Area* pFloor, const int nAction, int* pPlayerPos){
//MOVE HORIZONTAL
	if(nAction == LEFT 									//When moving left
		&& (*pPlayerPos % pFloor->nCol) != 0 				//&& player is not at the left edge
		&& pFloor->pTiles[*pPlayerPos - 1] != TILE_INVALID)	//&& next tile is valid
			
			{*pPlayerPos -= 1; }
	

	else if (nAction == RIGHT 								//When moving right
		&& (*pPlayerPos % pFloor->nCol) != pFloor->nCol - 1 	//&& not at right edge
		&& pFloor->pTiles[*pPlayerPos + 1] != TILE_INVALID)  	//&& next tile is valid
			
			{*pPlayerPos += 1; }


//MOVE VERTICAL
	else if (nAction == UP 										//When moving right
		&& *pPlayerPos >= pFloor->nCol									//&& not at the top
		&& pFloor->pTiles[*pPlayerPos - pFloor->nCol] != TILE_INVALID)	//&& next tile is valid
			
			{*pPlayerPos -= pFloor->nCol; }

	else if(nAction == DOWN										//When moving down
		&& *pPlayerPos < (pFloor->nRow * pFloor->nCol) - pFloor->nCol	//&& not at the bottom
		&& pFloor->pTiles[*pPlayerPos + pFloor->nCol] != TILE_INVALID)	//&& next tile is valid

			{*pPlayerPos += pFloor->nCol; }
		
//INVALID MOVEMENT
	else
		{prompt(113);}
}


/*
Determine the interaction depending on tile
*/
void interactTile(Area *pCurrentFloor, int* pPlayerPos, int* pQuit, Player* pPlayer){
	int nTileType = pCurrentFloor->pTiles[*pPlayerPos];

	switch(nTileType){
		case TILE_EMPTY:
			prompt(114);
			break;
		case TILE_SPAWN:
			if (generateRNG(1, 4) == 1){		//25% chance treasure
				getTreasure(&(pPlayer->nRunes), pCurrentFloor->nArea);
				pCurrentFloor->pTiles[*pPlayerPos] = TILE_EMPTY;	//Disable the tile
			}
			else{
				Enemy* pEnemy = malloc(sizeof(Enemy));
				setCommonEnemy(pCurrentFloor->nArea, pEnemy);
				startBattle(pEnemy, pPlayer, pCurrentFloor);
				free(pEnemy);
			}
			break;
		case TILE_BOSS:
			break;
		case TILE_UP:
		case TILE_DOWN:
			break;
		case TILE_FAST_TRAVEL:
			*pQuit = VALID;
			prompt(1);
			break;
		case TILE_LOCKED_FAST_TRAVEL:
			prompt(115);
			break;
		case TILE_CREDITS:
			if (pPlayer->aShards[5] == VALID)
				{printCreditsScreen();}
			else
				{prompt(115);}
			break;
		default:
			prompt(102);
	}
}

void getTreasure(int* pRunes, const int nArea){
	int nTreasure = generateRNG(50, 150) * (nArea + 1);		//Increment area by 1. Stormveil is 0
	printf(GREEN);
	printf("[GAME]: TREASURE FOUND %d RUNES", nTreasure);
	printf(COLOR_RESET);
	*pRunes += nTreasure;		//Add to player runes
}

void setCommonEnemy(const int nArea, Enemy* pEnemy){
	int nEnemyType = generateRNG(1, 3);

	pEnemy->nType = nEnemyType - 1;

	pEnemy->nHP = generateRNG(aCOMMON_HP_RANGE[pEnemy->nType][0], aCOMMON_HP_RANGE[pEnemy->nType][1]) * (nArea + 1);
	pEnemy->aAtkRange[0] = aCOMMON_ATK_RANGE[pEnemy->nType][0];
	pEnemy->aAtkRange[1] = aCOMMON_ATK_RANGE[pEnemy->nType][1];

	pEnemy->aDefenses[0] = aCOMMON_DEFENSES[pEnemy->nType][0];
	pEnemy->aDefenses[1] = aCOMMON_DEFENSES[pEnemy->nType][1];
	pEnemy->aDefenses[2] = aCOMMON_DEFENSES[pEnemy->nType][2];

	strcpy(pEnemy->strEnemyName, aCOMMON_NAMES[nArea][pEnemy->nType]);
}