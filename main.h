/* This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include <string.h>
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include "kbhit.h"

#define N 20
#define L 3  
#define M 12 

void abou(void);
void pri_menu(WINDOW *w, int rev);
void pri_menu1(WINDOW *w, int rev);
void pri_menu2(WINDOW *w, int rev);
void pri_menu3(WINDOW *w, int rev);
void setting(void);
void mode(void);
void weapon(void);
char *ch[] = { "New Game", "Buy Weapons", "Options", "About game", "Exit"};
char *ch1[4] = { "Easy", "Medium", "Hard", "Reset highscore"};
char *ch2[3] = { "Single Player", "Two Player", "Player vs Player"};
char *ch3[2] = { "Weapon A - |", "Weapon B - ^"};
int par_x, par_y;

typedef struct {
	int column;
	int row;
	int player_ammo_reach[N]; 
	int player_shoot_column[N];
	int player_life;
	int points;
} player_ship;
typedef struct {
	int column;
	int row;
	int player_ammo_reach[N]; 
	int player_shoot_column[N];
	int player_life;
	int player_no_of_shoots;
	int points;
	char missile;
} player_shiptp;
typedef struct {
	int ship_column; 
	int ship_shoot_row; 
	int life; 
	int value; 
} enemy_ship;

void one_player(void);
void two_player(void);
void playervsplayer(void);

int initiate(void);
void space_create(char a[][N]);
void delete_enemy_ship(char a[][N], int j, enemy_ship s[M],enemy_ship prev[M]);
void game_end(player_ship player);
void bold_print(int i, int k, char c);
void change_refresh_time(player_ship player1);
void increase_difficulty(char a[][N], enemy_ship s[M], player_ship *player1,enemy_ship prev[M]);
void change_no_of_ships(char a[][N], enemy_ship s[M], player_ship player1);
void enemy_ships_create(char a[][N], enemy_ship s[M]);
void enemy_shoots(char a[][N], enemy_ship s[M], player_ship *player1);
void player_shoot(player_ship *player1);
void player_ammo_forward(char a[][N], enemy_ship s[M],player_ship *player1, enemy_ship prev[M]);
void manage_hit(char a[][N], int i, int j, enemy_ship s[M],enemy_ship prev[M], player_ship *player);
void prev_shoots_recover(char a[][N], enemy_ship prev[M], player_ship *player1);
void player_shoots_sort(player_ship *player1);


void game_end2(player_shiptp *player1, player_shiptp *player2);
void space_create2(char a[][N]);
void bold_print2(int i, int k, char c);
void change_refresh_time2(player_shiptp player1, player_shiptp player2);
void increase_difficulty2(char a[][N], enemy_ship s[M], player_shiptp *player, enemy_ship prev[M], int points1, int points2);
void change_no_of_ships2(char a[][N], enemy_ship s[M], int points1, int points2);
void enemy_ships_create2(char a[][N], enemy_ship s[M]);
void enemy_shoots2(char a[][N], enemy_ship s[M], player_shiptp *player);
void player_shoots2(player_shiptp *player);
void player_ammo_forward2(char a[][N], enemy_ship s[M],player_shiptp *player, enemy_ship prev[M]);
void manage_hit2(char a[][N], int i, int j, enemy_ship s[M],enemy_ship prev[M], player_shiptp *player);
void delete_enemy_ship2(char a[][N], int j, enemy_ship s[M],enemy_ship prev[M]);
void prev_shoots_recover2(char a[][N], enemy_ship prev[M], player_shiptp *player);
void player_shoots_sort2(player_shiptp *player);

int highscore = 0, money, win = 1, player_no_of_shoots = 0, row, column, horiz_space, vert_space, max_y, max_x, height = 0, intra_diff = 0, enemy_ships_number = 7, difficulty = 3, money, new_y, new_x;
char missile = '|';
FILE *fp;
