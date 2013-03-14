
OBJS=monster.c conlib.c player.c game.c

WFLAGS=-Wall -Wextra -g3
CFLAGS=$(WFLAGS)

all: FORCE
	gcc $(OBJS) -o monster.exe $(CFLAGS)

test: FORCE
	gcc $(OBJS) -c $(CFLAGS)

clean: FORCE
	rm *.o *.exe
FORCE:

