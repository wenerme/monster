#include "game.h"

/* 局部变量 */
static int iLastAction;

// 游戏信息
static enum GameStatus iGameStatus;
static COORD cdArena;
static COORD* cdpMonsters;
static int iMonstersNumber;

/* 初始化 */
void GameInit()
{
	/* 设置初始值 */
	iGameStatus = GameSplashScreen;
	iLastAction = 0;
	cdpMonsters = NULL;
}

/* 显示相关信息 */
void ShowSplash(void)
{
	ConClear();
	ConOutputString("\t小怪兽 v 1.0\n\n");
	ConOutputString("\t一个异常简单的小游戏咯！\n\n");
	ConOutputString("游戏目标为消灭所有小怪兽，当两个\n");
	ConOutputString("小怪兽进入到一个区域时，两个都被\n");
	ConOutputString("消灭，当你和小怪兽同时进入一个区\n");
	ConOutputString("域时，怪兽被消灭，你被降低一滴血\n");
	ConOutputString("用小键盘的8个键进行移动，也可以\n");
	ConOutputString("按 INSERT 键来进行随机的跳跃\n\n");

	ConSetTextColor(ConRed);
	ConOutputString("注意:确认 NUMLOCK 是关闭的\n\n");

	ConSetTextColor(ConWhite);
	ConOutputString("有以下难度可供选择:\n\n");
	ConOutputString("简单:	怪兽数 = 10 区域 = 25*15\n");
	ConOutputString("		生命数 = 4  跳跃数 = 3\n");
	ConOutputString("普通:	怪兽数 = 20 区域 = 35*18\n");
	ConOutputString("		生命数 = 3  跳跃数 = 2\n");
	ConOutputString("困难:	怪兽数 = 30 区域 = 50*23\n");
	ConOutputString("		生命数 = 2  跳跃数 = 1\n");
}
void ShowMenu(void)
{
	ConSetBackgroundColor(ConBlack);
	ConSetTextColor(ConRed);
	ConClear();

	ConSetBackgroundColor(ConWhite);

	ConOutputString("\n");
	ConOutputString("小怪兽 - version 1.0\n");
	
	ConSetBackgroundColor(ConBlack);
	ConSetTextColor(ConWhite);

	ConSetPosition(1, 4);
	ConOutputString("你想干嘛！！！");

	ConSetPosition(3, 6);
	ConOutputString("1 - 开始游戏 - 简单");

	ConSetPosition(3, 7);
	ConOutputString("2 - 开始游戏 - 普通");

	ConSetPosition(3, 8);
	ConOutputString("3 - 开始游戏 - 困难");

	ConSetPosition(3, 10);
	ConOutputString("L - 加载游戏");

	ConSetPosition(3, 12);
	ConOutputString("Q - 退出游戏");
}
void ShowGame(void)
{
	COORD position;
	int monster;
	/* 绘制玩家位置 */
	ConSetBackgroundColor(ConBlack);
	ConSetTextColor(ConGreen);

	PlayerGetPosition(&position);

	ConSetPosition(position.X,position.Y);
	ConOutputString("P");

	/* 绘制场地 */
	int fieldx, fieldy;

	ConSetBackgroundColor(ConWhite);
	ConSetTextColor(ConWhite);

	for(fieldy = 0; fieldy <= cdArena.Y; fieldy ++)
	{
		if(fieldy == 0 || fieldy == cdArena.Y)
		{
			for(fieldx = 0; fieldx <= cdArena.X; fieldx ++)
			{
				ConSetPosition(fieldx, fieldy);
				ConOutputString("#");
			}
		}else
		{
			ConSetPosition(0, fieldy);
			ConOutputString("#");

			ConSetPosition(cdArena.X, fieldy);
			ConOutputString("#");
		}
	}/* 外部for */

	/* 绘制怪物 */
	ConSetBackgroundColor(ConBlack);
	ConSetTextColor(ConRed);

	for(monster = 0; monster < iMonstersNumber; monster ++)
	{
		if(cdpMonsters[monster].X != 0)
		{
			ConSetPosition(cdpMonsters[monster].X,cdpMonsters[monster].Y);
			ConOutputString("M");
		}
	
	}/* 外部for */

	/* 显示生命数和分数 */
	char buffer[100];
	
	sprintf(buffer, "Lives:%d\t\tScore:%d\t\tLeaps:%d\tS-保存游戏"
			,PlayerGetLives()
			,PlayerGetScore()
			,PlayerGetLeaps());

	ConSetPosition(5,24);
	ConSetTextColor(ConRed | ConGreen);
	ConOutputString(buffer);

}
void ShowWon(void)
{
	ShowGame();

	ConSetPosition(20, 11);
	ConSetBackgroundColor(ConGreen);
	ConSetTextColor(ConRed);

	ConOutputString("#####################################");
	ConSetPosition(20, 12);
	ConOutputString("# 恭喜！                            #");
	ConSetPosition(20, 13);
	ConOutputString("# 你已经杀死了所有的小怪兽。        #");
	ConSetPosition(20, 14);
	ConOutputString("#####################################");

}
void ShowLostLife(void)
{
	ShowGame();

	ConSetPosition(20,11);
	
	ConSetBackgroundColor(ConGreen);
	ConSetTextColor(ConRed);
	ConOutputString("#####################################");
	ConSetPosition(20,12);
	ConOutputString("# 你失去一条生命                    #");
	ConSetPosition(20,13);
	ConOutputString("#####################################");

}
void ShowLost(void)
{
	ShowGame();

	ConSetPosition(20,11);
	
	ConSetBackgroundColor(ConGreen);
	ConSetTextColor(ConRed);
	ConOutputString("#####################################");
	ConSetPosition(20,12);
	ConOutputString("# 胜败乃兵家常事，                  #");
	ConSetPosition(20,13);
	ConOutputString("# 英雄请重新来过。                  #");
	ConSetPosition(20,14);
	ConOutputString("#####################################");

}
void ShowExit(void)
{
	ConSetBackgroundColor(ConBlack);
	ConSetTextColor(ConWhite);
	ConClear();

	ConOutputString("\n\t小怪兽 v 1.0\n\n\n");
	ConOutputString("by: Wener (wenermail@gmail.com)\n");
	ConOutputString("Bay!\n");
}
void Show(void)
{
	/* 初始化控制台 */
	ConSetBackgroundColor(ConBlack);
	ConSetTextColor(ConWhite);
	ConClear();

	switch(iGameStatus)
	{
		case GameMainMenu:
			ShowMenu();
			break;
		case GameRunning:
			ShowGame();
			break;
		case GameWon:
			ShowWon();
			break;
		case GameLostLife:
			ShowLostLife();
			break;
		case GameLost:
			ShowLost();
			break;
		case GameExit:
			ShowExit();
			break;
		case GameSplashScreen:
			ShowSplash();
			break;

		default:
			break;
	}/* switch */
}

