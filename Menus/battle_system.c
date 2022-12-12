#include "battle_system.h"
#include "Configurations/enemy_stats.h"

void startBattle(Enemy* pEnemy, Player* pPlayer, Area* pFloor){
	int nChoice;
	int nDmg;
	int nEndTurn = INVALID;

	do {
		nDmg = calcDamage(pEnemy, pFloor->nArea);
		printBattleScreen(pEnemy, pPlayer, pFloor);
		printBattleChoices(nDmg, pPlayer->sEquipment.nPotions);
		scanIntChoice(&nChoice, 1, 3);

		switch(nChoice){
			case 1:
				break;
			case 2:
				if(!useDodge(pPlayer))
					{ takeDamage(pPlayer, nDmg); }
				nEndTurn = VALID;
				break;
			case 3:
				if(usePotion(pPlayer))
					{ nEndTurn = VALID; }
				break;
			default:
				prompt(102);
		}
	} while(!isGameOver(pPlayer, pEnemy));
}


int calcDamage(const Enemy* pEnemy, const int nArea){
	int nDmg = generateRNG(pEnemy->aAtkRange[0], pEnemy->aAtkRange[1]);
	
	if (pEnemy->nType != BOSS)
		{nDmg *= (nArea + 1);}

	return nDmg;
}

void takeDamage(Player* pPlayer, const int nDmg){
	pPlayer->nCurHP -= nDmg;
	if (pPlayer->nCurHP < 0)
		{pPlayer->nCurHP = 0;}

	printf("\n[DAMAGE] RECEIVED %d DMG!", nDmg);
}

int useDodge(const Player* pPlayer){
	float fDodge = ((pPlayer->sJob.nEndurance + pPlayer->sEquipment.pWeaponInventory->aStats[1]) / 2.0 + 20) / 100;
	float fRNG = (float)generateRNG(1, 100);

	if (fRNG <= fDodge){
		printf("\n[DODGE]: %.2f vs %.2f SUCCESFULLY DODGED!", fDodge, fRNG);
		return VALID;
	}
	else{
		printf("\n[DODGE]: %.2f vs %.2f DODGE FAILED!", fDodge, fRNG);
		return INVALID;
	}
}

int calcMaxHealth(const Player* pPlayer){
	int nMax = 100 * ((pPlayer->sJob.nHealth + pPlayer->sEquipment.pWeaponInventory->aStats[0]) / 2);
	return nMax;
}

int usePotion(Player* pPlayer){
	if (pPlayer->sEquipment.nPotions <= 0)
		{prompt(116); return INVALID;}
	pPlayer->sEquipment.nPotions -= 1;

	int nMax = calcMaxHealth(pPlayer);

	int nRestore = (int)(nMax * (generateRNG(25, 50) / 100.0));
	pPlayer->nCurHP += nRestore;

	if(pPlayer->nCurHP > nMax)
		{ pPlayer->nCurHP = nMax; }
	printf("\n[BATTLE]: RESTORED %d HP! %d POTIONS REMAINING.", nRestore, pPlayer->sEquipment.nPotions);
	return VALID;
}

int isGameOver(Player* pPlayer, const Enemy* pEnemy){
	if (pPlayer->nCurHP <= 0){
		pPlayer->nRunes = 0;
		printf("DEFEAT.");
		return VALID;
	}

	if (pEnemy->nHP <= 0){
		printf("VICTORY");
		return VALID;
	}
	return INVALID;
}

void printBattleScreen(const Enemy* pEnemy, const Player* pPlayer, const Area* pFloor){
	printf("\n\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);
	printf("\n  ▮ "); printf(UWHITE); printf("%s %d-%d", pFloor->strAreaName, pFloor->nArea, pFloor->nFloor); printf(COLOR_RESET); printSymbols(BARS_WIDTH - (int)strlen(pFloor->strAreaName) - 8, SPACE_SYMBOL); printf(" ▮");
	printf("\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);

	printf("\n  ▮ "); printf("%s", pPlayer->strPlayerName); printf(" ▮"); 
	printf("%s", pEnemy->strEnemyName); printf(" ▮");

	printf("\n  ▮ "); printf("HP: %d", pPlayer->nCurHP); printSymbols(4, SPACE_SYMBOL); printf(" ▮"); 
		printf("HP: %d", pEnemy->nHP); printSymbols(4, SPACE_SYMBOL); 
	printf("\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL); printf("\n\n");
}

void printBattleChoices(const int nDmg, const int nPotions){
	printf("\n  INCOMING DAMAGE: %d", nDmg);
	printf("\n\t1. ATTACK");
	printf("\n\t2. DODGE");
	printf("\n\t3. DRINK POTION (%d/8)", nPotions);
}