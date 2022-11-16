#ifndef SCREEN_FILE
#define SCREEN_FILE

#define BARS_WIDTH 35
#define BARS 1

void printTitleScreen();
void printCharCreationScreen(string25 strName, int nLevel, string25 strClass);
void printJobSelectorScreen(JobClass *sJob);
int calcDigits(int nNum);
void printSpaces(int nSpaces);
void printSymbols(int nSymbols);
void printRoundTableScreen(JobClass pJob);

#endif