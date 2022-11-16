void prompt(int nCode){
	switch(nCode){
		case 0:
			printf("\n[SYSTEM]: Closing program...");
			break;
		case 1:
			printf("\n[SYSTEM]: Returning...");
			break;
		case 100:
			printf("\n[ERROR]: Enter a valid input.");
			break;
		case 102:
			printf("\n[ERROR]: Not covered in switch cases.");
			break;
		default:
			printf("\n[ERROR]: Not in prompt options.");
	}
}