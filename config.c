#include <time.h>
#include "config.h"

void startUp(){
	srand(time(NULL));
}

int generateRNG(int nMin, int nMax){
	int nNum = rand() % (nMax + 1 - nMin) + nMin;
	return nNum;
}