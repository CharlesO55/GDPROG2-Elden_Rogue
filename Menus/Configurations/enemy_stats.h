#ifndef ENEMY_STATS_FILE
#define ENEMY_STATS_FILE

#define ENEMY_TYPES 3
#define BOSS 4

string25 aCOMMON_NAMES[6][ENEMY_TYPES] = {
	{"Godrick Soldier", "Godrick Archer", "Godrick Knight"},
	{"Living Jar", "Glinstone Sorcerer", "Battlemage"},
	{"Radahn Soldier", "Radahn Archer", "Radahn Knight"},
	{"Man-Serpent", "Mage-Serpent", "Abductor Virgin"},
	{"Leyndell Soldier", "Leyndell Archer", "Leyndell Knight"},
	{"", "", ""}
};

string25 aCOMMON_SPRITES[3] = {
	"   ▣ ",
	" ↙▥↘ ",
	" ▥ ▥ "
};

int aCOMMON_HP_RANGE[ENEMY_TYPES][2] = {
	{20, 30},
	{25, 35},
	{70, 80}
};

int aCOMMON_ATK_RANGE[ENEMY_TYPES][2] = {
	{70, 80},
	{110, 120},
	{120, 130}
};

float aCOMMON_DEFENSES[ENEMY_TYPES][3] = {
	{0.20, 0.15, 0.10},
	{0.50, 0.15, 0.20},
	{0.25, 0.25, 0.20}
};

#endif