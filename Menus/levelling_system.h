#ifndef LEVELLING_SYSTEM
#define LEVELLING_SYSTEM

void getLevelingMenu(Player* pPlayer);
	int calcRuneCost(const int nLevel);
	void levelUp(Player* pPlayer, const int nRuneCost, const int nChoice);
		int checkLevelUp(const int nStatLevel, const int nRuneCost, const int nRunes);
		
#endif