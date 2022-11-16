#ifndef CONTROLS_FILE
#define CONTROLS_FILE

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define INTERACT 5
#define FOUND 1
#define UNFOUND 0
#define VALID 1
#define INVALID 0
#define EXIT 0

void scanIntChoice(int *nChoice, int nMin, int nMax);
void playerMovement(int* nAction);
void scanString(char *strInput, int nMaxLetters);

#endif