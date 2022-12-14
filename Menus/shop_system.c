#include "shop_system.h"

/*Shop title page and redirects to buying/selling
	@param pPlayer - Contains player's runes and weapons 
*/
void getShopOpen(Player* pPlayer){
	int nChoice;
	Weapon* pAllWeapons = getAllWeapons();
	do{
		printShopOpening(pPlayer->strPlayerName, pPlayer->nRunes);
		scanIntChoice(&nChoice, 0, 2);

		switch(nChoice){
			case 1:
				//Buy weapons
				getShopBuyMenu(pPlayer, pAllWeapons);
				break;
			case 2:
				//Sell weapons
				getShopSellWeapons(pPlayer);
				break;
			case 0:
				prompt(1);
				break;
			default:
				prompt(102);
		}
	} while(nChoice);
	free(pAllWeapons);
}

	/*Allows players to pick a weapon category
		@param pPlayer - Contains player runes and weapon inventory
		@param pAllWeapons - All weapons available to scroll through
	*/
	void getShopBuyMenu(Player* pPlayer, Weapon* pAllWeapons){
			int nChoice;
			do{
				printShopBuyScreen(pPlayer->nRunes);
				scanIntChoice(&nChoice, 0, TOTAL_WEAPONS_TYPES);
				if(nChoice){
					getShopBuyWeapons(pPlayer, pAllWeapons+((nChoice-1)*TOTAL_WEAPONS_TYPES_CHOICES), nChoice);
				}
			} while(nChoice);
			prompt(1);
		}

			/*Buys and adds chosen weapon to inventory
				@param pPlayer - Contains player runes and weapon inventory
				@param aWeapons - Array of available weapons under that category
				@param nWeaponType - Use for determining weapon sprite
			*/
			void getShopBuyWeapons(Player* pPlayer, const Weapon aWeapons[], const int nWeaponType){
				int nChoice;
				do{
					printShopBuyWeapons(aWeapons, nWeaponType, pPlayer->nRunes);
					scanIntChoice(&nChoice, 0, TOTAL_WEAPONS_TYPES_CHOICES);
					
					if (nChoice != 0 && checkWeaponPurchase(*pPlayer, aWeapons[nChoice-1].nRuneCost, aWeapons[nChoice-1].nDexCost)){
						//setWeaponStats(pPlayer->sEquipment.pWeaponInventory+0, aWeapons[nChoice-1].nIdentifier);
						
						addWeapon(&(pPlayer->sEquipment), aWeapons[nChoice-1].nIdentifier);

						pPlayer->nRunes -= aWeapons[nChoice-1].nRuneCost;
						prompt(4);
					}
				}while(nChoice);
				prompt(1);
			}


				/*Check if player can purchase the weapon
					@param sPlayer - The player runes to read
					@param nRuneCost - The cost of the weapon
					@param nDexCost - Dexterity requirement of the weapon
					@return 0 - Unable to afford weapon
							1 - Can afford the weapon
				*/
				int checkWeaponPurchase(const Player sPlayer, const int nRuneCost, const int nDexCost){
					if (sPlayer.nRunes < nRuneCost){
						prompt(103);
						return 0;
					} /*	//DEXTERITY REQ NOT PART OF WEAPON PURCHASE
					if (sPlayer.sJob.nDexterity < nDexCost){
						prompt(105);
						return 0;
					}*/
					return 1;
				}

				/*Adds a weapon to player's inventory
					@param pEquipment - The player's weapons
					@param nIdentifier - The new weapon type to add
				*/
				void addWeapon(Equipment* pEquipment, const int nIdentifier){
					int i;
					//Expand dynamic array if already at limit
					if (pEquipment->nInventoryUsedSlots >= pEquipment->nInventoryCapacity){
						pEquipment->nInventoryCapacity += 4;
						pEquipment->pWeaponInventory = realloc(pEquipment->pWeaponInventory, (pEquipment->nInventoryCapacity * sizeof(Weapon)));
						
						//Set new slots to empty so we can detect them
						for(i = pEquipment->nInventoryCapacity - 4; i < pEquipment->nInventoryCapacity; i++){
							setWeaponStats(pEquipment->pWeaponInventory + i, EMPTY);
						}
					}

					int nSelected = findEmptySlot(pEquipment->pWeaponInventory, pEquipment->nInventoryCapacity);

					if (nSelected != -1){
						setWeaponStats(pEquipment->pWeaponInventory + nSelected, nIdentifier);
						pEquipment->nInventoryUsedSlots += 1;
						return;
					}
					prompt(106);
				}

				/*Finds an empty inventory slot
					@param pInventory - The inventory of weapons
					@param nElements - The size of the inventory
					@return i - Index for an available slot
							(-1) - No empty slot available
				*/
				int findEmptySlot(const Weapon* pInventory, const int nElements){
					int i = 1;	//Excluding first slot[0] for equipped items only
					while(i < nElements){
						if (pInventory[i].nIdentifier == EMPTY) 
							{printf("\nEMPTY FOUND\n"); return i;}
						i++;
					}
					//printf("\nno EMPTY FOUND\n");
					return -1;
				}


	/*Display possessed weapons and interpret actions to sell
		@param pPlayer - Contains player runes and weapons
	*/
	void getShopSellWeapons(Player* pPlayer){
			int nChoice;
			int nPage = 0;
			int nIndex;

			do{
				printShopSellScreen(pPlayer, nPage);
				scanIntChoice(&nChoice, 0, 6);
				switch(nChoice){
					case 1:
					case 2:
					case 3:
					case 4:
						nIndex = nChoice + nPage * 4;
						sellWeapon(pPlayer->sEquipment.pWeaponInventory+nIndex, &pPlayer->nRunes);
						break;
					case 5:
						if (nPage > 0){nPage--;}
						else {prompt(107);}
						break;
					case 6:
						if (nPage < (int)(pPlayer->sEquipment.nInventoryCapacity / 4)-1){nPage++;}
						else {prompt(107);}
						break;
					case 0:
						prompt(1);
						break;
					default:
						prompt(102);
				}
			} while (nChoice);
		}

			/*Sells the weapon.
				@param pWeapon - pWeapon to alter
				@param pRunes - Runes to alter
			*/
			void sellWeapon(Weapon* pWeapon, int* pRunes){
				if (pWeapon->nIdentifier == EMPTY)
					{prompt(108); return;}
				
				*pRunes += pWeapon->nRuneCost / 2;
				setWeaponStats(pWeapon, EMPTY);
				prompt(7);
			}