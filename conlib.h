#ifndef CONLIB_H
	#define CONLIB_H

enum ConColor
{
	ConRed = 1,
	ConGreen = 2,
	ConBlue = 4,

	ConWhite = ConRed | ConGreen | ConBlue,
	ConBlack = 0
};

void ConLibInit(void);

void ConSetBackgroundColor(int color);
void ConSetTextColor(int color);
void ConSetTitle(char *title);
void ConSetPosition(int x, int y);

void ConClear(void);
void ConOutputString(char *string);

void ConRead(char *buffer, int buffersize);
int ConGetKey(void);

#endif
