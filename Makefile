game: pvp.c pvp.h main.c main.h
	cc -c pvp.c
	cc -c main.c
	cc -c kbhit.c
	cc main.o pvp.o kbhit.o -lncurses -o program
remove:
	rm *.o
