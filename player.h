#include <windows.h>
#include <time.h>

void PlayerInit();

/* 移动玩家 */
void PlayerMove(COORD direction);
void PlayerRandomLeap(COORD arenaSize);

/* GET/SET */
void PlayerGetPosition(COORD *position);
void PlayerSetPosition(COORD *position);

void PlayerSetLives(int n);
int  PlayerGetLives(void);

void PlayerSetScore(int score);
int  PlayerGetScore(void);

void PlayerSetLeaps(int leaps);
int  PlayerGetLeaps(void);

