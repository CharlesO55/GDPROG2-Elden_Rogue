#include "navigation.h"
//HANDLES MENU NAVIGATION
#include "Menus/character_creation_system.c"
#include "Menus/levelling_system.c"
#include "Menus/inventory_system.c"
#include "Menus/shop_system.c"



/*	Opens Character creation menu, Load saves, and Returning to main()
*/
void getTitleScreen(){
	Player sPlayer;

	int nChoice;
	do {
		printTitleScreen();

		scanIntChoice(&nChoice, 0, 2);

		switch(nChoice){
			case 1:	//New game
				prompt(2);
				getCharCreationScreen(&sPlayer);
				break;
			case 2:	//Continue
				prompt(2);
				break;
			case 0:	//Exit
				prompt(0);
				return;
			default:
				prompt(102);
		}
	} while (nChoice);
}




void getRoundTable(Player* pPlayer){
	int nChoice = VALID;
	int nValid = INVALID;

	do {
		printRoundTableScreen(*pPlayer);
		scanIntChoice(&nChoice, 0, 5);
		switch(nChoice){
		case 1:	//Fast travel
			prompt(2);
			break;
		case 2:	//Level up
			prompt(2);
			getLevelingMenu(pPlayer);
			break;
		case 3:	//Inventory
			prompt(2);
			getInventoryMenu(&(pPlayer->sEquipment), pPlayer->sJob.nDexterity);
			break;
		case 4:	//Shop
			prompt(2);
			getShopOpen(pPlayer);
			break;
		case 5:	//Save
			prompt(2);
			break;
		case 0:	//Return to title
			prompt(1);
			nValid = VALID;
			break;
		default:
			prompt(102);
		}
	} while (!nValid);
}