/* 根据游戏状态处理游戏的情形变化 */
void ProcessSplash(void)
{
	if(iLastAction)
	{
		iGameStatus = GameMainMenu;
	}
}
void ProcessMenu(void)
{
	switch(iLastAction)
	{
		/* 退出游戏 */
		case VK_ESCAPE:
		case 'Q':
		case 'q':
			iGameStatus = GameExit;
			break;

		case 'l':
		case 'L':
			StartNewGame(GameEasy);
			Load();
			iGameStatus = GameRunning;
			break;

		case '1':
			StartNewGame(GameEasy);
			iGameStatus = GameRunning;
			break;
		case '2':
			StartNewGame(GameMedium);
			iGameStatus = GameRunning;
			break;
		case '3':
			StartNewGame(GameDifficult);
			iGameStatus = GameRunning;
			break;

		default:
			break;
	}
}
void ProcessGame(void)
{
	COORD movement;
	int monster, monstersAlive;

	movement.X = 0, movement.Y = 0;

	/* 移动玩家 */
	switch(iLastAction)
	{
		case 's':
		case 'S':
			Save();
			break;

		case VK_UP:
			movement.Y = -1;
			break;
		case VK_DOWN:
			movement.Y = 1;
			break;
		case VK_RIGHT:
			movement.X = 1;
			break;
		case VK_LEFT:
			movement.X = -1;
			break;

		case VK_HOME:
			movement.X = -1;
			movement.Y = -1;
			break;
		case VK_PRIOR:
			movement.X = 1;
			movement.Y = -1;
			break;
		case VK_END:
			movement.X = -1;
			movement.Y = 1;
			break;
		case VK_NEXT:
			movement.Y = 1;
			movement.Y = 1;
			break;

		case VK_INSERT:
			if(PlayerGetLeaps() > 0)
			{
				PlayerRandomLeap(cdArena);
				PlayerSetLeaps(PlayerGetLeaps() - 1);
			}
			break;

		case VK_ESCAPE:
			EndGame();
			iGameStatus = GameMainMenu;
			break;

		default:
			break;
	}/* switch */

	/* 移动 */
	if(movement.X != 0 || movement.Y != 0)
	{
		COORD playerPosition;
		PlayerGetPosition(&playerPosition);

		/* 如果在范围内，就相应的移动娃娃你家 */
		if(movement.X + playerPosition.X > 0
			&& movement.Y + playerPosition.Y > 0
			&& movement.X + playerPosition.X < cdArena.X
			&& movement.Y + playerPosition.Y < cdArena.Y)
		{
			PlayerMove(movement);
		}

		/* 编写怪物人工智能，检测是否会发生碰撞 */
		MoveMonsters();
		CheckCollisions();

		/* 检测是否还有怪物活着 */
		monstersAlive = 0;
		for(monster = 0; monster < iMonstersNumber; monster++)
		{
			/* 检验怪物是否死了 */
			if(cdpMonsters[monster].X == 0)
				continue;
			monstersAlive = 1;
			break;
		}/* end for */

		if(monstersAlive == 0)
		{
			iGameStatus = GameWon;
		}
	}/* 移动 if */
}
void ProcessWon(void)
{
	if(iLastAction)
	{
		iGameStatus = GameMainMenu;
	}

	EndGame();
}
void ProcessLost(void)
{
	if(iLastAction)
	{
		iGameStatus = GameMainMenu;
	}

	EndGame();
	Show();
}
void ProcessLostLife(void)
{
	int isValid = 0;
	int monster;
	COORD position;

	/* 减去我玩家一个生命数，如果生命输耗尽，就结束游戏 */
	PlayerSetLives(PlayerGetLives() - 1);
	if(PlayerGetLives() - 1 <= -1)
	{
		iGameStatus = GameLost;
	}else
	{
		iGameStatus = GameRunning;
		isValid = 0;

		/* 计算玩家随机位置 */
		do
		{
			PlayerRandomLeap(cdArena);
			PlayerGetPosition(&position);

			/* 确保该位置没有怪物 */
			for(monster = 0; monster < iMonstersNumber; monster ++)
			{
				/* 怪物已经死了 */
				if(cdpMonsters[monster].X == 0)
					continue;
				/* 是否碰撞 */
				if(cdpMonsters[monster].X == position.X
					&& cdpMonsters[monster].Y == position.Y)
				{
					isValid = 0;
				}else
				{
					isValid = 1;
				}
			}/* for 与怪物的碰撞 */
		}while(isValid == 0);/* 为玩家找一个新的位置 */
	}
}
void ProcessExit(void)
{
}
void Process()
{
	/* 游戏百世必须闪屏，因为没有触发，所以强制显示 */
	if(iGameStatus == GameSplashScreen)
	{
		Show();
	}
	
	/* 对用户按键做出相应的响应 */
	if(GetAction())
	{
		switch(iGameStatus)
		{
			case GameMainMenu:
				ProcessMenu();
				break;
			case GameRunning:
				ProcessGame();
				break;
			case GameWon:
				ProcessWon();
				break;
			case GameLostLife:
				ProcessLostLife();
				break;
			case GameLost:
				ProcessLost();
				break;
			case GameExit:
				ProcessExit();
				break;
			case GameSplashScreen:
				ProcessSplash();
				break;

			default:
				break;
		}/* switch */
	
		Show();
	}/* if GetAction */
}

