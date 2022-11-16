#include "controls.h"

void scanIntChoice(int *nChoice, int nMin, int nMax){
    int nValid = INVALID;
    char strInput[100];

    while(!nValid){
        printf("\n[INPUT]: ");
        scanf(" %s", strInput);

        if (strlen(strInput) == 1 && strInput[0]-48 >= nMin  && strInput[0]-48 <= nMax){    //If single input and is in int range
            nValid = VALID;
            *nChoice = strInput[0] - 48;    //Convert from ascii char to int. Typecasting doesn't work \'_'/
        } 
        else{
            prompt(100);
        }
    }
}

void scanString(char *strOutput, int nMaxLetters){
    char strInput[100]; //Store whatever player types
    scanf(" %[^\n]s", strInput);

    strncpy(strOutput, strInput, nMaxLetters);
    strOutput[nMaxLetters] = '\0';
}

void playerMovement(int* nAction){
    char cInput;
    int nValid = INVALID;

    while(!nValid){
        printf("\n[INPUT]: ");
        scanf(" %c", &cInput);

        switch(cInput){
            case 'w':
            case 'W':
                *nAction = UP;
                nValid = VALID;
                break;
            case 's':
            case 'S':
                *nAction = DOWN;
                nValid = VALID;
                break;
            case 'd':
            case 'D':
                *nAction = RIGHT;
                nValid = VALID;
                break;
            case 'a':
            case 'A':
                *nAction = LEFT;
                nValid = VALID;
                break;
            case 'e':
            case 'E':
                *nAction = INTERACT;
                nValid = VALID;
                break;
            default:
                prompt(100);
                //printf("\n[ERROR]: ENTER A VALID VALUE");
            }
        }
}
