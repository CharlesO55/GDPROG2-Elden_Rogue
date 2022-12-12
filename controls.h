#ifndef CONTROLS_FILE
#define CONTROLS_FILE

#define QUIT 0
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define INTERACT 5
#define FOUND 1
#define UNFOUND 0
#define VALID 1
#define INVALID 0
#define INVALID2 -1
#define EXIT 0

#define KILL_SWITCH 96	// ` symbol

void scanIntChoice(int *nChoice, int nMin, int nMax);
void scanPlayerControl(int* nAction);
void scanString(char *strInput, int nMaxLetters);

#endif