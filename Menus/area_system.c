#include "area_system.h"
#include "area_screen.c"

void getFastTravelMenu(Player* pPlayer){
	int nChoice;
	int nValid = VALID;
	Area* pHead;

	int i;
	do{
		printFastTravelScreen(pPlayer->aShards);
		scanIntChoice(&nChoice, 0, 6);
		switch (nChoice){
			case 1:
			case 2:
			case 3:
			case 4:
				//getAreaMenu
				pPlayer->sEquipment.nPotions = 8;
				pHead = initArea(nChoice-1);
				for (i = 0; i < aFLOORS[nChoice-1]; i++){
					printAreaMap(pPlayer, pHead+i);
					printf("MAP SEEN");
				}
				//getMap(pHead);
				nValid = VALID;
				break;
			case 5:
				if (checkAreaUnlocked(pPlayer->aShards)){
					nValid = VALID;
					prompt(2);
				}
				else{prompt(111); nValid = INVALID;}
				break;
			case 6:
				if (checkAreaUnlocked(pPlayer->aShards)){
					nValid = VALID;
					prompt(2);
				}
				else {prompt(111); nValid = INVALID;}
				break;
			case 0:
				nValid = VALID;
				prompt(1);
				break;
			default:
				prompt(102);
		}
	} while (!nValid);
	free(pHead);
	printf("FREED HEAD\n");
}


int checkAreaUnlocked(const int aShards[MAX_SHARDS]){
	int nTotal = 0;
	int i;

	for (i = 0; i < MAX_SHARDS; i++){
		if(aShards[i] == VALID){
			nTotal++;
		}
	}

	if (nTotal >= 2){ return VALID; }

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

	for (i = 0; i < pFloor->nCol; i++){
		for (j = 0; j < pFloor->nRow; j++){
			pFloor->pTiles[pFloor->nRow * i + j] = aALL_AREA_TILES[nArea][nFloor][pFloor->nRow * i + j];
		}
	}
	
	printf("created floor\n");
}