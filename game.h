#include <windows.h>
#include <stdio.h>

#include "conlib.h"
#include "player.h"
/* 枚举游戏状态 */
enum GameStatus
{
	GameMainMenu = 1,
	GameRunning,
	GamePaused,
	GameWon,
	GameLostLife,
	GameLost,
	GameExit,
	GameSplashScreen
};

/* 枚举游戏难度 */
enum GameDifficulty
{
	GameEasy = 1,
	GameMedium,
	GameDifficult
};

/* 初始化 */
void GameInit();

/* 显示相关信息 */
void ShowSplash(void);
void ShowMenu(void);
void ShowGame(void);
void ShowWon(void);
void ShowLostLife(void);
void ShowLost(void);
void ShowExit(void);
void Show(void);

/* 根据游戏状态处理游戏的情形变化 */
void ProcessSplash(void);
void ProcessMenu(void);
void ProcessGame(void);
void ProcessWon(void);
void ProcessLostLife(void);
void ProcessLost(void);
void ProcessExit(void);
void Process();

/* 游戏方法 */
void StartNewGame(int diffuculty);
void EndGame(void);
void CheckCollisions(void);
int GetAction(void);
int GetStatus(void);
void MoveMonsters(void);

void Load(void);
void Save(void);
