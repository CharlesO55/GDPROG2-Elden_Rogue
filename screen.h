#ifndef SCREEN_FILE
#define SCREEN_FILE

#define BARS_WIDTH 35

#define SPACE_SYMBOL 0
#define BAR_SYMBOL 1
//#define SHARD_SYMBOL 2
//#define EMPTY_SHARD_SYMBOL 3

void printTitleScreen();
void printCharCreationScreen(string25 strName, int nLevel, string25 strClass);
void printJobSelectorScreen(JobClass *sJob);
int calcDigits(int nNum);
void printSpaces(int nSpaces);
void printSymbols(int nAmount, int nSymbol);
void printRoundTableScreen(Player sPlayer);
	void printShards(int aShards[MAX_SHARDS]);

	void printLevelingScreen(Player sPlayer, int nRuneCost);

#endif