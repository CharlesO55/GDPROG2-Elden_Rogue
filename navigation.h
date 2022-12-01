#ifndef NAVIGATION_FILE
#define NAVIGATION_FILE

void getTitleScreen();
void getCharCreationScreen(Player* pPlayer);
void selectJobClass(JobClass *pPlayerJob);
void getRoundTable(Player* pPlayer);
void getLevelingMenu(Player* pPlayer);
	int calcRuneCost(int nLevel);
	void levelUp(Player* pPlayer, int nRuneCost, int nChoice);
		int checkLevelUp(int nStatLevel, int nRuneCost, int nRunes);

#endif