game: pvp.c pvp.h main.c main.h kbhit.c kbhit.h
	cc -c pvp.c
	cc -c main.c
	cc -c kbhit.c
	cc main.o pvp.o kbhit.o -lncurses -o project
remove:
	rm *.o
