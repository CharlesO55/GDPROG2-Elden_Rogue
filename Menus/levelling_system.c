#include "levelling_system.h"


void getLevelingMenu(Player* pPlayer){
	int nChoice;
	int nRuneCost;

	do {
		nRuneCost = calcRuneCost((pPlayer->sJob.nLevel));

		printLevelingScreen(*pPlayer, nRuneCost);
		scanIntChoice(&nChoice, 0, 6);

		if(nChoice != 0){
			levelUp(pPlayer, nRuneCost, nChoice);
		}
		
	} while (nChoice);
	prompt(1);
}

	int calcRuneCost(const int nLevel){
		return (nLevel * 100 / 2);
	}

	void levelUp(Player* pPlayer, const int nRuneCost, const int nChoice){
		int nSuccess = checkLevelUp(*(pPlayer->sJob.pStats[nChoice]), nRuneCost, pPlayer->nRunes);

		if (!nSuccess) { return; }

		pPlayer->nRunes -= nRuneCost;
		*(pPlayer->sJob.pStats[0]) += 1;
		*(pPlayer->sJob.pStats[nChoice]) += 1;
		prompt(3);
	}

		int checkLevelUp(const int nStatLevel, const int nRuneCost, const int nRunes){
			if (nRunes < nRuneCost){ prompt(103); return INVALID; }

			if(nStatLevel >= 50){ prompt(104); return INVALID; }

			return VALID;
		}