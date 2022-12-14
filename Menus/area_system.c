#include "area_system.h"
#include "area_screen.c"
#include "battle_system.c"
#include "Configurations/enemy_stats.h"

/*Fast travel menu loop and action interpetration. Redirects to areas
	@param pPlayer - The player's stats
*/
void getFastTravelMenu(Player* pPlayer){
	int nChoice;
	int nValid = VALID;
	//Area* pHead;
	
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
				//pHead = initArea(nChoice-1);
				prompt(2);
				//getAreaPlay(pPlayer, pHead);
				getAreaPlay(pPlayer, nChoice);

				nValid = VALID;
				break;
			case 5:
				if (checkAreaUnlocked(pPlayer->aShards)){	//Clear at least 2 areas
					//pHead = initArea(nChoice-1);
					prompt(2);
					//getAreaPlay(pPlayer, pHead);
					getAreaPlay(pPlayer, nChoice);
					nValid = VALID;
				}
				else
					{prompt(111); nValid = INVALID;}
				break;
			case 6:
				if (pPlayer->aShards[4] == VALID || IS_AREA_5_UNLOCKED){		//Clear area 4
					//pHead = initArea(nChoice-1);
					prompt(2);
					//getAreaPlay(pPlayer, pHead);
					getAreaPlay(pPlayer, nChoice);
					nValid = VALID;
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
	/*WILL CRASH
	printf("\nFREEING HEAD");
	free(pHead);
	printf("\nFREED HEAD");*/
}


/*Count the shards and return whether min is met
	@aShards - Array of shard values
	@return VALID - If shard values meet min value
			INVALID - Insufficient shards
*/
int checkAreaUnlocked(const int aShards[MAX_SHARDS]){
	int nTotal = 0;
	int i;

	if (IS_AREA_4_UNLOCKED){return VALID;}	//DEBUG ONLY

	for (i = 0; i < MAX_SHARDS; i++){
		if(aShards[i] == VALID)
			{ nTotal++; }
	}

	if (nTotal >= 2)
		{ return VALID; }

	return INVALID;
}



/*Creates an entire area's floors
	@param nArea - Area index
	@retrun pHead - The very first floor of the area
*/
Area* initArea(const int nArea){
	Area* pHead = malloc(sizeof(nArea) * aFLOORS[nArea]);

	int i;
	for (i = 0; i < aFLOORS[nArea]; i++){
		createFloor(nArea, i, pHead+i);
	}

	connectFloors(nArea, pHead);
	printf("\nADDRESS OF BEFORE pCurr: %p pNEXT: %p", pHead, pHead->pNext);
/*
	printf("finished area\n");
	for (i = 0; i < 21; i++){
		printf("%d ", pHead->pTiles[i]);
	}*/
	return pHead;
}

void connectFloors(const int nArea, Area* pHead){
	Area* pTemp = pHead;
	int i;
	
	for (i = 1; i < aFLOORS[nArea]; i++){
		pTemp->pNext = pHead + i;
		pTemp = pTemp->pNext;
	}
	for (i = aFLOORS[nArea] - 2; i > 0; i--){
		pTemp->pPrev = pHead + i;
		pTemp = pTemp->pPrev;
	}
}


/*Assigns a floor stats and its tiles
	@nArea - The area index
	@nFloor - The floor index
	@pFloor - The floor to alter
*/
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


	printf("ASSIGNING TILES [%d]x[%d]\n", pFloor->nRow, pFloor->nCol);
	for (i = 0; i < pFloor->nRow; i++){
		for (j = 0; j < pFloor->nCol; j++){
			int nIndex = pFloor->nCol * i + j;
			printf("[%d][%d] or [%d] = %d\t", i, j, nIndex, aALL_AREA_TILES[nArea][nFloor][nIndex]);
			//pFloor->pTiles[nIndex] = aALL_AREA_TILES[nArea][nFloor][nIndex];
			switch(nArea){
				case 0:
					pFloor->pTiles[nIndex] = aAREA_0_TILES[nFloor][nIndex];
					break;
				case 1:
					pFloor->pTiles[nIndex] = aAREA_1_TILES[nFloor][nIndex];
					break;
				case 2:
					printf("SETTING...");
					pFloor->pTiles[nIndex] = aAREA_2_TILES[nFloor][nIndex];
					printf("[%d] SETTING SUCCESS!\n", nIndex);
					break;
				case 3:
					pFloor->pTiles[nIndex] = aAREA_3_TILES[nFloor][nIndex];
					break;
				case 4:
					pFloor->pTiles[nIndex] = aAREA_4_TILES[nFloor][nIndex];
					break;
				case 5:
					pFloor->pTiles[nIndex] = aAREA_5_TILES[nFloor][nIndex];
					break;
				default:
					prompt(102);
			}
		}
		printf("%d-%d-%d COL\n", pFloor->nArea, pFloor->nFloor, i);
	}
	printf("created floor\n");
}


