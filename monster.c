#include <stdio.h>
#include <stdlib.h>
#include "conlib.h"

#include "game.h"

int main(void)
{
	ConLibInit();
	GameInit();
	PlayerInit();

	ConSetTitle("С���� v 1.0");

	while(GetStatus() != GameExit)
	{
		Process();
	}

return EXIT_SUCCESS;
}
