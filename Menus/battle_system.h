#ifndef BATTLE_SYSTEM_FILE
#define BATTLE_SYSTEM_FILE


void startBattle(Enemy* pEnemy, Player* pPlayer, Area* pFloor);
int calcDamage(const Enemy* pEnemy, const int nArea);

int calcMaxHealth(const Player* pPlayer);
int useDodge(const Player* pPlayer);
int usePotion(Player* pPlayer);
void takeDamage(Player* pPlayer, const int nDmg);

void printBattleScreen(const Enemy* pEnemy, const Player* pPlayer, const Area* pFloor);
void printBattleChoices(const int nDmg, const int nPotions);

int isGameOver(Player* pPlayer, const Enemy* pEnemy);
#endif