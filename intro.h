#include <string.h>
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "options.h"
void abou(void);
void pri_menu(WINDOW *w, int rev);
int par_x, par_y;
char *ch[] = { "New Game", "Buy Weapons and Ships", "Options", "About game", "Exit"};

