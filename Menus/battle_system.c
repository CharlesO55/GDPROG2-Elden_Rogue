#include "battle_system.h"
#include "Configurations/enemy_stats.h"

/*Initializes the battle loop and handles player's actions
	@param pEnemy - The enemy stats
	@param pPlayer - The player stats
	@param pFloor - The current floor
	@return 1 - Player won
			0 - Player lost
*/
int startBattle(Enemy* pEnemy, Player* pPlayer, Area* pFloor){
	int nDmg;
	int nDodged;

	do {
		nDmg = calcDamage(pEnemy, pFloor->nArea);
		printBattleScreen(pEnemy, pPlayer, pFloor);
		printBattleChoices(nDmg, pPlayer->sEquipment.nPotions);
		
		getPlayerTurn(pPlayer, pEnemy, &nDodged);

		if (isGameOver(pPlayer, pEnemy))
			{break;}
		
		takeDamage(pPlayer, nDmg);
		nDodged = INVALID;
	} while(!isGameOver(pPlayer, pEnemy));

	return calcResults(pPlayer, pEnemy, pFloor->nArea);
}


int calcResults(Player* pPlayer, Enemy* pEnemy, const int nArea){
	if (pPlayer->nCurHP <= 0){
		pPlayer->nRunes = 0;
		printf(RED); printf("\n[RESULT] YOU DIED.\nLOST ALL RUNES"); printf(COLOR_RESET);
		return 0;	//LOST
	}

	if(pEnemy->nType < BOSS){
		pPlayer->nRunes += pEnemy->nHP * 2;
		printf(GREEN); printf("\n[RESULT] ENEMY FELLED\n[REWARD] %d RUNES EARNED", pEnemy->nHP * 2); printf(COLOR_RESET);
	}
	/*else if (){

	}*/
	else{
		pPlayer->nRunes += pEnemy->nHP * 5;
		printf(GREEN); printf("\n[RESULT] GREAT ENEMY FELLED\n[REWARD]%d RUNES EARNED", pEnemy->nHP * 5); printf(COLOR_RESET);
		pPlayer->aShards[nArea] = VALID;
	}

	return 1;		//WON
}

/*Interpretate action for dodging, healing, attacking
	@param pPlayer - Player stats
	@param pEnemy - Enemy stats
	@param pDodge - Dodge success
*/
void getPlayerTurn(Player* pPlayer, Enemy* pEnemy, int* pDodged){
	int nChoice;
	int nEndTurn = INVALID;
	do {
		scanIntChoice(&nChoice, 1, 3);

		switch(nChoice){
			case 1:
				useAttack(pPlayer, pEnemy);
				nEndTurn = VALID;
				break;
			case 2:
				*pDodged = useDodge(pPlayer);
				nEndTurn = VALID;
				break;
			case 3:
				usePotion(pPlayer);
				break;
			default:
				prompt(102);
		}
	} while (!nEndTurn);
}

/*Determines which attack type is used and calculate the dmg dealt to enemy
	@param pPlayer - Player stats and weapon
	@param pEnemy - Enemy health and defense stats
*/
void useAttack(Player* pPlayer, Enemy* pEnemy){
	int nChoice;
	int nAtk;
	printAttackChoices();
	scanIntChoice(&nChoice, 1, 3);
	string25 strType[3] = {"PHYSICAL", "SORCERY", "INCANTATION"};

	switch(nChoice){
		case 1: 	//Strength based physical
		case 2: 	//Intelligence based sorcery
		case 3:		//Faith based incantation
			nAtk = calcAttack(*(pPlayer->sJob.pStats[nChoice + 3]), 
							  pPlayer->sEquipment.pWeaponInventory->aStats[nChoice + 2], 
							  pEnemy->aDefenses[nChoice-1]);
			damageEnemy(pEnemy, nAtk);
			printf(GREEN); printf("\n[ATTACK] DEALT %d %s DAMAGE", nAtk, strType[nChoice-1]); printf(COLOR_RESET);
			break;
		default:
			prompt(102);
	}
}

