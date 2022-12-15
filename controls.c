#include "controls.h"


/*Scans integer inputs
    @param pChoice - The player's chosen int
*/
void scanIntChoice(int *pChoice, int nMin, int nMax){
    int nValid = INVALID;
    char strInput[100];

    while(!nValid){
        printf("\n[INPUT]: ");
        scanf(" %s", strInput);

        //DEBUG ONLY
        if(strInput[0] == KILL_SWITCH)
            {prompt(0); exit(1);}


        if (strlen(strInput) == 1 && strInput[0]-48 >= nMin  && strInput[0]-48 <= nMax){    //If single input and is in int range
            nValid = VALID;
            *pChoice = strInput[0] - 48;
        } 
        else{
            prompt(100);
        }
    }
}

/*Scan's user input with spaces included
    @param strOutput - String to output matcthing the req size
    @param nMaxLetters - The number of letters allowed
*/
void scanString(char *strOutput, int nMaxLetters){
    char strInput[100]; //Store whatever player types
    scanf(" %[^\n]s", strInput);

    strncpy(strOutput, strInput, nMaxLetters);
    strOutput[nMaxLetters] = '\0';
}


/*Scan player charcter inputs for controls
    @param nAction - Player's chosen action
*/
void scanPlayerControl(int* nAction){
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
            case 'q':
            case 'Q':
                *nAction = QUIT;
                nValid = VALID;
                break;
            case '[':
                *nAction = DEBUG_CONTROL_0;
                nValid = VALID;
                break;
            case ']':
                *nAction = DEBUG_CONTROL_1;
                nValid = VALID;
                break;
            case '`':
                prompt(0);
                exit(1);
            default:
                prompt(100);
            }
        }
}
