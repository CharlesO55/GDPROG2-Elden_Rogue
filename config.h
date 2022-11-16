#ifndef CONFIG_FILE
#define CONFIG_FILE

#define PLAYER_NAME_MAX_CHARS 25

typedef char string25[26];
typedef char string15[16];

#define TOTAL_CLASSES 6
#define TOTAL_WEAPONS_TYPES 6
#define TOTAL_WEAPONS_TYPES_CHOICES 4

typedef struct JobTag{
    string15 strJob;
    int nLevel;
    int nHealth, nEndurance, nDexterity, nStrength, nIntelligence, nFaith;
} JobClass;

JobClass* initJobClasses();
void setJobStats(JobClass *sJob, int nLVL, int nHP, int nEND, int nDEX, int nSTR, int nINT, int nFTH, string15 strJobName);
#endif