game:
	gcc c.c -lncurses
intro:
	cc -c intro.c 
	cc -c options.c 
	cc options.o intro.o -lncurses -o intro
remove:
	rm *.o