/* 游戏方法 */
void StartNewGame(int diffuculty)
{
	int monster;
	COORD position;

	iGameStatus = GameRunning;

	/* 设置游戏难度 */
	switch(diffuculty)
	{
		case GameEasy:
			iMonstersNumber = 10;
			PlayerSetLives(4);
			PlayerSetLeaps(3);
			cdArena.X = 25;
			cdArena.Y = 15;
			break;
		case GameMedium:
			iMonstersNumber = 20;
			PlayerSetLives(3);
			PlayerSetLeaps(2);
			cdArena.X = 35;
			cdArena.Y = 18;
			break;
		case GameDifficult:
			iMonstersNumber = 30;
			PlayerSetLives(2);
			PlayerSetLeaps(1);
			cdArena.X = 50;
			cdArena.Y = 23;
			break;
		default:
			break;
	}

	/* 创建玩家 */
	PlayerRandomLeap(cdArena);
	PlayerSetScore(0);

	/* 创建怪物 */
	cdpMonsters = malloc(sizeof(COORD) * iMonstersNumber);

	srand(time(NULL));

	/* 计算怪物的随机位置 */
	PlayerGetPosition(&position);
	for(monster = 0; monster < iMonstersNumber; monster ++)
	{
		/* 确保怪物和玩家的位置不同 */
		do
		{
			cdpMonsters[monster].X = (rand() % (cdArena.X - 1)) + 1;
			cdpMonsters[monster].Y = (rand() % (cdArena.Y - 1)) + 1;
		}
		while( (cdpMonsters[monster].X == position.X)
				&& (cdpMonsters[monster].Y == position.Y));
	}/* end for */
}
void EndGame(void)
{
	if(cdpMonsters != NULL)
	{
		free(cdpMonsters);
		cdpMonsters = NULL;
	}
}
void CheckCollisions(void)
{
	COORD position;
	int monsterA, monsterB;

	PlayerGetPosition(&position);

	for(monsterA = 0; monsterA < iMonstersNumber; monsterA ++)
	{
		/* 检测是否怪物已死 */
		if(cdpMonsters[monsterA].X == 0)
			continue;

		/* 检测和玩家的碰撞 */
		if((cdpMonsters[monsterA].X == position.X)
			&& (cdpMonsters[monsterA].Y == position.Y))
		{
			cdpMonsters[monsterA].X = 0;
			cdpMonsters[monsterA].Y = 0;

			/* 检验玩家是否还有生命数 */
			if(PlayerGetLives() - 1 <= 0)
			{
				iGameStatus = GameLost;
			}else
			{
				iGameStatus = GameLostLife;
			}
			return;
		}/* end if */

		/* 检测怪物之间的碰撞 */
		for(monsterB = monsterA + 1; monsterB < iMonstersNumber; monsterB++)
		{
			/* 检测怪物是否已死 */
			if(cdpMonsters[monsterB].X == 0)
				continue;

			/* 怪物之间的碰撞检测 */
			if((cdpMonsters[monsterA].X == cdpMonsters[monsterB].X)
				&& (cdpMonsters[monsterA].Y == cdpMonsters[monsterB].Y))
			{
				cdpMonsters[monsterA].X = cdpMonsters[monsterA].Y = 0;
				cdpMonsters[monsterB].X = cdpMonsters[monsterB].Y = 0;

				PlayerSetScore(PlayerGetScore() + 15);
			}

		}/* end if */
	}/* end outter for */

}
int GetAction(void)
{
	iLastAction = ConGetKey();
return iLastAction;
}
int GetStatus(void)
{
	return iGameStatus;
}
void MoveMonsters(void)
{
	COORD distance, position;
	int monster;
	PlayerGetPosition(&position);

	for(monster = 0; monster < iMonstersNumber; monster ++)
	{
		/* 检查怪物是否已经死了 */
		if(cdpMonsters[monster].X == 0)
			continue;

		distance.X = position.X - cdpMonsters[monster].X;
		distance.Y = position.Y - cdpMonsters[monster].Y;

		/* 确保移动一个单位 */
		if(distance.X > 0)
			distance.X = 1;
		else if(distance.X < 0)
			distance.X = -1;

		if(distance.Y > 0)
			distance.Y = 1;
		else if(distance.Y < 0)
			distance.Y = -1;

		/* 移动哦怪物 */
		cdpMonsters[monster].X += distance.X;
		cdpMonsters[monster].Y += distance.Y;
	}
}