/*Action interpetration for map actions
	@pPlayer - Player pointer
	@pHead - Floor pointer
*/
void getAreaPlay(Player* pPlayer, const int nAreaChoice/*Area* pHead*/){
	printf("STARTING AREA");
	//int i;
	int nAction;
	int nQuit = INVALID;
	Area* pCurrentFloor = initArea(nAreaChoice-1);
	Area* pActiveFloor = pCurrentFloor;

	int nPlayerPos = findTile(pCurrentFloor, TILE_FAST_TRAVEL);
	

	do {
		printf("\nFLOOR: %d-%d SIZE: %dx%d", /*pCurrentFloor*/pActiveFloor->nArea, /*pCurrentFloor*/pActiveFloor->nFloor, /*pCurrentFloor*/pActiveFloor->nRow, /*pCurrentFloor*/pActiveFloor->nCol);
		printAreaMap(pPlayer, /*pCurrentFloor*/pActiveFloor, nPlayerPos);
		scanPlayerControl(&nAction);

		switch(nAction){
			case UP:
			case DOWN:
			case LEFT:
			case RIGHT:
				movePlayer(/*pCurrentFloor*/pActiveFloor, nAction, &nPlayerPos);
				break;
			case INTERACT:
				interactTile(/*pCurrentFloor*/pActiveFloor, &nPlayerPos, &nQuit, pPlayer);
				break;
			case QUIT:
				nQuit = VALID;
				break;
			default:
				prompt(102);
		}
	} while (!nQuit);
	free(pCurrentFloor);
	/*
	for (i = 0; i < aFLOORS[pCurrentFloor->nArea]; i++){
		printAreaMap(pPlayer, pHead+i);
	}*/

	//Possibility of crashing. Since pHead is pCurrentFloor and pHead could point to the same
	/*printf("\nFREEING CURENT FLOOR");
	free(pCurrentFloor);
	if (pHead != NULL){
		printf("\nFREEING HEAD");	
		free(pHead);
	}*/
	prompt(1);
}


/*
Finds and Returns the index of the desired tile
	@pFloor - The current floor to scan
	@nTarget - The tile value to compare
	@return i - Position
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


/*Determine the interaction depending on tile
	@param pCurrentFloor - The current floor
	@param pPlayerPos - Player's position
	@param pQuit - Quitting check in getAreaPlay() loop
	@param pPlaye -  Player's stats
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
				if (!startBattle(pEnemy, pPlayer, pCurrentFloor)) //Player lost
					{ *pQuit = VALID; }
				else
					{ pCurrentFloor->pTiles[*pPlayerPos] = TILE_EMPTY; }
				free(pEnemy);
			}
			break;
		case TILE_BOSS:
			if(getBossWarning()){
				Enemy* pEnemy = malloc(sizeof(Enemy));
				setBossEnemy(pCurrentFloor->nArea, pEnemy);
				printf("\nA GREAT ENEMY APPROACHES");
				if (!startBattle(pEnemy, pPlayer, pCurrentFloor)) //Player lost
					{ *pQuit = VALID; }
				else{ 
					pCurrentFloor->pTiles[*pPlayerPos] = TILE_EMPTY; 
					
					if(strcmp(pEnemy->strEnemyName, aBOSS_NAMES[5]) == 0){
					  	printf("\nTHE ELDEN BEAST EMERGES!");
					  	setBossEnemy(6, pEnemy);
					  	if (!startBattle(pEnemy, pPlayer, pCurrentFloor)) //Player lost
							{ *pQuit = VALID; pPlayer->aShards[5] = INVALID; };	//Reset the shard if player failed to defeat elden beast
					  }
					}
				free(pEnemy);
			}
			break;
		case TILE_UP:
			printf("\nADDRESS OF BEFORE pCurr: %p pNEXT: %p", pCurrentFloor, pCurrentFloor->pNext);
			pCurrentFloor = pCurrentFloor->pNext;
			printf("\nADDRESS OF AFTER pCurr: %p pNEXT: %p", pCurrentFloor, pCurrentFloor->pNext);
			break;
		case TILE_DOWN:
			printf("\nADDRESS OF BEFORE pCurr: %p pNEXT: %p", pCurrentFloor, pCurrentFloor->pNext);
			changeFloor(&pCurrentFloor, pPlayerPos, nTileType);
			printf("\nADDRESS OF AFTER pCurr: %p pNEXT: %p", pCurrentFloor, pCurrentFloor->pNext);
			break;
		case TILE_FAST_TRAVEL:
			{ *pQuit = VALID; }
			break;
		case TILE_LOCKED_FAST_TRAVEL:
			if(pPlayer->aShards[pCurrentFloor->nArea] != VALID)
				{prompt(115);}
			else
				{ *pQuit = VALID; }
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


int getBossWarning(){
	printf("[WARNING] BOSS AHEAD. Do you want to proceed?");
	printf("\n\t1. YES\t0. NO");

	int nChoice;
	scanIntChoice(&nChoice, 0, 1);
	return nChoice;
}

/*Updates player runes from treasure
	@param pRunes - Pointer to player's runes
	@param nArea - Current area number (increment by 1 needed)
*/
void getTreasure(int* pRunes, const int nArea){
	int nTreasure = generateRNG(50, 150) * (nArea + 1);		//Increment area by 1. Stormveil is 0
	printf(GREEN);
	printf("[GAME]: TREASURE FOUND %d RUNES", nTreasure);
	printf(COLOR_RESET);
	*pRunes += nTreasure;		//Add to player runes
}


