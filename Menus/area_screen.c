#include "area_screen.h"
#include "area_system.h"

void printFastTravelScreen(const int aShards[MAX_SHARDS]){
	printf("\n\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);
	printHeader("FAST TRAVEL MENU");
	printf("\n  ▮ SHARDS: ");printShards(aShards); printSymbols(BARS_WIDTH - (int)strlen("▮ SHARDS: ") - 6, SPACE_SYMBOL); printf(" ▮");
	printf("\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL); 

	printf("\n\n  TRAVEL TO:");
	printf("\n\t1. STORMVEIL CASTLE");
	printf("\n\t2. RAYA LUCARIA ACADEMY");
	printf("\n\t3. REDMANE CASTLE");
	printf("\n\t4. VOLCANO MANOR");
	if (!checkAreaUnlocked(aShards)) {printf(RED);}
	printf("\n\t5. LEYNDELL ROYAL CAPITAL");
	if (aShards[4] == INVALID){ printf(RED); }
	printf("\n\t6. THE ELDEN THRONE"); printf(COLOR_RESET);
	printf("\n  0. RETURN TO ROUNDTABLE HOLD");
}


void printAreaMap(const Player* pPlayer, const Area* pFloor, const int nPlayerPos){
	printf("\n\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);
	printf("\n  ▮ "); printf(UWHITE); printf("%s %d-%d", pFloor->strAreaName, pFloor->nArea, pFloor->nFloor); printf(COLOR_RESET); printSymbols(BARS_WIDTH - (int)strlen(pFloor->strAreaName) - 8, SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮ LV %d %s", pPlayer->sJob.nLevel, pPlayer->sJob.strJob); printSymbols(20 - (int)strlen("▮ LV ") - calcDigits(pPlayer->sJob.nLevel) - (int)strlen(pPlayer->sJob.strJob), SPACE_SYMBOL);
		printf(" HP: %d", pPlayer->nCurHP); printSymbols(14 - calcDigits(pPlayer->nCurHP) - (int)strlen(" HP: "), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮ RUNES: %d", pPlayer->nRunes); printSymbols(21 - (int)strlen("▮ RUNES: ") - calcDigits(pPlayer->nRunes), SPACE_SYMBOL); 
		printf(" POTIONS: %d", pPlayer->sEquipment.nPotions); printSymbols(13 - (int)strlen("POTIONS: ") - calcDigits(pPlayer->sEquipment.nPotions), SPACE_SYMBOL);  printf(" ▮");
	printf("\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL); printf("\n\n");

	printTiles(pFloor, nPlayerPos);

	printf("\n\t◠  ◠  ◠  ◠  ◠  ◠");
	printf("\n\t↺  ←  ↑  ↓  →  ◎");
	printf("\n\t◡  ◡  ◡  ◡  ◡  ◡");
	printf("\n\tQ  A  W  S  D  E");
}


/*Prints the tiles based on floor dimesions
	@param pFloor - Contains floor row and col sizes
	@param nPlayerPos - The player's index position
*/
void printTiles(const Area* pFloor, const int nPlayerPos){
	int i, j;
	printf("\n\t");
	for(i = 0; i < pFloor->nRow; i++){
		for(j = 0; j < pFloor->nCol; j++){
			if (nPlayerPos == pFloor->nCol * i + j)
				{ printf(YELLOW); }
			else 
				{ checkTileColor(pFloor->pTiles[pFloor->nCol * i + j]); }
			printf("■■■");
			printf(COLOR_RESET);
			printf(" ");
		}
		printf("\n\t");
		for(j = 0; j < pFloor->nCol; j++){
			if (nPlayerPos == pFloor->nCol * i + j)
				{ printf(YELLOW); }
			else 
				{ checkTileColor(pFloor->pTiles[pFloor->nCol * i + j]); }
			printf("■");
			printTileContent(pFloor->pTiles[pFloor->nCol * i + j]);
			printf("■");
			printf(COLOR_RESET);
			printf(" ");
		}
		printf("\n\t");
		for(j = 0; j < pFloor->nCol; j++){
			if (nPlayerPos == pFloor->nCol * i + j)
				{ printf(YELLOW); }
			else 
				{ checkTileColor(pFloor->pTiles[pFloor->nCol * i + j]); }
			printf("■■■");
			printf(COLOR_RESET);
			printf(" ");
		}
		printf("\n\n\t");
	}
}

/*Determine text color based on tile type
	@param nTile - The tile type
*/
void checkTileColor(const int nTile){
	switch(nTile){
		case TILE_INVALID:
			printf(GRAY);
			break;
		case TILE_LOCKED_FAST_TRAVEL:
		case TILE_BOSS:	
		case TILE_CREDITS:	
			printf(RED);
			break;
		case TILE_SPAWN:
			printf(BLUE);
			break;
		case TILE_UP:
		case TILE_DOWN:
		case TILE_UP1:
		case TILE_DOWN1:
		case TILE_FAST_TRAVEL:
			printf(GREEN);
			break;
		case TILE_EMPTY:
			break;
		default:
			prompt(102);
	}
}

/*Determine text symbol based on tile type
	@param nTile - The tile type
*/
void printTileContent(const int nTile){
	switch(nTile){
		case TILE_INVALID:
			printf("⨉");
			break;
		case TILE_EMPTY:
			printf(" ");
			break;
		case TILE_FAST_TRAVEL:
			printf("↺");
			break;
		case TILE_SPAWN:
			printf("※");
			break;
		case TILE_BOSS:
			printf("⨂");
			break;
		case TILE_UP:
		case TILE_UP1:
			printf("▲");
			break;
		case TILE_DOWN:
		case TILE_DOWN1:
			printf("▼");
			break;
		case TILE_LOCKED_FAST_TRAVEL:
			printf("֏");
			break;
		case TILE_CREDITS:
			printf("Ω");
			break;
		default:
			prompt(102);
	}
}


void printCreditsScreen(){
	printf("\n\n\tTHANK YOU FOR PLAYING");
	printf("\n\t     ELDEN ROGUE");

	printf(UWHITE);	printf("\n\tDEVELOPERS:");	printf(COLOR_RESET);
	printf("\n\t\tONG, CHARLES MATHEW");

	printf(UWHITE); printf("\n\tSPECIAL THANKS:"); printf(COLOR_RESET);
	printf("\n\t\tESPULGAR, CANDY JOYCE");
	printf("\n\n");

	printf("PRESS ANY BUTTON TO CONTINUE...");
	int n;
	scanf("%d", &n);
}