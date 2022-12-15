#include "levelling_system.h"


/*Levelling up menu and action interpetration
	@param pPlayer - Player's stats and runes to alter
*/
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

/*Calculate the rune cost for leveling up
	@param nLevel - Players current level
	@return - The rune cost
*/
int calcRuneCost(const int nLevel){
	return (nLevel * 100 / 2);
}



/*Increase player's stat when applicable
	@param pPlayer - The player's stats
	@param nRuneCost - Cost for levelling up
	@param nChoice - The player's choice. Used in determining which stat to upgrade 
*/
void levelUp(Player* pPlayer, const int nRuneCost, const int nChoice){
	int nSuccess = checkLevelUp(*(pPlayer->sJob.pStats[nChoice]), nRuneCost, pPlayer->nRunes);

	if (nSuccess == 0) { prompt(103); return; }
	else if (nSuccess == -1) { prompt(104); return; }


	pPlayer->nRunes -= nRuneCost;
	*(pPlayer->sJob.pStats[0]) += 1;
	*(pPlayer->sJob.pStats[nChoice]) += 1;
	prompt(3);
}

/*Check when player can level up
	@param nStatLevel - The specific stat's level
	@param nRuneCost - Cost for levelling
	@param nRunes - Player's possessesd runes
	@return VALID - Level is not max and rune cost is afforadble
			0 - Runes aren't enough
			-1 - Stat is maxed
*/
int checkLevelUp(const int nStatLevel, const int nRuneCost, const int nRunes){
	if (nRunes < nRuneCost){ return 0; }

	if (nStatLevel >= 50){ return -1; }

	return VALID;
}