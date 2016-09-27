#include "c.h"
int main(void) {
	int i;
	char a[N][N];
	player_ship player1;
	initiate();
	space_create(a);
	for (i = 0; i < N; i++)
		player1.player_shoot_column[i] = -1;
	player1.column = 0;
	player1.row = N - 1;
	i--;
	a[i][player1.column] = 'X';
	bold_print(i, player1.column, a[i][player1.column]);
	do {
		move(row + i * vert_space, column + player1.column * horiz_space);
		change_refresh_time();
		refresh();
		switch (getch()) {
		case KEY_LEFT:
			if (player1.column > 0) {
				a[i][player1.column] = ' ';
				printw("%c", a[i][player1.column]);
				player1.column--;
				a[i][player1.column] = 'X';
				mvprintw(row + i * vert_space, column + player1.column * horiz_space, "%c", a[i][player1.column]);
			}
			break;
		case KEY_RIGHT:
			if (player1.column < N - 1) {
				a[i][player1.column] = ' ';
				printw("%c", a[i][player1.column]);
				player1.column++;
				a[i][player1.column] = 'X';
				mvprintw(row + i * vert_space, column + player1.column * horiz_space, "%c", a[i][player1.column]);
			}
			break;
		case KEY_UP:
			if (i > height + 1) {
				a[i][player1.column] = ' ';
				printw("%c", a[i][player1.column]);
				i--;
				player1.row = i;
				a[i][player1.column] = 'X';
				mvprintw(row + i * vert_space, column + player1.column * horiz_space, "%c", a[i][player1.column]);
			}
			break;
		case KEY_DOWN:
			if (i < N - 1) {
				a[i][player1.column] = ' ';
				printw("%c", a[i][player1.column]);
				i++;
				player1.row = i;
				a[i][player1.column] = 'X';
				mvprintw(row + i * vert_space, column + player1.column * horiz_space, "%c", a[i][player1.column]);
			}
			break;
		case 32:
			player_shoot(&player1);
			player_no_of_shoots++;
			break;
		case 27:
			endwin();
			exit(0);
		}
		if (player_no_of_shoots != 0)
			player_ammo_forward(a, &player1);
	} while(win);
	return 0;
}
int initiate(void) {
	initscr();
	curs_set(0);
	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	noecho();
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, max_y, max_x);
	return 0;
}
void space_create(char a[][N]) {
	int i, k;
	for (i = 0; i < N; i++) {
		for (k = 0; k < N; k++) {
			a[i][k] = ' ';
		}
	}
	vert_space = max_y / (N - 1);
	horiz_space = max_x / (N - 1);
	row = (max_y - (N - 1) * vert_space) / 2;
	column = (max_x - (N - 1) * horiz_space) / 2;
	for (i = 0; i < N; i++) {
		for (k = 0; k < N; k++) {
			mvprintw(row + i * vert_space, column + k * horiz_space,"%c", a[i][k]);
		}
	}
	return;
}
void bold_print(int i, int k, char c) {
	attron(A_BOLD);
	mvprintw(row + i * vert_space, column + k * horiz_space, "%c", c);
	attroff(A_BOLD);
}
void player_shoot(player_ship *player1) {
	int i;
	for (i = 0; i < N; i++) {
		if (player1->player_shoot_column[i] == -1) {
			player1->player_shoot_column[i] = player1->column;
			player1->player_ammo_reach[i] = player1->row - 1;
			return;
		}
	}
}
void player_ammo_forward(char a[][N], player_ship *player1) {
	int i, j;
	for (i = 0; i < N; i++) {
		if (player1->player_shoot_column[i] != -1) {
			if (player1->player_ammo_reach[i] != N - 1) {
				a[player1->player_ammo_reach[i]][player1->player_shoot_column[i]] = ' ';
				mvprintw(row + player1->player_ammo_reach[i] * vert_space, column + player1->player_shoot_column[i] * horiz_space, "%c", a[player1->player_ammo_reach[i]][player1->player_shoot_column[i]]);
			}
			if (player1->player_ammo_reach[i] - 1 <= height) {
				player1->player_shoot_column[i] = -1;
				player_no_of_shoots--;
			}
			else {
				player1->player_ammo_reach[i]--;
				a[player1->player_ammo_reach[i]][player1->player_shoot_column[i]] = missile;
				if(missile == '|') {
					attron(COLOR_PAIR(1));
					bold_print(player1->player_ammo_reach[i], player1->player_shoot_column[i], a[player1->player_ammo_reach[i]][player1->player_shoot_column[i]]);
					attroff(COLOR_PAIR(1));
				}
				else if(missile == '^') {
					attron(COLOR_PAIR(2));
					bold_print(player1->player_ammo_reach[i], player1->player_shoot_column[i], a[player1->player_ammo_reach[i]][player1->player_shoot_column[i]]);
					attroff(COLOR_PAIR(2));
				}
		
			}
		}
	}
}
void change_refresh_time(void) {
	if (points >= 800) {
		wtimeout(stdscr, 50);
		return;
	}
	if (points >= 400) {
		wtimeout(stdscr, 100);
		return;
	}
	if (points >= 100) {
		wtimeout(stdscr, 200);
		return;
	}
	if ((points == 0) && (points < 100)) {
		wtimeout(stdscr, 250);
		return;
	}
}

