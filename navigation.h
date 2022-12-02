#ifndef NAVIGATION_FILE
#define NAVIGATION_FILE

void getTitleScreen();
void getCharCreationScreen(Player* pPlayer);
void selectJobClass(JobClass *pPlayerJob);
void getRoundTable(Player* pPlayer);
void getLevelingMenu(Player* pPlayer);
	int calcRuneCost(const int nLevel);
	void levelUp(Player* pPlayer, const int nRuneCost, const int nChoice);
		int checkLevelUp(const int nStatLevel, const int nRuneCost, const int nRunes);

void getInventoryMenu(int* pInventory);
void getShopOpen(Player* pPlayer);
	void getShopBuyMenu(Player* pPlayer, Weapon* pAllWeapons);
		void getShopBuyWeapons(Weapon aWeapons[], const int nWeaponType);
#endif