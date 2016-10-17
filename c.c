#include "c.h"
int main(void) {
	int i;
	char a[N][N];
	enemy_ship s[M],  prev[M];
	player_ship player1;
	if(difficulty == 1) {
		player1.player_life = 5;
	}
	else if(difficulty == 2) {
		player1.player_life = 3;
	}
	else
		player1.player_life = 1;
	srand(time(NULL));
	initiate();
	space_create(a);
	for (i = 0; i < M; i++) {
		s[i].ship_column = -1;
		prev[i].ship_column = -1;
	}
	enemy_ships_create(a, s);
	for (i = 0; i < N; i++)
		player1.player_shoot_column[i] = -1;
	player1.column = 0;
	player1.row = N - 1;
	i--;
	a[i][player1.column] = '*';
	bold_print(i, player1.column, a[i][player1.column]);
	do {
		move(row + i * vert_space, column + player1.column * horiz_space);
		change_refresh_time();
		refresh();
		switch (getch()) {
		case KEY_LEFT:
			if ((player1.column > 0) && (a[i][player1.column - 1] != ':')) {
				a[i][player1.column] = ' ';
				printw("%c", a[i][player1.column]);
				player1.column--;
				a[i][player1.column] = '*';
				mvprintw(row + i * vert_space, column + player1.column * horiz_space, "%c", a[i][player1.column]);
			}
			break;
		case KEY_RIGHT:
			if ((player1.column < N - 1) && (a[i][player1.column + 1] != ':')) {
				a[i][player1.column] = ' ';
				printw("%c", a[i][player1.column]);
				player1.column++;
				a[i][player1.column] = '*';
				mvprintw(row + i * vert_space, column + player1.column * horiz_space, "%c", a[i][player1.column]);
			}
			break;
		case KEY_UP:
			if ((i > height + 1) && (a[i][player1.column + 1] != ':')) {
				a[i][player1.column] = ' ';
				printw("%c", a[i][player1.column]);
				i--;
				player1.row = i;
				a[i][player1.column] = '*';
				mvprintw(row + i * vert_space, column + player1.column * horiz_space, "%c", a[i][player1.column]);
			}
			break;
		case KEY_DOWN:
			if ((i < N - 1) && (a[i][player1.column + 1] != ':')) {
				a[i][player1.column] = ' ';
				printw("%c", a[i][player1.column]);
				i++;
				player1.row = i;
				a[i][player1.column] = '*';
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
		if (points < 800) {
			if (points >= 100) {
				change_no_of_ships(a, s);
				if (points >= 150)
					increase_difficulty(a, s, &player1, prev);
			}
		}
		if (player_no_of_shoots != 0)
			player_ammo_forward(a, s, &player1, prev);
		enemy_shoots(a, s, &player1);
		prev_shoots_recover(a, prev, &player1);
	} while(win);
	game_end();
	return 0;
}
int initiate(void) {
	initscr();
	curs_set(0);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	raw();
	noecho();
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, max_y, max_x);
	return 0;
}
void game_end(void) {
	char exitmsg[] = "Better luck next time";
	wtimeout(stdscr, -1);
	clear();
	attron(COLOR_PAIR(1));
	attron(A_BOLD);
	if (!win) {
		mvprintw(max_y / 2, (max_x - strlen("You scored %d points!")) / 2, "You scored %d points!", points);
		mvprintw(max_y / 2 - 1, (max_x - strlen(exitmsg)) / 2, "%s", exitmsg);
	}	
	refresh();
	sleep(1);
	attroff(COLOR_PAIR);
	attroff(A_BOLD);
	endwin();
}
void space_create(char a[][N]) {
	int i, k;
	for (i = 0; i < N; i++) {
		for (k = 0; k < N; k++)
			a[i][k] = ' ';
	}
	vert_space = max_y / (N - 1);
	horiz_space = max_x / (N - 1);
	row = (max_y - 4 - (N - 1) * vert_space) / 2;
	column = (max_x - (N - 1) * horiz_space) / 2;
	for (i = 0; i < N; i++) {
		for (k = 0; k < N; k++)
			mvprintw(row + i * vert_space, column + k * horiz_space, "%c", a[i][k]);
	}
	return;
}
void bold_print(int i, int k, char c) {
	attron(A_BOLD);
	mvprintw(row + i * vert_space, column + k * horiz_space, "%c", c);
	attroff(A_BOLD);
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
	if (points == 0) {
		wtimeout(stdscr, 250);
		return;
	}
}
void increase_difficulty(char a[][N], enemy_ship s[M], player_ship *player1, enemy_ship prev[M]) {
	int prev_height = height, i, j;
	if (points >= 800) {
		height = 5;
	} else {
		if (points >= 650) {
			height = 4;
		} else {
			if (points >= 500) {
				height = 3;
			} else {
				if (points >= 300) {
					height = 2;
				} else {
					if (points >= 150)
						height = 1;
				}
			}
		}
	}
	if (height != prev_height) {
		for (i = 0; i < enemy_ships_number + intra_diff; i++) {
			a[height - 1][s[i].ship_column] = ' ';
			mvprintw(row + (height - 1) * vert_space, column + s[i].ship_column * horiz_space, "%c", a[height - 1][s[i].ship_column]);
			if (a[height][s[i].ship_column] != missile) {
				a[height][s[i].ship_column] = 'M';
				if (s[i].life == 3)
					bold_print(height, s[i].ship_column,
						   a[height][s[i].ship_column]);
				else
					mvprintw(row + height * vert_space, column + s[i].ship_column * horiz_space, "%c", a[height][s[i].ship_column]);
			} else {
				if (s[i].life != 1) {
					a[height][s[i].ship_column] = 'M';
					mvprintw(row + height * vert_space, column + s[i].ship_column * horiz_space, "%c", a[height][s[i].ship_column]);
				}
				for (j = 0; j < N; j++) {
					if ((player1->player_shoot_column[j] == s[i].ship_column) && (player1->player_ammo_reach[j] == height)) {
						manage_hit(a, j, i, s, prev);
						j = N;
					}
				}
				player1->player_shoot_column[j] = -1;
				player_no_of_shoots--;
			}
		}
	}
}
void change_no_of_ships(char a[][N], enemy_ship s[M]) {
	int prev_intra_diff = intra_diff;
	if (points >= 750) {
		intra_diff = 5;
	} else {
		if (points >= 600) {
			intra_diff = 4;
		} else {
			if (points >= 450) {
				intra_diff = 3;
			} else {
				if (points >= 250) {
					intra_diff = 2;
				} else {
					if (points >= 100)
						intra_diff = 1;
				}
			}
		}
	}
	if (intra_diff != prev_intra_diff)
		enemy_ships_create(a, s);
}
void enemy_ships_create(char a[][N], enemy_ship s[M]) {
	int k, i;
	for (i = 0; i < enemy_ships_number + intra_diff; i++) {
		if (s[i].ship_column == -1) {
			do {
				k = rand() % N;
			}while(a[height][k] == 'M');
			a[height][k] = 'M';
			s[i].ship_column = k;
			s[i].ship_shoot_row = height;
			if(difficulty == 1) {
				s[i].life = 1;
			}
			else
				s[i].life = rand() % L + 1;
			s[i].value = 5 * s[i].life;
			if (s[i].life == 3)
				bold_print(height, s[i].ship_column, a[height][s[i].ship_column]);
			else
				mvprintw(row + height * vert_space,column + s[i].ship_column * horiz_space, "%c", a[height][s[i].ship_column]);
		}
	}
}
void enemy_shoots(char a[][N], enemy_ship s[M], player_ship *player1) {
	int i;
	for (i = 0; i < enemy_ships_number + intra_diff; i++) {
		if (s[i].ship_shoot_row > height) {
			if (a[s[i].ship_shoot_row][s[i].ship_column] == ':') {
				a[s[i].ship_shoot_row][s[i].ship_column] = ' ';
				mvprintw(row + s[i].ship_shoot_row * vert_space,column + s[i].ship_column * horiz_space, "%c", a[s[i].ship_shoot_row][s[i].ship_column]);
			}
			if ((s[i].ship_column == player1->column) && (s[i].ship_shoot_row == player1->row)) {
				if(player1->player_life == 1) {
					win = 0;
				}
				else
					--player1->player_life;
				return;
			}
			if (s[i].ship_shoot_row + 1 == N)
				s[i].ship_shoot_row = height;
		}
		s[i].ship_shoot_row++;
		if (a[s[i].ship_shoot_row][s[i].ship_column] != missile) {
			a[s[i].ship_shoot_row][s[i].ship_column] = ':';
			attron(COLOR_PAIR(1));
			bold_print(s[i].ship_shoot_row, s[i].ship_column, a[s[i].ship_shoot_row][s[i].ship_column]);
			attroff(COLOR_PAIR);
		}
	}
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
void player_ammo_forward(char a[][N], enemy_ship s[M],player_ship *player1, enemy_ship prev[M]) {
	int i, j;
	for (i = 0; i < N; i++) {
		if (player1->player_shoot_column[i] != -1) {
			if (player1->player_ammo_reach[i] != N - 1) {
				a[player1->player_ammo_reach[i]][player1->player_shoot_column[i]] = ' ';
				mvprintw(row + player1->player_ammo_reach[i] * vert_space, column + player1->player_shoot_column[i] * horiz_space, "%c", a[player1->player_ammo_reach[i]][player1->player_shoot_column[i]]);
			}
			if (player1->player_ammo_reach[i] - 1 <= height) {
				for (j = 0; j < enemy_ships_number + intra_diff; j++) {
					if (s[j].ship_column == player1->player_shoot_column[i]) {
						manage_hit(a, i, j, s, prev);
						j = M;
					}
				}
				player1->player_shoot_column[i] = -1;
				player_no_of_shoots--;
			} else {
				player1->player_ammo_reach[i]--;
				a[player1->player_ammo_reach[i]][player1->player_shoot_column[i]] = missile;
				if(missile == '|') {
					attron(COLOR_PAIR(3));
					bold_print(player1->player_ammo_reach[i], player1->player_shoot_column[i], a[player1->player_ammo_reach[i]][player1->player_shoot_column[i]]);
					attroff(COLOR_PAIR(3));
				}
				else if(missile == '^') {
					attron(COLOR_PAIR(4));
					bold_print(player1->player_ammo_reach[i], player1->player_shoot_column[i], a[player1->player_ammo_reach[i]][player1->player_shoot_column[i]]);
					attroff(COLOR_PAIR(4));
				}
		
			}
		}
	}
}
void manage_hit(char a[][N], int i, int j, enemy_ship s[M], enemy_ship prev[M]) {
	if (s[j].life == 1) {
		points = points + s[j].value;
		delete_enemy_ship(a, j, s, prev);
		attron(COLOR_PAIR(3));
		attron(A_BOLD);
		mvprintw(max_y - 1, 1, "Points: %d", points);
		attroff(COLOR_PAIR(3));
		attroff(A_BOLD);
	} else {
		s[j].life--;
	}
}
void delete_enemy_ship(char a[][N], int j, enemy_ship s[M], enemy_ship prev[M]) {
	int i;
	if (s[j].ship_shoot_row != N - 1) {
		for (i = 0; i < enemy_ships_number + intra_diff; i++) {
			if (prev[i].ship_column == -1) {
				prev[j].ship_shoot_row = s[j].ship_shoot_row;
				prev[j].ship_column = s[j].ship_column;
				i = M;
			}
		}
	}
	a[height][s[j].ship_column] = ' ';
	mvprintw(row + height * vert_space, column + s[j].ship_column * horiz_space, "%c", a[height][s[j].ship_column]);
	s[j].ship_column = -1;
	enemy_ships_create(a, s);
}
void prev_shoots_recover(char a[][N], enemy_ship prev[M], player_ship *player1) {
	int i;
	for (i = 0; i < enemy_ships_number + intra_diff; i++) {
		if (prev[i].ship_column != -1) {
			if (a[prev[i].ship_shoot_row][prev[i].ship_column] == ':') {
				a[prev[i].ship_shoot_row][prev[i].ship_column] = ' ';
				mvprintw(row + prev[i].ship_shoot_row * vert_space,column + prev[i].ship_column * horiz_space, "%c", a[prev[i].ship_shoot_row][prev[i].ship_column]);
			}
			if ((prev[i].ship_column == player1->column) && (prev[i].ship_shoot_row == player1->row)) {
				if(player1->player_life == 1) {
					win = 0;
				}
				else
					--player1->player_life;				
				return;
			}
			if (prev[i].ship_shoot_row + 1 == N) {
				prev[i].ship_column = -1;
				return;
			}

			prev[i].ship_shoot_row++;
			if (a[prev[i].ship_shoot_row][prev[i].ship_column] != missile) {
				a[prev[i].ship_shoot_row][prev[i].ship_column] = ':';
				attron(COLOR_PAIR(1));
				bold_print(prev[i].ship_shoot_row, prev[i].ship_column, a[prev[i].ship_shoot_row][prev[i].ship_column]);
				attroff(COLOR_PAIR(1));
			}
		}
		mvprintw(max_y - 2, 1, "Ship Damage: ");
		if(player1->player_life == 5) {
			attron(A_REVERSE);		
			mvprintw(max_y - 2, 14, "    ");
			attroff(A_REVERSE);
		}	
		else if(player1->player_life == 3) {
			attron(A_REVERSE);		
			mvprintw(max_y - 2, 14, "      ");
			attroff(A_REVERSE);
		}	
		else if(player1->player_life == 1) {
			attron(A_REVERSE);		
			mvprintw(max_y - 2, 14, "        ");
			attroff(A_REVERSE);
		}	
	}
}