void Load(void)
{
	FILE* fp;
	
	fp = fopen("monster.sav", "rb");
	if(NULL != fp)
	{
		COORD playerPosition;
		int playerLives;
		int playerScore;
		int playerLeaps;

		/* 从文件加载数据 */
		fread(&cdArena, sizeof(COORD), 1, fp);
		fread(&playerPosition, sizeof(COORD), 1, fp);
		fread(&playerLives, sizeof(int), 1, fp);
		fread(&playerScore, sizeof(int), 1, fp);
		fread(&playerLeaps, sizeof(int), 1, fp);
		fread(&iMonstersNumber, sizeof(int), 1, fp);

		if(cdpMonsters != NULL)
			free(cdpMonsters);
		
		cdpMonsters = malloc(sizeof(COORD) * iMonstersNumber);
		fread(cdpMonsters, sizeof(COORD) * iMonstersNumber, 1, fp);
		
		/* 设置 */
		PlayerSetPosition(&playerPosition);
		PlayerSetLives(playerLives);
		PlayerSetLeaps(playerLeaps);
		PlayerSetScore(playerScore);
	}
	/* 关闭文件句柄 */
	fclose(fp);
}

void Save(void)
{
	FILE* fp;
	
	fp = fopen("monster.sav", "wb");
	if(NULL != fp)
	{
		COORD playerPosition;
		int playerLives;
		int playerScore;
		int playerLeaps;

		PlayerGetPosition(&playerPosition);
		playerLives = PlayerGetLives();
		playerLeaps = PlayerGetLeaps();
		playerScore = PlayerGetScore();

		/* 从文件加载数据 */
		fwrite(&cdArena, sizeof(COORD), 1, fp);
		fwrite(&playerPosition, sizeof(COORD), 1, fp);
		fwrite(&playerLives, sizeof(int), 1, fp);
		fwrite(&playerScore, sizeof(int), 1, fp);
		fwrite(&playerLeaps, sizeof(int), 1, fp);
		fwrite(&iMonstersNumber, sizeof(int), 1, fp);

		fwrite(cdpMonsters, sizeof(COORD) * iMonstersNumber, 1, fp);
	}
	/* 关闭文件句柄 */
	fclose(fp);

}
