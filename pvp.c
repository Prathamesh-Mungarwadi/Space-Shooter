#include "pvp.h"
void playervsplayer(void) {
	clear();
	struct timeval t1, t2;
	int i, j;
	char a[N][N];
	char ship1 = '*', ship2 = 'X';
	enemy_ship s[M], prev[M];
	player_shippvp player1, player2;
	player1.player_life = 1;
	player2.player_life = 1;
	player1.missile = '^';
	player2.missile = '|';
	player1.player_no_of_shoots = 0;
	player2.player_no_of_shoots = 0;
	player1.points = 0;
	player2.points = 0;
	srand(time(NULL));
	initiate3();
	space_create3(a);
	for (i = 0; i < M; i++) {
		s[i].ship_column = -1;
		prev[i].ship_column = -1;
	}
	enemy_ships_create3(a, s);
	for (i = 0; i < N; i++) {
		player1.player_shoot_column[i] = -1;
		player2.player_shoot_column[i] = -1;
	}	
	player2.column = 0;
	player2.row = 1;
	player1.column = 0;
	player1.row = N - 1;
	i--;
	j = 1;
	a[i][player1.column] = ship1;
	a[j][player2.column] = ship2;
	bold_print3(i, player1.column, a[i][player1.column]);
	bold_print3(j, player2.column, a[j][player2.column]);
	gettimeofday(&t1, NULL);
	do {
		move(row + i * vert_space, column + player1.column * horiz_space);
		change_refresh_time3(&player1);
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
			if ((i > heightb + 1) && (a[i][player1.column + 1] != ':')) {
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
			player_shootpvp(&player1);
			player_shoots_sortpvp(&player1);
			player1.player_no_of_shoots++;
			break;
		case 'a':
			if ((player2.column > 0) && (a[j][player2.column - 1] != ':')) {
				a[j][player2.column] = ' ';
				mvprintw(row + j * vert_space, column + player2.column * horiz_space, "%c", a[j][player2.column]);
				player2.column--;
				a[j][player2.column] = ship2;
				mvprintw(row + j * vert_space, column + player2.column * horiz_space, "%c", a[j][player2.column]);
			}
			break;
		case 'd':
			if ((player2.column < N - 1) && (a[j][player2.column + 1] != ':')) {
				a[j][player2.column] = ' ';
				mvprintw(row + j * vert_space, column + player2.column * horiz_space, "%c", a[j][player2.column]);
				player2.column++;
				a[j][player2.column] = ship2;
				mvprintw(row + j * vert_space, column + player2.column * horiz_space, "%c", a[j][player2.column]);
			}
			break;
		case 'w':
			if ((j > heighta) && (a[j][player2.column + 1] != ':')) {
				a[j][player2.column] = ' ';
				mvprintw(row + j * vert_space, column + player2.column * horiz_space, "%c", a[j][player2.column]);
				j--;
				player2.row = j;
				a[j][player2.column] = ship2;
				mvprintw(row + j * vert_space, column + player2.column * horiz_space, "%c", a[j][player2.column]);
			}
			break;
		case 's':
			if ((j < (N / 2 - 1)) && (a[j][player1.column + 1] != ':')) {
				a[j][player2.column] = ' ';
				mvprintw(row + j * vert_space, column + player2.column * horiz_space, "%c", a[j][player2.column]);
				j++;
				player2.row = j;
				a[j][player2.column] = ship2;
				mvprintw(row + j * vert_space, column + player2.column * horiz_space, "%c", a[j][player2.column]);
			}
			break;
		case 'f':
			player2_shoot(&player2);
			player2.player_no_of_shoots++;
			break;
		case 27:
			endwin();
			exit(0);
		}
		if ((player1.points < 800) || (player2.points < 800)) {
			if (player1.points >= 100) {
				change_no_of_ships3(a, s, &player1);
			}
		}
		if (player1.player_no_of_shoots != 0)
			player1_ammo_forward(a, s, &player1, prev, player2);
		if (player2.player_no_of_shoots != 0)
			player2_ammo_downward(a, s, &player2, prev, player1);
			attron(A_BOLD);
			attron(COLOR_PAIR(4));
			mvprintw(max_y - 1, 1, "Points: %d", player1.points);
			attroff(COLOR_PAIR(4));
			attron(COLOR_PAIR(3));
			mvprintw(max_y - 1, 15, "Points: %d", player2.points);
			attroff(COLOR_PAIR(3));
			attroff(A_BOLD);
	gettimeofday(&t2, NULL);	
	}while((t2.tv_sec - t1.tv_sec) < 60);
	game_end3(player1, player2);
	return;
}
int initiate3(void) {
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
void game_end3(player_shippvp player1, player_shippvp player2) {
	char exitmsg[] = "Better luck next time";
	wtimeout(stdscr, -1);
	clear();
	attron(A_BOLD);
	if (player1.points > player2.points) {
		attron(COLOR_PAIR(4));
		mvprintw(max_y / 2, (max_x - strlen("Player1 won by %d points")) / 2, "Player1 won by %d points", player1.points - player2.points);
		mvprintw(max_y / 2 - 1, (max_x - strlen(exitmsg)) / 2, "%s", exitmsg);
		attroff(COLOR_PAIR);
	}
	else if(player2.points > player1.points) {
		attron(COLOR_PAIR(3));
		mvprintw(max_y / 2, (max_x - strlen("Player2 won by %d points")) / 2, "Player2 won by %d points", player2.points - player1.points);
		mvprintw(max_y / 2 - 1, (max_x - strlen(exitmsg)) / 2, "%s", exitmsg);
		attroff(COLOR_PAIR);
	}
	else {
		attron(COLOR_PAIR(6));
		mvprintw(max_y / 2, (max_x - strlen("Player1 and Player2 scored same points")) / 2, "Player1 and Player2 scored same points");
		mvprintw(max_y / 2 - 1, (max_x - strlen(exitmsg)) / 2, "%s", exitmsg);
		attroff(COLOR_PAIR);
	}
	refresh();
	attroff(A_BOLD);
	sleep(2);	
	endwin();
}
void space_create3(char a[][N]) {
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
void bold_print3(int i, int k, char c) {
	attron(A_BOLD);
	mvprintw(row + i * vert_space, column + k * horiz_space, "%c", c);
	attroff(A_BOLD);
}
void change_refresh_time3(player_shippvp *player) {
	if (player->points >= 800) {
		wtimeout(stdscr, 50);
		return;
	}
	if (player->points >= 400) {
		wtimeout(stdscr, 100);
		return;
	}
	if (player->points >= 100) {
		wtimeout(stdscr, 200);
		return;
	}
	if (player->points == 0) {
		wtimeout(stdscr, 250);
		return;
	}
}
void change_no_of_ships3(char a[][N], enemy_ship s[M], player_shippvp *player) {
	int prev_intra_diff3 = intra_diff3;
	if (player->points >= 750) {
		intra_diff3 = 5;
	}
	else {
		if (player->points >= 600) {
			intra_diff3 = 4;
		}
		else {
			if (player->points >= 450) {
				intra_diff3 = 3;
			}
			else {
				if (player->points >= 250) {
					intra_diff3 = 2;
				}
				else {
					if (player->points >= 100)
						intra_diff3 = 1;
				}
			}
		}
	}
	if (intra_diff3 != prev_intra_diff3)
		enemy_ships_create3(a, s);
}
void enemy_ships_create3(char a[][N], enemy_ship s[M]) {
	int k, i;
	for (i = 0; i < enemy_ships_number3 + intra_diff3; i++) {
		if (s[i].ship_column == -1) {
			do {
				k = rand()%N;
			}while(a[heightb][k] == 'M');
			a[heightb][k] = 'M';
			s[i].ship_column = k;
			s[i].ship_shoot_row = heightb;
			if(diff == 1) {
				s[i].life = 1;
			}
			else
				s[i].life = rand()%L+1;
			s[i].value = 5 * s[i].life;
			if (s[i].life == 3)
				bold_print3(heightb, s[i].ship_column,a[heightb][s[i].ship_column]);
			else
				mvprintw(row + heightb * vert_space,column + s[i].ship_column * horiz_space, "%c", a[heightb][s[i].ship_column]);
		}
	}
}
void player_shootpvp(player_shippvp *player1) {
	int i;
	for (i = 0; i < N; i++) {
		if (player1->player_shoot_column[i] == -1) {
			player1->player_shoot_column[i] = player1->column;
			player1->player_ammo_reach[i] = player1->row - 1;
			return;
		}
	}
}
void player2_shoot(player_shippvp *player1) {
	int i;
	for (i = 0; i < N; i++) {
		if (player1->player_shoot_column[i] == -1) {
			player1->player_shoot_column[i] = player1->column;
			player1->player_ammo_reach[i] = player1->row + 1;
			return;
		}
	}
}
void player1_ammo_forward(char a[][N], enemy_ship s[M],player_shippvp *player1, enemy_ship prev[M], player_shippvp player2) {
	int i, j;
	for (i = 0; i < N; i++) {
		if (player1->player_shoot_column[i] != -1) {
			if (player1->player_ammo_reach[i] != N - 1) {
				a[player1->player_ammo_reach[i]][player1->player_shoot_column[i]] = ' ';
				mvprintw(row + player1->player_ammo_reach[i] * vert_space, column + player1->player_shoot_column[i] * horiz_space, "%c", a[player1->player_ammo_reach[i]][player1->player_shoot_column[i]]);
			}
			if (player1->player_ammo_reach[i] - 1 <= heightb) {
				for (j = 0; j < enemy_ships_number3 + intra_diff3; j++) {
					if (s[j].ship_column == player1->player_shoot_column[i]) {
						manage_hit3(a, i, j, s, prev, player1, player2);
						j = M;
					}
				}
				player1->player_shoot_column[i] = -1;
				player1->player_no_of_shoots--;
			}
			else {
				player1->player_ammo_reach[i]--;
				a[player1->player_ammo_reach[i]][player1->player_shoot_column[i]] = player1->missile;
				attron(COLOR_PAIR(4));
				bold_print3(player1->player_ammo_reach[i], player1->player_shoot_column[i], a[player1->player_ammo_reach[i]][player1->player_shoot_column[i]]);
				attroff(COLOR_PAIR(4));
			}
		}
	}
}
void player2_ammo_downward(char a[][N], enemy_ship s[M], player_shippvp * player1, enemy_ship prev[M], player_shippvp player2) {
	int i, j;
	for (i = 0; i < N; i++) {
		if (player1->player_shoot_column[i] != -1) {
			if (player1->player_ammo_reach[i] != N / 2 + 1) {
				a[player1->player_ammo_reach[i]][player1->player_shoot_column[i]] = ' ';
				mvprintw(row + player1->player_ammo_reach[i] * vert_space, column + player1->player_shoot_column[i] * horiz_space, "%c", a[player1->player_ammo_reach[i]][player1->player_shoot_column[i]]);
			}
			if (player1->player_ammo_reach[i] == heightb - 1) {
				for (j = 0; j < enemy_ships_number3 + intra_diff3; j++) {
					if (s[j].ship_column == player1->player_shoot_column[i]) {
						manage_hit3(a, i, j, s, prev, player1, player2);
						j = M;
					}
				}
				player1->player_shoot_column[i] = -1;
				player1->player_no_of_shoots--;
			}
			else {
				if (player1->player_ammo_reach[i] < N / 2) {
					player1->player_ammo_reach[i]++;
					a[player1->player_ammo_reach[i]][player1->player_shoot_column[i]] = player1->missile;
					attron(COLOR_PAIR(3));
					bold_print3(player1->player_ammo_reach[i], player1->player_shoot_column[i], a[player1->player_ammo_reach[i]][player1->player_shoot_column[i]]);
					attroff(COLOR_PAIR(3));
				}
			}
		}
	}
}
void manage_hit3(char a[][N], int i, int j, enemy_ship s[M], enemy_ship prev[M], player_shippvp * player_a, player_shippvp player_b) {
	if (s[j].life == 1) {
		player_a->points = player_a->points + s[j].value;
		delete_enemy_ship3(a, j, s, prev);
		attron(A_BOLD);
	} else {
		s[j].life--;
	}
}
void delete_enemy_ship3(char a[][N], int j, enemy_ship s[M], enemy_ship prev[M]) {
	int i;
	if (s[j].ship_shoot_row != N - 1) {
		for (i = 0; i < enemy_ships_number3 + intra_diff3; i++) {
			if (prev[i].ship_column == -1) {
				prev[j].ship_shoot_row = s[j].ship_shoot_row;
				prev[j].ship_column = s[j].ship_column;
				i = M;
			}
		}
	}
	a[heightb][s[j].ship_column] = ' ';
	mvprintw(row + heightb * vert_space, column + s[j].ship_column * horiz_space, "%c", a[heightb][s[j].ship_column]);
	s[j].ship_column = -1;
	enemy_ships_create3(a, s);
}
void player_shoots_sortpvp(player_shippvp *player1) {
	int i, j, higher;
	for (i = 0; i < N - 1; i++) {
		for (j = i + 1; j < N; j++) {
			if ((player1->player_shoot_column[i] == player1->player_shoot_column[j]) && (player1->player_ammo_reach[i] > player1->player_ammo_reach[j])) {
				higher = player1->player_ammo_reach[i];
				player1->player_ammo_reach[i] = player1->player_ammo_reach[j];
				player1->player_ammo_reach[j] = higher;
			}
		}
	}
}
