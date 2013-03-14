#include <windows.h>
#include <string.h>
#include "conlib.h"

static HANDLE hndScreen = NULL;
static HANDLE hndKeyboard = NULL;

static WORD wTextColor;
static WORD wBackgroundColor;

void ConLibInit(void)
{
	hndScreen = GetStdHandle(STD_OUTPUT_HANDLE);
	hndKeyboard = GetStdHandle(STD_INPUT_HANDLE);

	ConSetTextColor(ConWhite);
	ConSetBackgroundColor(ConBlack);
}

void ConSetBackgroundColor(int color)
{
	wBackgroundColor = 0;
	if(color & ConRed)
		wBackgroundColor |= BACKGROUND_RED;
	if(color & ConGreen)
		wBackgroundColor |= BACKGROUND_GREEN;
	if(color & ConBlue)
		wBackgroundColor |= BACKGROUND_BLUE;

	SetConsoleTextAttribute(hndScreen, wTextColor | wBackgroundColor);
}
void ConSetTextColor(int color)
{
	wTextColor = 0;
	if(color & ConRed)
		wTextColor |= FOREGROUND_RED;
	if(color & ConGreen)
		wTextColor |= FOREGROUND_GREEN;
	if(color & ConBlue)
		wTextColor |= FOREGROUND_BLUE;
	
	SetConsoleTextAttribute(hndScreen, wTextColor | wBackgroundColor);
}
void ConSetTitle(char *title)
{
	SetConsoleTitle(title);
}
void ConSetPosition(int x, int y)
{
	COORD pos;
	pos.X = x, pos.Y = y;
	SetConsoleCursorPosition(hndScreen, pos);
}

void ConClear(void)
{
	COORD start;
	DWORD written;

	start.X = 0, start.Y = 0;

	FillConsoleOutputAttribute(hndScreen,wTextColor | wBackgroundColor\
			, 80 * 25, start, &written);
	FillConsoleOutputCharacter(hndScreen, ' '\
			, 80 * 25, start, &written);
	SetConsoleCursorPosition(hndScreen, start);
}
void ConOutputString(char *string)
{
	DWORD written;
	WriteConsole(hndScreen, string, strlen(string), &written, NULL);
}

void ConRead(char *buffer, int buffersize)
{
	DWORD read;
	ReadConsole(hndKeyboard, buffer, buffersize, &read, NULL);
}
int ConGetKey(void)
{
	DWORD read;
	INPUT_RECORD e;

	ReadConsoleInput(hndKeyboard, & e, 1, &read);

	if(e.EventType == KEY_EVENT)
	{
		if(e.Event.KeyEvent.bKeyDown)
		{
			return e.Event.KeyEvent.wVirtualKeyCode;
		}
	}
return 0;
}
