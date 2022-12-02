#ifndef SCREEN_FILE
#define SCREEN_FILE

#define BARS_WIDTH 35

#define SPACE_SYMBOL 0
#define BAR_SYMBOL 1

#include "navigation.h"

void printTitleScreen();
void printCharCreationScreen(const string25 strName, const int nLevel, const string25 strClass);
void printJobSelectorScreen(const JobClass sJob);
int calcDigits(int nNum);
void printSpaces(const int nSpaces);
void printSymbols(const int nAmount, const int nSymbol);
void printRoundTableScreen(const Player sPlayer);
	void printShards(const int aShards[MAX_SHARDS]);

	void printLevelingScreen(const Player sPlayer, const int nRuneCost);


	void printInventoryScreen(int* pInventory, int nPage);

	void printShopOpening(const string25 strName, const int nRunes);
		void printShopBuyScreen(const int nRunes);
			void printShopBuyWeapons(const Weapon aWeapons[], const int nWeaponType);
				void displayWeapons(const Weapon aWeapons[]);


void printHeader(const stringMax strName);
void printStatLine(const int nNum, const char strText[]);
void fillText(char string[], const int nSize);
#endif