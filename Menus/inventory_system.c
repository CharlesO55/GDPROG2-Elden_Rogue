#include "inventory_system.h"
#include "shop_system.h"

void getInventoryMenu(Equipment* pEquipment, const int nDex){
	int nChoice;
	int nPage = 0;
	Weapon sTempWep;
	int nIndex;
	do {
											//1-4: 4 weapons inventory							//0: Equipped
		printInventoryScreen((pEquipment->pWeaponInventory+(nPage*4+1)), nPage, nDex, pEquipment->pWeaponInventory->strWeaponName);
		scanIntChoice(&nChoice, 0, 7);

		switch(nChoice){
			case 1:
			case 2:
			case 3:
			case 4:
						//1-4: 4 weapons in inventory
				nIndex = nPage*4 + nChoice;
				sTempWep = *(pEquipment->pWeaponInventory+(nIndex));
				
				if (sTempWep.nIdentifier == EMPTY){	prompt(108); break; }

				if (nDex >= sTempWep.nDexCost){	
					setWeaponStats((pEquipment->pWeaponInventory+(nIndex)), pEquipment->pWeaponInventory->nIdentifier);
					setWeaponStats(pEquipment->pWeaponInventory, sTempWep.nIdentifier);
					//*(pEquipment->pWeaponInventory) = sTempWep;
					prompt(5);
				}

				else{ prompt(110); }
				break;
			case 5:
				if (pEquipment->pWeaponInventory->nIdentifier != EMPTY){
					addWeapon(pEquipment, pEquipment->pWeaponInventory->nIdentifier);	//Readd the weapon to list
					setWeaponStats(pEquipment->pWeaponInventory, EMPTY);	//Reset to empty
					prompt(6);
				}
				else{ prompt(109); }
				break;
			case 6:
				if (nPage > 0){nPage--;}
				else {prompt(107);}
				break;
			case 7:
				if (nPage < (int)(pEquipment->nInventoryCapacity / 4)-1){nPage++;}
				else {prompt(107);}
				break;
			case 0:
				prompt(1);
				break;
			default:
				prompt(102);
			}
	} while(nChoice);	
}