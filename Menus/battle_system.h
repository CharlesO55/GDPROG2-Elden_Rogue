#ifndef BATTLE_SYSTEM_FILE
#define BATTLE_SYSTEM_FILE


int startBattle(Enemy* pEnemy, Player* pPlayer, Area* pFloor);
	int calcDamage(const Enemy* pEnemy, const int nArea);
		void getPlayerTurn(Player* pPlayer, Enemy* pEnemy, int* pDodged, int isFlinch[3]);
		//void getPlayerTurn(Player* pPlayer, Enemy* pEnemy, int* pDodged);
			void printAttackChoices();
			void useAttack(Player* pPlayer, Enemy* pEnemy, int isFlinch[3]);
			//void useAttack(Player* pPlayer, Enemy* pEnemy);
				int calcAttack(const int nPlayerStat, const int nWeaponStat, const float fEnemyDefense);
					void damageEnemy(Enemy* pEnemy, const int nAtk);
			int useDodge(const Player* pPlayer);
			int usePotion(Player* pPlayer);
				int calcMaxHealth(const Player* pPlayer);
	void takeDamage(Player* pPlayer, const int nDmg);


int isGameOver(Player* pPlayer, const Enemy* pEnemy);
int calcResults(Player* pPlayer, Enemy* pEnemy, const int nArea);

void printBattleScreen(const Enemy* pEnemy, const Player* pPlayer, const Area* pFloor);
void printBattleChoices(const int nDmg, const int nPotions);

void printHealthBar(const int nMaxHP, const int nCurHP);
char* splitText(const char strInput[], const int nLettersPerLine, const int nLineNumber);





#endif