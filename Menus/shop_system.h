#ifndef SHOP_SYSTEM_FILE
#define SHOP_SYSTEM_FILE

void getShopOpen(Player* pPlayer);
	void getShopBuyMenu(Player* pPlayer, Weapon* pAllWeapons);
			void getShopBuyWeapons(Player* pPlayer, const Weapon aWeapons[], const int nWeaponType);
				int checkWeaponPurchase(const Player sPlayer, const int nRuneCost, const int nDexCost);
					void addWeapon(Equipment* pEquipment, const int nIdentifier);
						int findEmptySlot(const Weapon* pInventory, const int nElements);
					
	void getShopSellWeapons(Player* pPlayer);
		void sellWeapon(Weapon* pWeapon, int* pRunes);


#endif