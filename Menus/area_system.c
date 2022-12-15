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
	
	//Prepare the player stats
	resetHealth(pPlayer);
	pPlayer->sEquipment.nPotions = 8;	//Reset potions when entering new area


	do{
		printFastTravelScreen(pPlayer->aShards);
		scanIntChoice(&nChoice, 0, 6);
		
		//Redirect the player to a floor to create when valid
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

	//COUNT THEIR TOTAL ACTIVE SHARDS
	for (i = 0; i < MAX_SHARDS; i++){
		if(aShards[i] == VALID)
			{ nTotal++; }
	}

	//BEATEN 2 AREA BOSSES
	if (nTotal >= 2)
		{ return VALID; }
	//DIDN'T MEET REQ
	return INVALID;
}



/*Creates an entire area's floors
	@param nArea - Area index
	@retrun pHead - The very first floor of the area
*/
Area* initArea(const int nArea){
	//ALLOCATE MEM FOR x AMOUNT OF FLOORS DEPENDING ON AREA
	Area* pHead = malloc(sizeof(nArea) * aFLOORS[nArea]);

	//CREATE ALL THE FLOORS
	int i;
	for (i = 0; i < aFLOORS[nArea]; i++){
		createFloor(nArea, i, pHead+i);
	}

	//CONNECT CREATED FLOORS
	connectFloors(nArea, pHead);
	/*
	printf("finished area\n");
	for (i = 0; i < 21; i++){
		printf("%d ", pHead->pTiles[i]);
	}*/
	return pHead;
}