/*Calculate amount of atk player will do
	@param nPlayerStat - Player's job stat related to dmg type
	@param nWeaponStat - Weapon's stat related to dmg type
	@param fEnemyDefense - Enemy defense stat related to dmg type
	@return nAtk - Amount of atk player will deal
*/
int calcAttack(const int nPlayerStat, const int nWeaponStat, const float fEnemyDefense){
	int nAtk = (nPlayerStat + nWeaponStat) * (1.0 - fEnemyDefense);
	printf("player(%d) + weapon(%d) * defense(%.2f)", nPlayerStat, nWeaponStat, fEnemyDefense);
	return nAtk;
}

/*Reduce enemy health
	@param pEnemy - Contains enemy health
	@param nAtk - Amount of damage dealt
*/
void damageEnemy(Enemy* pEnemy, const int nAtk){
	pEnemy->nCurHP -= nAtk;
	if (pEnemy->nCurHP < 0)
		{pEnemy->nCurHP = 0;}
}

void printAttackChoices(){
	printf("\n  "); printf(UWHITE); printf("ATTACK:"); printf(COLOR_RESET);
	printf("\n\t1. PHYSICAL");
	printf("\n\t2. SORCERY");
	printf("\n\t3. INCANTATION");
}


/*Returns damage enemy will do
	@param pEnemy - Contains enemy type and atk rng range
	@param nArea - The current area number (increment by 1 needed)
	@return nDmg - Damage enemy will deal
*/
int calcDamage(const Enemy* pEnemy, const int nArea){
	int nDmg = generateRNG(pEnemy->aAtkRange[0], pEnemy->aAtkRange[1]);
	
	if (pEnemy->nType != BOSS)
		{nDmg *= (nArea + 1);}

	return nDmg;
}


/*Subtracts the player's health
	@param pPlayer - Contains player's health
	@param nDmg - Damage to receive
*/
void takeDamage(Player* pPlayer, const int nDmg){
	pPlayer->nCurHP -= nDmg;
	if (pPlayer->nCurHP < 0)
		{pPlayer->nCurHP = 0;}

	printf("\n[DAMAGE] RECEIVED %d DMG!", nDmg);
}


/*Calculates if dodge was succesful
	@param pPlayer - Player's endurance values
	@return VALID - Successfully dodged
			INVALID - Failed to dodge
*/
int useDodge(const Player* pPlayer){
	float fDodge = ((pPlayer->sJob.nEndurance + pPlayer->sEquipment.pWeaponInventory->aStats[1]) / 2.0 + 20) / 100;
	float fRNG = (float)generateRNG(1, 100);

	if (fRNG <= fDodge){
		printf("\n[DODGE] %.2f vs %.2f SUCCESFULLY DODGED!", fDodge, fRNG);
		return VALID;
	}
	else{
		printf("\n[DODGE] %.2f vs %.2f DODGE FAILED!", fDodge, fRNG);
		return INVALID;
	}
}

/*Calculates player's max health
	@param pPlayer - Contains player HP stats
	@return nMax - Player max hp
*/
int calcMaxHealth(const Player* pPlayer){
	int nMax = 100 * ((pPlayer->sJob.nHealth + pPlayer->sEquipment.pWeaponInventory->aStats[0]) / 2);
	return nMax;
}

/*Player uses a potion to restore health if applicable
	@param pPlayer - The player's health and potions are in here
	@return VALID - Healed successfuly 
	     OR INVALID - Unable to heal
*/
int usePotion(Player* pPlayer){
	if (pPlayer->sEquipment.nPotions <= 0)
		{prompt(116); return INVALID;}
	pPlayer->sEquipment.nPotions -= 1;

	int nMax = calcMaxHealth(pPlayer);

	int nRestore = (int)(nMax * (generateRNG(25, 50) / 100.0));
	pPlayer->nCurHP += nRestore;

	if(pPlayer->nCurHP > nMax)
		{ pPlayer->nCurHP = nMax; }
	printf("\n[BATTLE] RESTORED %d HP! %d POTIONS REMAINING.", nRestore, pPlayer->sEquipment.nPotions);
	return VALID;
}

