Every known bug and cause:

1. Game will crash when freeing pHead of area floors
2. Game will crash when pHead is existing and assigned to a new floor array
3. Initializing floor arrays can crash. Cause is unknown. (Area 0 & 1 work fine)
4. Change floors is not persistent. The floor changes in the function but doesn't persist when changeFloors function ends
5. None of the save/load functions work. Not implemented within time

Other stuff
1. Dodge rate calcultation from MP specs doesn't seem to be correct. Told to randomly generate int from 1-100 but dodge rate calc is a decimal. (Dodge rate will always fail)
2. Tiles were altered in floors 0 of Area 0,1,& 5 for debugging purposes only


Useful tools:
[CONFIG.h] IS_AREA_4_UNLOCKED - Will unlock LEYNDELL ROYAL CAPITAL (floor generation is still busted)
[CONFIG.h] IS_AREA_5_UNLOCKED - Will unlock THE ELDEN THRONE

` KEY will call exit() to close the program. Not used in any function. Just for escaping since pressing 0 is hassle and getting trapped in battle loop may exist.