/*Connects the floors pNext and pPrev
	@nArea - Used to identfiy total number of floors in an area
	@pHead - The starting floor of an area
*/
void connectFloors(const int nArea, Area* pHead){
	Area* pTemp = pHead;	//Start at the first floor
	int i;
	
	//ASSIGN ALL PNEXT FIRST AND MOVE TOWARDS LAST FLOOR
	for (i = 1; i < aFLOORS[nArea]; i++){
		pTemp->pNext = pHead + i;
		pTemp = pTemp->pNext;
	}
	//START ASSIGNING PPREV AND MOVING BACK TO FIRST FLOOR
	for (i = aFLOORS[nArea] - 2; i >= 0; i--){
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
	//INIT THE FLOOR PROPERTIES
	pFloor->pPrev = NULL;
	pFloor->pNext = NULL;
	pFloor->nArea = nArea;
	pFloor->nFloor = nFloor;
	pFloor->nRow = aROWS[nArea][nFloor];
	pFloor->nCol = aCOLS[nArea][nFloor];
	strcpy(pFloor->strAreaName, aAREA_NAMES[nArea]);
	
	//MEM ALLOC x AMOUNT OF TILES
	pFloor->pTiles = malloc(sizeof(int) * pFloor->nRow * pFloor->nCol);
	//printf("pTiles is %d bytes / %d elements", sizeof(pFloor->pTiles), sizeof(pFloor->pTiles)/sizeof(int));

	//ASSIGN THE TILES
	printf("\nASSIGNING TILES [%d]x[%d]\n", pFloor->nRow, pFloor->nCol);
	for (i = 0; i < pFloor->nRow; i++){
		for (j = 0; j < pFloor->nCol; j++){
			int nIndex = pFloor->nCol * i + j;
			//printf("[%d][%d] or [%d] = %d\t", i, j, nIndex, aALL_AREA_TILES[nArea][nFloor][nIndex]);
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
					//pFloor->pTiles[nIndex] = nIndex;
					printf("[%d] SETTING SUCCESS!\n", nIndex);
					pFloor->pTiles[nIndex] = aAREA_2_TILES[nFloor][nIndex];
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
	@nAreaChoice - Player's chosen area used in identifying area to init
	//@pHead - Floor pointer
*/
void getAreaPlay(Player* pPlayer, const int nAreaChoice/*Area* pHead*/){
	printf("STARTING AREA");
	//int i;
	int nAction;
	int nQuit = INVALID;
	//CREATE AN ENTIRE AREA AND ALL IT'S FLOORS
	Area* pCurrentFloor = initArea(nAreaChoice-1);

	//POSITION THE PLAYER AT THE FAST TRAVEL TILE
	int nPlayerPos = findTile(pCurrentFloor, TILE_FAST_TRAVEL);
	

	do {
		printAreaMap(pPlayer, pCurrentFloor/*pActiveFloor*/, nPlayerPos);
		scanPlayerControl(&nAction);

		switch(nAction){
			case UP:
			case DOWN:
			case LEFT:
			case RIGHT:
				movePlayer(pCurrentFloor/*pActiveFloor*/, nAction, &nPlayerPos);
				break;
			case INTERACT:
				interactTile(&pCurrentFloor/*&pActiveFloor*/, pCurrentFloor, &nPlayerPos, &nQuit, pPlayer);
				//printf("\nADDRESS OF AFTER pCurr: %p pNEXT: %p pPrev: %p", pCurrentFloor, pCurrentFloor->pNext, pCurrentFloor->pPrev);
				break;
			//Q KEY. NOT PART OF DEMO REQ BUT HELPS LEAVING AREA FASTER THAN FAST TRAVEL TILE
			case QUIT:	
				nQuit = VALID;
				break;
			//DEBUG TOOLS. USED WHEN STUCK IN A FLOOR WITH NO DOOR 
			case DEBUG_CONTROL_0:
				changeFloor(&pCurrentFloor, &nPlayerPos, TILE_UP);
				break;
			case DEBUG_CONTROL_1:
				changeFloor(&pCurrentFloor, &nPlayerPos, TILE_DOWN);
				break;
			default:
				prompt(102);
		}
	} while (!nQuit);
	
	//RESET THE FLOOR TO THE FIRST FLOOR
	while(pCurrentFloor->pPrev != NULL){
		pCurrentFloor = pCurrentFloor->pPrev;
	}
	//FREE THE FLOOR. DO NOT LEAVE THE 1ST FLOOR UNFREED. WILL CRASH WHEN initArea tries to assign a new area
	printf("\nFREEING HEAD %p", pCurrentFloor);
	free(pCurrentFloor);
	printf("\nFREED");
	
	
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
	@nTarget - The tile type to compare
	@return i - Position
	@return (-1) - No matching tile found
*/
int findTile(const Area* pFloor, const int nTarget){
	int i;
	int nSize = pFloor->nRow * pFloor->nCol;

	//SCAN ALL THE FLOOR'S TILES TO LOOCK FOR MATCHING TILE
	for (i = 0; i < nSize; i++){
		if (pFloor->pTiles[i] == nTarget)
			{return i;}
	}
	//NO MATCHING TILE FOUND
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
	@param pFloorAddress - The floor address to change into pNext or pPrev
	@param pCurrentFloor - The current floor. Quicker access for tiles
	@param pPlayerPos - Player's position
	@param pQuit - Quitting check in getAreaPlay() loop
	@param pPlayer -  Player's stats
*/
void interactTile(Area** pFloorAddress, Area *pCurrentFloor, int* pPlayerPos, int* pQuit, Player* pPlayer){
	//READ CURRENT TILE THE PLAYER IS ON
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

			else{		//75% chance enemy fight
				Enemy* pEnemy = malloc(sizeof(Enemy));				//Mem alloc an enemy (Allows for creation of more than one enemy though battle loop won't read the others)
				setCommonEnemy(pCurrentFloor->nArea, pEnemy);		//Set the enemies stats

				//THROW INTO BATTLE LOOP
				if (!startBattle(pEnemy, pPlayer, pCurrentFloor)) 	//PLAYER LOST
					{ *pQuit = VALID; } //EXIT THE AREA ENTIRELY 
				else    											//PLAYER WON
					{ pCurrentFloor->pTiles[*pPlayerPos] = TILE_EMPTY; }	//CONTINUE IN THE AREA AND SET THE TILE TO CLEARED
				free(pEnemy);
			}
			break;
		case TILE_BOSS:
			if(getBossWarning()){
				//CREATE THE BOSS
				Enemy* pEnemy = malloc(sizeof(Enemy));			
				setBossEnemy(pCurrentFloor->nArea, pEnemy);
				printf("\nA GREAT ENEMY APPROACHES");

				//START BATTLE LOOP
				if (!startBattle(pEnemy, pPlayer, pCurrentFloor)) //Player lost
					{ *pQuit = VALID; }
				//PLAYER WON BOSS BATTLE
				else{ 
					pCurrentFloor->pTiles[*pPlayerPos] = TILE_EMPTY; 
					
					//DEFEATED BOSS WAS PRECEDENT TO ELDEN BEAST
					if(strcmp(pEnemy->strEnemyName, aBOSS_NAMES[5]) == 0){
						//CREATE ELDEN BEAST AND REASSIGN EXISTING ENEMY AS NEW BOSS
					  	printf("\nTHE ELDEN BEAST EMERGES!");
					  	setBossEnemy(6, pEnemy);

					  	//ANOTHER BATTLE LOOP
					  	if (!startBattle(pEnemy, pPlayer, pCurrentFloor)){ //Player lost
							*pQuit = VALID; 
							pPlayer->aShards[5] = INVALID;	//Reset the shard if player failed to defeat elden beast. SHARD WAS AWARDED WHEN BEATING PRECEEDING BOSS
					    }
					}
				}
				free(pEnemy);
			}
			break;
		case TILE_UP:
		case TILE_DOWN:
			//CHANGE THE FLOOR
			changeFloor(pFloorAddress, pPlayerPos, nTileType);
			break;
		case TILE_FAST_TRAVEL:
			{ *pQuit = VALID; }
			break;
		case TILE_LOCKED_FAST_TRAVEL:
			//PLAYER HASN'T CLEARED THE AREA BOSS
			if(pPlayer->aShards[pCurrentFloor->nArea] != VALID)
				{prompt(115);}
			//PLAYER BEAT THE BOSS AT LEAST ONCE
			else
				{ *pQuit = VALID; }
			break;
		case TILE_CREDITS:
			//PLAYER HASN'T CLEARED THE ELDEN BEAST BOSS
			if (pPlayer->aShards[5] == VALID)
				{printCreditsScreen();}
			else
				{prompt(115);}
			break;
		default:
			prompt(102);

	}
}

/*Prompt a warning
	@return 0 - Cancelled boss battle
	@return 1 - Confirming boss battle begin
*/
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
	//RNG COMMON ENEMY TYPE FROM 1-3
	int nEnemyType = generateRNG(1, 3);
	int i;
	//DECREMENT TO MATCH ARRAY INDEX
	pEnemy->nType = nEnemyType - 1;

	//ASSIGN VALUES
	pEnemy->nHP = generateRNG(aCOMMON_HP_RANGE[pEnemy->nType][0], aCOMMON_HP_RANGE[pEnemy->nType][1]) * (nArea + 1);
	pEnemy->nCurHP = pEnemy->nHP;
	pEnemy->aAtkRange[0] = aCOMMON_ATK_RANGE[pEnemy->nType][0];
	pEnemy->aAtkRange[1] = aCOMMON_ATK_RANGE[pEnemy->nType][1];

	pEnemy->aDefenses[0] = aCOMMON_DEFENSES[pEnemy->nType][0];
	pEnemy->aDefenses[1] = aCOMMON_DEFENSES[pEnemy->nType][1];
	pEnemy->aDefenses[2] = aCOMMON_DEFENSES[pEnemy->nType][2];

	//COPY THE SPRITE AND NAME STRINGS
	for (i = 0; i < 5; i++){
		strcpy(pEnemy->aSprites[i], aCOMMON_SPRITES[nArea][pEnemy->nType][i]);
	}
	strcpy(pEnemy->strEnemyName, aCOMMON_NAMES[nArea][pEnemy->nType]);
}


/*Sets the stats for a boss enemy instance depending on index
	@param nIndex - Boss identifier
	@param pEnemy - The enemy stats to set
*/
void setBossEnemy(const int nIndex, Enemy* pEnemy){
	//SET TYPE
	pEnemy->nType = BOSS;
	
	//ASSIGN STATS
	pEnemy->nHP = aBOSS_HP[nIndex];
	pEnemy->nCurHP = pEnemy->nHP;

	pEnemy->aAtkRange[0] = aBOSS_ATK_RANGE[nIndex][0];
	pEnemy->aAtkRange[1] = aBOSS_ATK_RANGE[nIndex][1];

	pEnemy->aDefenses[0] = aBOSS_DEFENSES[nIndex][0];
	pEnemy->aDefenses[1] = aBOSS_DEFENSES[nIndex][1];
	pEnemy->aDefenses[2] = aBOSS_DEFENSES[nIndex][2];

	//COPY SPRITE AND NAMES
	int i;
	for (i = 0; i < 5; i++){
		strcpy(pEnemy->aSprites[i], aBOSS_SPRITES[nIndex][i]);
	}
	strcpy(pEnemy->strEnemyName, aBOSS_NAMES[nIndex]);
}

/*Change the floor to pNext or pPrev when applicable
	@param pFloorAddress - The address of the floor to change
	@param pPlayerPos - The player's position to readjust
	@param nTileType - The door tile type the player interacted
*/
void changeFloor(Area** pFloorAddress, int* pPlayerPos, const int nTileType){
	if (nTileType == TILE_UP){
		//NO FLOOR ABOVE
		if ((*pFloorAddress)->pNext == NULL)
			{prompt(117); return;}

		//CHANGE TO NEXT FLOOR
		*pFloorAddress = (*pFloorAddress)->pNext;
		//REPOSITION PLAYER TO DOOR TILE
		*pPlayerPos = findTile(*pFloorAddress, TILE_DOWN);
		
	}
	else if (nTileType == TILE_DOWN){
		//NO FLOOR BELOW
		if ((*pFloorAddress)->pPrev == NULL)
			{prompt(117); return;}

		//CHANGE TO PREV FLOOR
		*pFloorAddress = (*pFloorAddress)->pPrev;
		//REPOSITION PLAYER TO DOOR TILE
		*pPlayerPos = findTile(*pFloorAddress, TILE_UP);
	}

	//Change position to an empty if desired up/down tile was not to found
	if (*pPlayerPos == -1)
			{*pPlayerPos = findTile(*pFloorAddress, TILE_EMPTY);}


		/*if (pCurrentFloor->pNext == NULL)
			{prompt(117); return;}
		
		pCurrentFloor = pCurrentFloor->pNext;

		printf("\nFLOOR: %d-%d SIZE: %dx%d", pCurrentFloor->nArea, pCurrentFloor->nFloor, pCurrentFloor->nRow, pCurrentFloor->nCol);

		*pPlayerPos = findTile(pCurrentFloor, TILE_DOWN);
		
		if (*pPlayerPos == -1)
			{*pPlayerPos = findTile(pCurrentFloor, TILE_EMPTY);}

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