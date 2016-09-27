#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#define N 20
/*Number of blocks used*/
#define M 7

typedef struct {
	int ship_column; 
	int ship_shoot_row; 
	int life; 
	int value; 
} enemy_ship;
/*Structure of enemy ship*/

typedef struct {
	int column;
	int row;
	int player_ammo_reach[N]; 
	int player_shoot_column[N];
	int player_life; 
} player_ship;
/*Structure of player's ship*/

int initiate(void);
/*Initializing screen*/

void space_create(char a[][N]);
/*Creating game background*/

void bold_print(int i, int k, char c);
/*Highlighting some enemies and printing in bold*/

void change_refresh_time(void);
/*Increasing speed of the game*/

void player_shoot(player_ship *player1);
/*Player shoots*/

void player_ammo_forward(char a[][N], player_ship *player1);
/*Moving player ammo forward*/

int points = 0;/*Player points*/
int  win = 1;/*Condition for continuing game*/
int  player_no_of_shoots = 0;/*Number of shoots fired by player*/
int row, column, horiz_space, vert_space, max_y, max_x;/*Total game dimensions*/
int  height = 0;/*Enemy ships height*/
char missile = '|';

