#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#define N 20
/*Number of blocks used*/
#define L 3  
/*Player life*/
#define M 12 

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

void player_ammo_forward(char a[][N], enemy_ship s[M], player_ship *player1, enemy_ship prev[M]);
/*Moving player ammo forward*/

void game_end(void);
/*Game end screen*/

void increase_difficulty(char a[][N], enemy_ship s[M], player_ship *player1, enemy_ship prev[M]);
/*Increasing difficulty*/

void change_no_of_ships(char a[][N], enemy_ship s[M]);
/*Increasing number of enemy ships*/

void enemy_ships_create(char a[][N], enemy_ship s[M]);
/*Creating enemy ships*/

void enemy_shoots(char a[][N], enemy_ship s[M], player_ship *player1);
/*Handling enemy shoots*/

void manage_hit(char a[][N], int i, int j, enemy_ship s[M], enemy_ship prev[M]);
/*Managing enemy hit*/

void delete_enemy_ship(char a[][N], int j, enemy_ship s[M], enemy_ship prev[M]);
/*Deleting enemy ships*/

void prev_shoots_recover(char a[][N], enemy_ship prev[M], player_ship *player1);
/*Previous shoots recovery*/

int points = 0;
/*Player points*/

int win = 1;
/*Condition for win*/

int player_no_of_shoots = 0;
/*Number of ammo*/

int row, column, horiz_space, vert_space, max_y, max_x;
/*Dimensions of the screen*/

int height = 0;
/*Enemy ship height*/

int intra_diff = 0;
/*Difficulty inside the game*/

int enemy_ships_number = 7;
/*Number of enemy ships*/

int difficulty = 3;
/*Difficulty selected by player*/

char missile = '|';
/*Ammo*/