/*Sets the stats for a common enemy instance depending on area
	@param nArea - The current area number (increment by 1 needed)
	@param pEnemy - The enemy's stats
*/
void setCommonEnemy(const int nArea, Enemy* pEnemy){
	int nEnemyType = generateRNG(1, 3);
	int i;
	pEnemy->nType = nEnemyType - 1;

	pEnemy->nHP = generateRNG(aCOMMON_HP_RANGE[pEnemy->nType][0], aCOMMON_HP_RANGE[pEnemy->nType][1]) * (nArea + 1);
	pEnemy->nCurHP = pEnemy->nHP;
	pEnemy->aAtkRange[0] = aCOMMON_ATK_RANGE[pEnemy->nType][0];
	pEnemy->aAtkRange[1] = aCOMMON_ATK_RANGE[pEnemy->nType][1];

	pEnemy->aDefenses[0] = aCOMMON_DEFENSES[pEnemy->nType][0];
	pEnemy->aDefenses[1] = aCOMMON_DEFENSES[pEnemy->nType][1];
	pEnemy->aDefenses[2] = aCOMMON_DEFENSES[pEnemy->nType][2];

	for (i = 0; i < 5; i++){
		strcpy(pEnemy->aSprites[i], aCOMMON_SPRITES[nArea][pEnemy->nType][i]);
	}
	strcpy(pEnemy->strEnemyName, aCOMMON_NAMES[nArea][pEnemy->nType]);
}

void setBossEnemy(const int nIndex, Enemy* pEnemy){
	pEnemy->nType = BOSS;
	
	pEnemy->nHP = aBOSS_HP[nIndex];
	pEnemy->nCurHP = pEnemy->nHP;

	pEnemy->aAtkRange[0] = aBOSS_ATK_RANGE[nIndex][0];
	pEnemy->aAtkRange[1] = aBOSS_ATK_RANGE[nIndex][1];

	pEnemy->aDefenses[0] = aBOSS_DEFENSES[nIndex][0];
	pEnemy->aDefenses[1] = aBOSS_DEFENSES[nIndex][1];
	pEnemy->aDefenses[2] = aBOSS_DEFENSES[nIndex][2];

	int i;
	for (i = 0; i < 5; i++){
		strcpy(pEnemy->aSprites[i], aBOSS_SPRITES[nIndex][i]);
	}
	strcpy(pEnemy->strEnemyName, aBOSS_NAMES[nIndex]);
}

void changeFloor(Area** pCurrentFloor, int* pPlayerPos, const int nTileType){
	if (nTileType == TILE_UP){
		if ((*pCurrentFloor)->pNext == NULL)
			{prompt(117); return;}

		*pCurrentFloor = (*pCurrentFloor)->pNext;
		printf("\nADDRESS OF INSIDE AFTER pCurr: %p pNEXT: %p", *pCurrentFloor, (*pCurrentFloor)->pNext);

		printf("\nFLOOR: %d-%d SIZE: %dx%d", (*pCurrentFloor)->nArea, (*pCurrentFloor)->nFloor, (*pCurrentFloor)->nRow, (*pCurrentFloor)->nCol);

		*pPlayerPos = findTile(*pCurrentFloor, TILE_DOWN);
		
		if (*pPlayerPos == -1)
			{*pPlayerPos = findTile(*pCurrentFloor, TILE_EMPTY);}
		
		/*if (pCurrentFloor->pNext == NULL)
			{prompt(117); return;}
		
		pCurrentFloor = pCurrentFloor->pNext;

		printf("\nFLOOR: %d-%d SIZE: %dx%d", pCurrentFloor->nArea, pCurrentFloor->nFloor, pCurrentFloor->nRow, pCurrentFloor->nCol);

		*pPlayerPos = findTile(pCurrentFloor, TILE_DOWN);
		
		if (*pPlayerPos == -1)
			{*pPlayerPos = findTile(pCurrentFloor, TILE_EMPTY);}
		*/
	}
/*

	else{
		if (pCurrentFloor->pPrev == NULL)
			{prompt(117); return;}


		pCurrentFloor = pCurrentFloor->pPrev;
		*pPlayerPos = findTile(pCurrentFloor, TILE_UP);

		if (*pPlayerPos == -1)
			{*pPlayerPos = findTile(pCurrentFloor, TILE_EMPTY);}
	}*/
	prompt(8);
}