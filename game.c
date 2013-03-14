#include "game.h"

/* �ֲ����� */
static int iLastAction;

// ��Ϸ��Ϣ
static enum GameStatus iGameStatus;
static COORD cdArena;
static COORD* cdpMonsters;
static int iMonstersNumber;

/* ��ʼ�� */
void GameInit()
{
	/* ���ó�ʼֵ */
	iGameStatus = GameSplashScreen;
	iLastAction = 0;
	cdpMonsters = NULL;
}

/* ��ʾ�����Ϣ */
void ShowSplash(void)
{
	ConClear();
	ConOutputString("\tС���� v 1.0\n\n");
	ConOutputString("\tһ���쳣�򵥵�С��Ϸ����\n\n");
	ConOutputString("��ϷĿ��Ϊ��������С���ޣ�������\n");
	ConOutputString("С���޽��뵽һ������ʱ����������\n");
	ConOutputString("���𣬵����С����ͬʱ����һ����\n");
	ConOutputString("��ʱ�����ޱ������㱻����һ��Ѫ\n");
	ConOutputString("��С���̵�8���������ƶ���Ҳ����\n");
	ConOutputString("�� INSERT ���������������Ծ\n\n");

	ConSetTextColor(ConRed);
	ConOutputString("ע��:ȷ�� NUMLOCK �ǹرյ�\n\n");

	ConSetTextColor(ConWhite);
	ConOutputString("�������Ѷȿɹ�ѡ��:\n\n");
	ConOutputString("��:	������ = 10 ���� = 25*15\n");
	ConOutputString("		������ = 4  ��Ծ�� = 3\n");
	ConOutputString("��ͨ:	������ = 20 ���� = 35*18\n");
	ConOutputString("		������ = 3  ��Ծ�� = 2\n");
	ConOutputString("����:	������ = 30 ���� = 50*23\n");
	ConOutputString("		������ = 2  ��Ծ�� = 1\n");
}
void ShowMenu(void)
{
	ConSetBackgroundColor(ConBlack);
	ConSetTextColor(ConRed);
	ConClear();

	ConSetBackgroundColor(ConWhite);

	ConOutputString("\n");
	ConOutputString("С���� - version 1.0\n");
	
	ConSetBackgroundColor(ConBlack);
	ConSetTextColor(ConWhite);

	ConSetPosition(1, 4);
	ConOutputString("����������");

	ConSetPosition(3, 6);
	ConOutputString("1 - ��ʼ��Ϸ - ��");

	ConSetPosition(3, 7);
	ConOutputString("2 - ��ʼ��Ϸ - ��ͨ");

	ConSetPosition(3, 8);
	ConOutputString("3 - ��ʼ��Ϸ - ����");

	ConSetPosition(3, 10);
	ConOutputString("L - ������Ϸ");

	ConSetPosition(3, 12);
	ConOutputString("Q - �˳���Ϸ");
}
void ShowGame(void)
{
	COORD position;
	int monster;
	/* �������λ�� */
	ConSetBackgroundColor(ConBlack);
	ConSetTextColor(ConGreen);

	PlayerGetPosition(&position);

	ConSetPosition(position.X,position.Y);
	ConOutputString("P");

	/* ���Ƴ��� */
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
	}/* �ⲿfor */

	/* ���ƹ��� */
	ConSetBackgroundColor(ConBlack);
	ConSetTextColor(ConRed);

	for(monster = 0; monster < iMonstersNumber; monster ++)
	{
		if(cdpMonsters[monster].X != 0)
		{
			ConSetPosition(cdpMonsters[monster].X,cdpMonsters[monster].Y);
			ConOutputString("M");
		}
	
	}/* �ⲿfor */

	/* ��ʾ�������ͷ��� */
	char buffer[100];
	
	sprintf(buffer, "Lives:%d\t\tScore:%d\t\tLeaps:%d\tS-������Ϸ"
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
	ConOutputString("# ��ϲ��                            #");
	ConSetPosition(20, 13);
	ConOutputString("# ���Ѿ�ɱ�������е�С���ޡ�        #");
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
	ConOutputString("# ��ʧȥһ������                    #");
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
	ConOutputString("# ʤ���˱��ҳ��£�                  #");
	ConSetPosition(20,13);
	ConOutputString("# Ӣ��������������                  #");
	ConSetPosition(20,14);
	ConOutputString("#####################################");

}
void ShowExit(void)
{
	ConSetBackgroundColor(ConBlack);
	ConSetTextColor(ConWhite);
	ConClear();

	ConOutputString("\n\tС���� v 1.0\n\n\n");
	ConOutputString("by: Wener (wenermail@gmail.com)\n");
	ConOutputString("Bay!\n");
}
void Show(void)
{
	/* ��ʼ������̨ */
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

/* ������Ϸ״̬������Ϸ�����α仯 */
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
		/* �˳���Ϸ */
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

	/* �ƶ���� */
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

	/* �ƶ� */
	if(movement.X != 0 || movement.Y != 0)
	{
		COORD playerPosition;
		PlayerGetPosition(&playerPosition);

		/* ����ڷ�Χ�ڣ�����Ӧ���ƶ�������� */
		if(movement.X + playerPosition.X > 0
			&& movement.Y + playerPosition.Y > 0
			&& movement.X + playerPosition.X < cdArena.X
			&& movement.Y + playerPosition.Y < cdArena.Y)
		{
			PlayerMove(movement);
		}

		/* ��д�����˹����ܣ�����Ƿ�ᷢ����ײ */
		MoveMonsters();
		CheckCollisions();

		/* ����Ƿ��й������ */
		monstersAlive = 0;
		for(monster = 0; monster < iMonstersNumber; monster++)
		{
			/* ��������Ƿ����� */
			if(cdpMonsters[monster].X == 0)
				continue;
			monstersAlive = 1;
			break;
		}/* end for */

		if(monstersAlive == 0)
		{
			iGameStatus = GameWon;
		}
	}/* �ƶ� if */
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

	/* ��ȥ�����һ�������������������ľ����ͽ�����Ϸ */
	PlayerSetLives(PlayerGetLives() - 1);
	if(PlayerGetLives() - 1 <= -1)
	{
		iGameStatus = GameLost;
	}else
	{
		iGameStatus = GameRunning;
		isValid = 0;

		/* ����������λ�� */
		do
		{
			PlayerRandomLeap(cdArena);
			PlayerGetPosition(&position);

			/* ȷ����λ��û�й��� */
			for(monster = 0; monster < iMonstersNumber; monster ++)
			{
				/* �����Ѿ����� */
				if(cdpMonsters[monster].X == 0)
					continue;
				/* �Ƿ���ײ */
				if(cdpMonsters[monster].X == position.X
					&& cdpMonsters[monster].Y == position.Y)
				{
					isValid = 0;
				}else
				{
					isValid = 1;
				}
			}/* for ��������ײ */
		}while(isValid == 0);/* Ϊ�����һ���µ�λ�� */
	}
}
void ProcessExit(void)
{
}
void Process()
{
	/* ��Ϸ����������������Ϊû�д���������ǿ����ʾ */
	if(iGameStatus == GameSplashScreen)
	{
		Show();
	}
	
	/* ���û�����������Ӧ����Ӧ */
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

/* ��Ϸ���� */
void StartNewGame(int diffuculty)
{
	int monster;
	COORD position;

	iGameStatus = GameRunning;

	/* ������Ϸ�Ѷ� */
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

	/* ������� */
	PlayerRandomLeap(cdArena);
	PlayerSetScore(0);

	/* �������� */
	cdpMonsters = malloc(sizeof(COORD) * iMonstersNumber);

	srand(time(NULL));

	/* �����������λ�� */
	PlayerGetPosition(&position);
	for(monster = 0; monster < iMonstersNumber; monster ++)
	{
		/* ȷ���������ҵ�λ�ò�ͬ */
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
		/* ����Ƿ�������� */
		if(cdpMonsters[monsterA].X == 0)
			continue;

		/* ������ҵ���ײ */
		if((cdpMonsters[monsterA].X == position.X)
			&& (cdpMonsters[monsterA].Y == position.Y))
		{
			cdpMonsters[monsterA].X = 0;
			cdpMonsters[monsterA].Y = 0;

			/* ��������Ƿ��������� */
			if(PlayerGetLives() - 1 <= 0)
			{
				iGameStatus = GameLost;
			}else
			{
				iGameStatus = GameLostLife;
			}
			return;
		}/* end if */

		/* ������֮�����ײ */
		for(monsterB = monsterA + 1; monsterB < iMonstersNumber; monsterB++)
		{
			/* �������Ƿ����� */
			if(cdpMonsters[monsterB].X == 0)
				continue;

			/* ����֮�����ײ��� */
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
		/* �������Ƿ��Ѿ����� */
		if(cdpMonsters[monster].X == 0)
			continue;

		distance.X = position.X - cdpMonsters[monster].X;
		distance.Y = position.Y - cdpMonsters[monster].Y;

		/* ȷ���ƶ�һ����λ */
		if(distance.X > 0)
			distance.X = 1;
		else if(distance.X < 0)
			distance.X = -1;

		if(distance.Y > 0)
			distance.Y = 1;
		else if(distance.Y < 0)
			distance.Y = -1;

		/* �ƶ�Ŷ���� */
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

		/* ���ļ��������� */
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
		
		/* ���� */
		PlayerSetPosition(&playerPosition);
		PlayerSetLives(playerLives);
		PlayerSetLeaps(playerLeaps);
		PlayerSetScore(playerScore);
	}
	/* �ر��ļ���� */
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

		/* ���ļ��������� */
		fwrite(&cdArena, sizeof(COORD), 1, fp);
		fwrite(&playerPosition, sizeof(COORD), 1, fp);
		fwrite(&playerLives, sizeof(int), 1, fp);
		fwrite(&playerScore, sizeof(int), 1, fp);
		fwrite(&playerLeaps, sizeof(int), 1, fp);
		fwrite(&iMonstersNumber, sizeof(int), 1, fp);

		fwrite(cdpMonsters, sizeof(COORD) * iMonstersNumber, 1, fp);
	}
	/* �ر��ļ���� */
	fclose(fp);

}
