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
#include "kbhit.h"
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#define N 20
#define L 3  
#define M 12 

typedef struct {
	int ship_column; 
	int ship_shoot_row; 
	int life; 
	int value; 
} enemy_ship;
typedef struct {
	int column;
	int row;
	int player_ammo_reach[N]; 
	int player_shoot_column[N];
	int player_life;
	int player_no_of_shoots;
	int points;
	char missile;
} player_shippvp;

void space_create3(char a[][N]);
void delete_enemy_ship3(char a[][N], int j, enemy_ship s[M],enemy_ship prev[M]);
void bold_print3(int i, int k, char c);
int initiate3(void);
void game_end3(player_shippvp player1, player_shippvp player2);
void change_refresh_time3(player_shippvp *player);
void change_no_of_ships3(char a[][N], enemy_ship s[M], player_shippvp *player);
void enemy_ships_create3(char a[][N], enemy_ship s[M]);
void player_shootpvp(player_shippvp *player1);
void player2_shoot(player_shippvp *player1);
void player1_ammo_forward(char a[][N], enemy_ship s[M],player_shippvp *player1, enemy_ship prev[M], player_shippvp player2);
void player2_ammo_downward(char a[][N], enemy_ship s[M],player_shippvp *player1, enemy_ship prev[M], player_shippvp player2);
void manage_hit3(char a[][N], int i, int j, enemy_ship s[M],enemy_ship prev[M], player_shippvp *player1, player_shippvp player2);
void player_shoots_sortpvp(player_shippvp *player1);

int row, column, horiz_space, vert_space, max_y, max_x, intra_diff3 = 0, enemy_ships_number3 = 7, diff = 3, new_y, new_x, heighta = 0, heightb = 10;;
FILE *fp;