/*Checks if player or enemy is dead and update runes
	@param pPlayer - The player. Also contains their runes
	@param pEnemy - The enemy. Reads their health
	@return VALID (DEFEATED/VICTORY)
	@return INVALID (STILL ALIVE)
*/
int isGameOver(Player* pPlayer, const Enemy* pEnemy){
	if (pPlayer->nCurHP <= 0 || pEnemy->nCurHP <= 0)
		{ return VALID; }

	return INVALID;
}


/*Prints the battle screen
	@pEnemy - The enemy's stats
	@pPlayer - The player's stats
	@pFloor - The current floor
*/
void printBattleScreen(const Enemy* pEnemy, const Player* pPlayer, const Area* pFloor){
	printf("\n\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);
	printf("\n  ▮ "); printf(UWHITE); printf("%s %d-%d", pFloor->strAreaName, pFloor->nArea, pFloor->nFloor); printf(COLOR_RESET); printSymbols(BARS_WIDTH - (int)strlen(pFloor->strAreaName) - 8, SPACE_SYMBOL); printf(" ▮");
	printf("\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL);

	int i;
	for (i = 0; i < 5; i++){
		printf("\n  ▮ "); printf("%s", TEMP_PLAYER_SPRITE[i]); 
		   printf(" ▮ "); printf(pEnemy->aSprites[i]); printf(" ▮");
	}

	for (i = 0; i < 3; i++){
		printf("\n  ▮ "); printf("%s", splitText(pPlayer->strPlayerName, LETTERS_PER_LINE, i)); printf(" ▮ "); 
						   printf("%s", splitText(pEnemy->strEnemyName, LETTERS_PER_LINE, i)); printf(" ▮");
	}
	int nMaxHP = calcMaxHealth(pPlayer);
	printf("\n  ▮ "); printf("HP: %d / %d", pPlayer->nCurHP, nMaxHP); printSymbols(LETTERS_PER_LINE - 7 - calcDigits(pPlayer->nCurHP) - calcDigits(nMaxHP), SPACE_SYMBOL); printf(" ▮ "); 
		printf("HP: %d / %d", pEnemy->nCurHP, pEnemy->nHP); printSymbols(LETTERS_PER_LINE - 7 - calcDigits(pEnemy->nCurHP) - calcDigits(pEnemy->nHP), SPACE_SYMBOL); printf(" ▮");
	printf("\n  ▮   "); printHealthBar(nMaxHP, pPlayer->nCurHP); printf("   ▮   "); 
		printHealthBar(pEnemy->nHP, pEnemy->nCurHP); printf("   ▮");
	printf("\n  "); printSymbols(BARS_WIDTH, BAR_SYMBOL); printf("\n");
}


/*Prints the healthbar
	@param nMaxHP - The max hp
	@param nCurHP - Current hp
*/
void printHealthBar(const int nMaxHP, const int nCurHP){
	float fPartitions = nMaxHP / 10.0;
	int i;

	for(i = 1; i <= 10; i++){
		if ((fPartitions * i) - 1 < nCurHP)
			{ printf("●"); }
		else
			{ printf("○"); }
	}
}


/*Prints the player's choices
	@param nDmg - Damage enemy will do
	@param nPotions - Number of potions player has
*/
void printBattleChoices(const int nDmg, const int nPotions){
	printf("\n  INCOMING DAMAGE: %d", nDmg);
	printf("\n\t1. ATTACK");
	printf("\n\t2. DODGE");
	printf("\n\t3. DRINK POTION (%d/8)", nPotions);
}


/*Returns splitted text
	@param strInput - The source
	@param nLetterPerLine - The number of letters in a string
	@param nLineNumber - The index of the current line
	@return strOutput - Persistent String to return
*/
char* splitText(const char strInput[], const int nLettersPerLine, const int nLineNumber){
	char* strOutput = malloc(sizeof(char)*nLettersPerLine + 1);

	if((int)strlen(strInput) >= nLettersPerLine*nLineNumber){
		strncpy(strOutput, strInput+(nLettersPerLine*nLineNumber), nLettersPerLine); 
		strOutput[nLettersPerLine] = '\0';
	}
	else{
		strOutput[0] = '\0';
	}

	
	while((int)strlen(strOutput) < nLettersPerLine){
		strcat(strOutput, " ");
	}
	return strOutput;
}