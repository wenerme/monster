#include <windows.h>
#include <time.h>
#include "player.h"

static COORD cdPosition;
static int iLives;
static int iScore;
static int iLeaps;

void PlayerInit()
{
}

/* 移动玩家 */
void PlayerMove(COORD direction)
{
	cdPosition.X += direction.X;
	cdPosition.Y += direction.Y;
}
void PlayerRandomLeap(COORD arenaSize)
{
	srand(time(NULL));

	cdPosition.X = (rand() % (arenaSize.X - 1) + 1);
	cdPosition.Y = (rand() % (arenaSize.Y - 1) + 1);
}

/* GET/SET */
void PlayerGetPosition(COORD *position)
{
	memcpy(position, &cdPosition, sizeof(COORD));
}
void PlayerSetPosition(COORD *position)
{
	memcpy(&cdPosition, position, sizeof(COORD));
}

void PlayerSetLives(int n)
{
	iLives = n;
}
int  PlayerGetLives(void)
{
	return iLives;
}

void PlayerSetScore(int score)
{
	iScore = score;
}
int  PlayerGetScore(void)
{
	return iScore;
}

void PlayerSetLeaps(int leaps)
{
	iLeaps = leaps;
}
int  PlayerGetLeaps(void)
{
	return iLeaps;
}

