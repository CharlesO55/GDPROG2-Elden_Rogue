void prompt(int nCode){
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
		default:
			printf("\n[ERROR]: Not in prompt options.");
	}
}