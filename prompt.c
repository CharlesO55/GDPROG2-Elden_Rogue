void prompt(int nCode){
	if (nCode >= 0 && nCode < 100){ printf(GREEN);}		//Success prompts
	else if (nCode >= 100 && nCode < 200){ printf(RED);}	//Switch to red font. Error prompts

	switch(nCode){
		case 0:
			printf("\n[SYSTEM]: Closing program...");
			break;
		case 1:
			printf("\n[SYSTEM]: Returning...");
			break;
		case 2:
			printf("\n[SYSTEM]: Opening next page...");
			break;
		case 3:
			printf("\n[SYSTEM]: Leveled up!");
			break;
		case 4:
			printf("\n[SYSTEM]: Bought new weapon!");
			break;
		case 5:
			printf("\n[SYSTEM]: Equipped weapon!");
			break;
		case 6:
			printf("\n[SYSTEM]: Unequipped weapon!");
			break;
		case 100:
			printf("\n[ERROR]: Enter a valid input.");
			break;
		case 101:
			printf("\n[ERROR]: Enter all needed information.");
			break;
		case 102:
			printf("\n[ERROR]: Not covered in switch cases.");
			break;
		case 103:
			printf("\n[ERROR]: Not enough runes.");
			break;
		case 104:
			printf("\n[ERROR]: Max level reached.");
			break;
		case 105:
			printf("\n[ERROR]: Dexterity requirement not met.");
			break;
		case 106:
			printf("\n[ERROR]: Add weapon failed.");
			break;
		case 107:
			printf("\n[ERROR]: No more pages.");
			break;
		case 108:
			printf("\n[ERROR]: Empty slot selected.");
			break;
		case 109:
			printf("\n[ERROR]: No weapon currently equipped.");
			break;
		case 110:
			printf("\n[ERROR]: Insufficient dexterity.");
			break;
		default:
			printf("\n[ERROR]: Not in prompt options.");
	}
	printf(COLOR_RESET);
}