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

void getInventoryMenu(Equipment* pEquipment, const int nDex);
void getShopOpen(Player* pPlayer);
	void getShopBuyMenu(Player* pPlayer, Weapon* pAllWeapons);
		void getShopBuyWeapons(Player* pPlayer, const Weapon aWeapons[], const int nWeaponType);
			int checkWeaponPurchase(const Player sPlayer, const int nRuneCost, const int nDexCost);
				void addWeapon(Equipment* pEquipment, const int nIdentifier);
					int findEmptySlot(const Weapon* pInventory, const int nElements);
#endif