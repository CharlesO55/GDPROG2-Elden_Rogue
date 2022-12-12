#ifndef CONFIG_FILE
#define CONFIG_FILE

#define PLAYER_NAME_MAX_CHARS 25
#define MAX_LEVEL 50
#define NUMBER_OF_STATS 6
#define MAX_SHARDS 6

#define TOTAL_CLASSES 6
#define TOTAL_WEAPONS_TYPES 6
#define TOTAL_WEAPONS_TYPES_CHOICES 4
#define WEAPON_ICON_WIDTH 12

#define STARTER_RUNES 20000

typedef char stringMax[100+1];
typedef char string25[PLAYER_NAME_MAX_CHARS+1];
typedef char string10[11];

#define RED 		"\e[0;31m"
#define GREEN 		"\e[0;32m"
#define YELLOW 		"\e[0;33m"
#define BLUE 		"\e[1;34m"	
#define UWHITE 		"\e[4;37m"
#define GRAY 		"\e[1;30m"
#define COLOR_RESET "\e[0m"


#define SWORD 1
#define KATANA 2
#define WHIP 3
#define GREATSWORD 4
#define STAFF 5
#define SEAL 6

#define EMPTY -1

#define STARTING_INVENTORY_SIZE 5
//STRUCTS INIT STATS
string10 CONFIG_JobName[TOTAL_CLASSES] = {
	"VAGABOND", "SAMURAI", "WARRIOR", "HERO", "ASTROLOGER", "PROPHET"
};

int CONFIG_JobStats[TOTAL_CLASSES][NUMBER_OF_STATS + 1] = {
	//LVL, HP, END, DXT, STR, INT, FTH;
	{9, 15, 11, 13, 14, 9, 9},	//Vagabond
	{9, 12, 13, 15, 12, 9, 8},	//Samurai
	{8, 11, 11, 16, 10, 10, 8},	//Warrior
	{7, 14, 12, 9, 16, 7, 8},	//Hero
	{6, 9, 9, 12, 8, 16, 7},	//Astrologer
	{7, 10, 8, 10, 11, 7, 16}	//Prophet
};


string25 CONFIG_WeaponTypes[TOTAL_WEAPONS_TYPES] = {
	"SWORD", "KATANA", "WHIP", "GREATSWORD", "STAFF", "SEAL"
};
//WEAPON INIT STATS
string25 CONFIG_WeaponName[TOTAL_WEAPONS_TYPES][TOTAL_WEAPONS_TYPES_CHOICES] = {
	{"SHORT SWORD", "ROGIER'S RAPIER", "CODED SWORD", "SWORD OF NIGHT AND FLAME"},
	{"UCHIGATANA", "MOONVEIL", "RIVERS OF BLOOD", "HAND OF MALENIA"},
	{"WHIP", "URUMI", "THORNED WHIP", "HOSLOW'S PETAL WHIP"},
	{"CLAYMORE", "STARSCOURGE GREATSWORD", "INSEPERABLE SWORD", "MALIKETH'S BLACK BLADE"},
	{"ASTROLOGER'S STAFF", "ALBINAURIC STAFF", "STAFF OF THE GUILTY", "CARIAN REGAL SCEPTER"},
	{"FINGER SEAL", "GODSLAYER'S SEAL", "GOLDEN ORDER SEAL", "DRAGON COMMUNION SEAL"}
};
/*
int CONFIG_WeaponIdentifier[TOTAL_WEAPONS_TYPES][TOTAL_WEAPONS_TYPES_CHOICES] = {
	{1, 2, 3, 4},		//Swords
	{5, 6, 7, 8},		//Katana
	{9, 10, 11, 12},	//Whip
	{13, 14, 15, 16},	//Greatswords
	{17, 18, 19, 20},	//Staves
	{21, 22, 23, 24}	//Seals
};*/

int CONFIG_WeaponRuneCost[TOTAL_WEAPONS_TYPES][TOTAL_WEAPONS_TYPES_CHOICES] = {
	{1000, 2000, 4000, 8000},	//Swords
	{1875, 3750, 7500, 15000},	//Katana
	{1500, 3000, 5000, 10000},	//Whip
	{3000, 6000, 12000, 24000},	//Greatswords
	{2000, 4000, 8000, 16000},	//Staves
	{2500, 5000, 10000, 15000}	//Seals
};

int CONFIG_WeaponDexterityReq[TOTAL_WEAPONS_TYPES][TOTAL_WEAPONS_TYPES_CHOICES] = {
	{13, 18, 21, 25},	//Swords
	{15, 20, 25, 30},	//Katana
	{20, 25, 30, 35},	//Whip
	{9, 14, 19, 24},	//Greatswords
	{12, 14, 16, 18},	//Staves
	{10, 12 ,14, 18}	//Seals
};

int CONFIG_WeaponStats[TOTAL_WEAPONS_TYPES][TOTAL_WEAPONS_TYPES_CHOICES][NUMBER_OF_STATS] = {
		//HP, END, DXT, STR, INT, FTH
	{	{0, 15, 0, 15, 15, 15},	{10, 25, 0, 35, 35, 35}, {20, 35, 0, 40, 40, 40}, {30, 45, 0, 55, 55, 55}	},	//Swords
	{	{20, 35, 0, 30, 0, 0},	{30, 40, 0, 45, 0, 0},	 {40, 45, 0, 60, 0, 0},	  {50, 50, 0, 75, 0, 0}  	},	//Katana
	{	{15, 60, 0, 20, 0, 0},	{20, 70, 0, 40, 10, 0},	 {30, 80, 0, 50, 0, 40},  {35, 90, 0, 55, 20, 20}	},	//Whip
	{	{15, 10, 0, 20, 0, 0},	{20, 15, 0, 40, 0, 20},	 {25, 20, 0, 70, 60, 60}, {30, 25, 0, 80, 40, 60}	},	//Greatswords
	{	{5, 20, 0, 5, 25, 15},	{10, 30, 0, 10, 45, 35}, {15, 40, 0, 15, 65, 60}, {25, 50, 0, 20, 85, 75}	},	//Staves
	{	{10, 45, 0, 0, 15, 20}, {15, 50, 0, 0, 35, 40},	 {20, 55, 0, 0, 65, 65},  {25, 60, 0, 0, 75, 80}	}	//Seals
};


string25 CONFIG_ShopDialogue[] = {
	"How's the weather today?",
	"More wares comin' soon.",
	"Fancy yeself a blade?",
	"Oh, it's you again.",
	"٭(•﹏•)٭" ,
	"(˵¯͒〰¯͒˵)",
	"╰(▔∀▔)╯",
	"(￣个￣)",
	"(◕ っ ◕✿)",
	"ᕙ(‾̀◡‾́)ᕗ"
};


//FUNCTIONS
void startUp();
int generateRNG(int nMin, int nMax);
#endif