#include "main.h"
int main(int argc, char *argv[]) {
	if(argc == 2) {
		if(((strcmp(argv[1], "--help")) == 0) || ((strcmp(argv[1], "-h")) == 0)) {
			printf("Usage: ./program [OPTION]\n");
			printf("Options available\n  (1) --help (or) -h \n\tPrint help message and exit\n");
			printf("Report bugs to prathmesh.mungarwadi@gmail.com\n"); 
			exit(0);
		}
		else {
			printf("Usage: ./program [OPTIONS]\n");
			printf("Options available\n\t--help\n");
			exit(0);
		}
	}
	WINDOW *w;
	fp = fopen( "Highscore.txt", "r");
	if(fp == NULL) {
		highscore = 0;
		money = 0;
	}
	else {
		fscanf(fp, "%d", &highscore);
		fscanf(fp, "%d", &money);
		fclose(fp);
	}
	int rev = 1;
	int choice = 0;	
	int input;
	initscr();
	noecho();
	curs_set(0);
	getmaxyx(stdscr, par_y, par_x);
	w = newwin(par_y, par_x, 0, 0);
	box(w, 0, 0);
	keypad(w, TRUE);
	start_color();
	/*init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_RED);
	bkgd(COLOR_PAIR(1));
	wbkgdset(w, COLOR_PAIR(2));*/
	//You can use color if you want
	pri_menu(w, rev);
	while(1) {
		input = wgetch(w);
		switch(input) {
			case KEY_UP:
				if(rev == 1)
					rev = 5;
				else
					--rev;
				break;
			case 'k':
				if(rev == 1)
					rev = 5;
				else
					--rev;
				break;
			case KEY_DOWN:
				if(rev == 5)
					rev = 1;
				else
					++rev;
				break;
			case 'j':
				if(rev == 5)
					rev = 1;
				else
					++rev;
				break;
			case 10:
				choice = rev;
				break;
			case 27:
				endwin();
				exit(0);
			default:
				break;
		}
		pri_menu(w, rev);
		clrtoeol();
		refresh();
		if(choice == 1) {
			mode();
			pri_menu(w, 1);
			choice = 0;
		}
		if(choice == 2) {
			weapon();
			pri_menu(w, 2);
			choice = 0;
		}
		if(choice == 3) {
			setting();
			pri_menu(w, 3);
			choice = 0;
		}
		if(choice == 4) {
			abou();
			pri_menu(w, 4);
			choice = 0;
		}
		if(choice == 5) {
			endwin();		
			exit(0);
			choice = 0;
		}
	}
	getch();
	endwin();
}
void pri_menu(WINDOW *w, int rev) {
	int y = -2, i;
	box(w, 2, 2);
	getmaxyx(w, par_y, par_x);
	for(i = 0; i < 5; i++) {
		if(rev == i + 1) {
			wattron(w, A_REVERSE);
			mvwprintw(w, par_y / 2 + y, par_x / 2 - strlen(ch[i]) / 2, "%s", ch[i]);
			wattroff(w, A_REVERSE);
			refresh();		
		}
		else
			mvwprintw(w, par_y / 2 + y, par_x / 2 - strlen(ch[i]) / 2, "%s", ch[i]);
		++y;
	}
	wrefresh(w);
}
void abou(void){
	int ch;
	clear();
	mvprintw(par_y / 2 - 5, par_x / 2 - 35, "Hello friends!!");
	mvprintw(par_y / 2 - 4, par_x / 2 - 35, "-This is a simple shooting game created using c language");
	mvprintw(par_y / 2 - 3, par_x / 2 - 35, "-You have to navigate your ship using up, down, right and left arrow keys");
	mvprintw(par_y / 2 - 2, par_x / 2 - 35, "-Use spacebar to shoot");
	mvprintw(par_y / 2 - 1, par_x / 2 - 35, "-Avoid being hit by enemy missiles");	
	mvprintw(par_y / 2, par_x / 2 - 35, "-Press esc to exit");	
	mvprintw(par_y - 2, 1, "Press q to go back or m to see modes or c to see controls or l to see difficulty levels");
	ch = getch();
	while(ch != 'q') {
		switch(ch) {
			case 'q':
				return;
			case 'm':
				clear();
				mvprintw(par_y / 2 - 4, par_x / 2 - 35, "-The game has three modes to play");
				mvprintw(par_y / 2 - 3, par_x / 2 - 35, "--Single Player Mode");
				mvprintw(par_y / 2 - 2, par_x / 2 - 35, "--Two Player Mode");
				mvprintw(par_y / 2 - 1, par_x / 2 - 35, "--Player vs Player Mode");
				mvprintw(par_y - 2, 1, "Press q to go back or m to see modes or c to see controls or l to see difficulty levels");
				refresh();
				ch = getch();
				break;
			case 'c':
				clear();
				mvprintw(par_y / 3 - 4, par_x / 2 - 35, "-Single Player Mode Controls");
				mvprintw(par_y / 3 - 3, par_x / 2 - 35, "		--Use up, down, left and right arrow to move your ship");
				mvprintw(par_y / 3 - 2, par_x / 2 - 35, "		--Press space to shoot");
				mvprintw(par_y / 3 - 1, par_x / 2 - 35, "-Two Player Mode");
				mvprintw(par_y / 3, par_x / 2 - 35, "	--Player 1 controls");
				mvprintw(par_y / 3 + 1, par_x / 2 - 35, "		--Press space to shoot");
				mvprintw(par_y / 3 + 2, par_x / 2 - 35, "		--Use up, down, left and right arrow to move your ship");
				mvprintw(par_y / 3 + 3, par_x / 2 - 35, "	--Player 2 controls");
				mvprintw(par_y / 3 + 4, par_x / 2 - 35, "		--Use w, a, s and d keys to move your ship");
				mvprintw(par_y / 3 + 5, par_x / 2 - 35, "		--Press f to shoot");
				mvprintw(par_y / 3 + 6, par_x / 2 - 35, "-Player vs Player Mode");
				mvprintw(par_y / 3 + 7, par_x / 2 - 35, "	--Player 1 controls");
				mvprintw(par_y / 3 + 8, par_x / 2 - 35, "		--Press space to shoot");
				mvprintw(par_y / 3 + 9, par_x / 2 - 35, "		--Use up, down, left and right arrow to move your ship");
				mvprintw(par_y / 3 + 10, par_x / 2 - 35, "	--Player 2 controls");
				mvprintw(par_y / 3 + 11, par_x / 2 - 35, "		--Use a, w, d and s keys to move your ship");
				mvprintw(par_y / 3 + 12, par_x / 2 - 35, "		--Press f to shoot");
				mvprintw(par_y - 2, 1, "Press q to go back or m to see modes or c to see controls or l to see difficulty levels");
				refresh();
				ch = getch();
				break;
			case 'l':
				clear();
				mvprintw(par_y / 2 - 3, par_x / 2 - 40, "There are three difficulty levels");
				mvprintw(par_y / 2 - 2, par_x / 2 - 40, "	-Easy");
				mvprintw(par_y / 2 - 1, par_x / 2 - 40, "	--Your ship can take more damage and enemies can be killed by one missile");
				mvprintw(par_y / 2, par_x / 2 - 40, "	-Medium");
				mvprintw(par_y / 2 + 1, par_x / 2 - 40, "	--Your ship can take lesser damage but enemies require more missiles to be killed");
				mvprintw(par_y / 2 + 2, par_x / 2 - 40, "	-Hard");
				mvprintw(par_y / 2 + 3, par_x / 2 - 40, "	--Your ship can take only one hit and enemies require more than one missile");
				mvprintw(par_y - 2, 1, "Press q to go back or m to see modes or c to see controls or l to see difficulty levels");
				refresh();
				ch = getch();
				break;
			default:
				ch = getch();
				break;
		}
	}

}
void setting(void) {
	WINDOW *w;
	int rev = 1;
	int choice = 0;	
	int input;	
	initscr();
	noecho();
	curs_set(0);
	getmaxyx(stdscr, par_y, par_x);
	w = newwin(par_y, par_x, 0, 0);
	box(w, 2, 2);
	/*start_color();
	init_pair(1, COLOR_WHITE, COLOR_YELLOW);
	init_pair(2, COLOR_WHITE, COLOR_RED);
	wbkgdset(w, COLOR_PAIR(1));*/
	keypad(w, TRUE);
	pri_menu1(w, rev);
	while(1) {
		input = wgetch(w);
		switch(input) {
			case KEY_UP:
				if(rev == 1)
					rev = 4;
				else
					--rev;
				break;
			case 'k':
				if(rev == 1)
					rev = 4;
				else
					--rev;
				break;
			case KEY_DOWN:
				if(rev == 4)
					rev = 1;
				else
					++rev;
				break;
			case 'j':
				if(rev == 4)
					rev = 1;
				else
					++rev;
				break;
			case 10:
				choice = rev;
				break;
			case 27:
				return;
			default:
				refresh();
				break;
		}
		pri_menu1(w, rev);
		if(choice != 0)
			break;
	}
	if(choice == 1)
		difficulty = 1;
	if(choice == 2)
		difficulty = 2;
	if(choice == 3)
		difficulty = 3;
	if(choice == 4) {
		fp = fopen("Highscore.txt", "w+");
		fprintf(fp, "0");
		highscore = 0;
		money = 0;
		fclose(fp);
		endwin();
		return;
	}
	clrtoeol();
	refresh();
	getch();
	endwin();
	return;
}
void pri_menu1(WINDOW *w, int rev) {
	int y = 0, i;
	box(w, 2, 2);
	getmaxyx(w, par_y, par_x);
	for(i = 0; i < 4; i++) {
		if(rev == i + 1) {
			wattron(w, A_REVERSE);
			mvwprintw(w, par_y / 2 + y , par_x / 2 - strlen(ch1[i]) / 2, "%s", ch1[i]);
			wattroff(w, A_REVERSE);
			refresh();		
		}
		else
			mvwprintw(w, par_y / 2 + y, par_x / 2 - strlen(ch1[i]) / 2, "%s", ch1[i]);
		++y;
	}
	wrefresh(w);
}
void mode(void) {
	WINDOW *w;
	int rev = 1;
	int choice = 0;	
	int input;	
	initscr();
	noecho();
	curs_set(0);
	getmaxyx(stdscr, par_y, par_x);
	w = newwin(par_y, par_x, 0, 0);
	box(w, 2, 2);
	keypad(w, TRUE);
	pri_menu2(w, rev);
	while(1) {
		input = wgetch(w);
		switch(input) {
			case KEY_UP:
				if(rev == 1)
					rev = 3;
				else
					--rev;
				break;
			case 'k':
				if(rev == 1)
					rev = 3;
				else
					--rev;
				break;
			case KEY_DOWN:
				if(rev == 3)
					rev = 1;
				else
					++rev;
				break;
			case 'j':
				if(rev == 3)
					rev = 1;
				else
					++rev;
				break;
			case 10:
				choice = rev;
				break;
			case 27:
				endwin();
				return;
			default:
				refresh();
				break;
		}
		pri_menu2(w, rev);
		if(choice != 0)
			break;
	}
	if(choice == 1) {
		one_player();
		return;	
	}
	if(choice == 2) {
		two_player();
		return;
	}
	if(choice == 3) {
		playervsplayer();
		return;
	}
	clrtoeol();
	refresh();
	getch();
	endwin();
	return;
}
void pri_menu2(WINDOW *w, int rev) {
	int y = 0, i;
	box(w, 2, 2);
	getmaxyx(w, par_y, par_x);
	for(i = 0; i < 3; i++) {
		if(rev == i + 1) {
			wattron(w, A_REVERSE);
			mvwprintw(w, par_y / 2 + y , par_x / 2 - 4, "%s", ch2[i]);
			wattroff(w, A_REVERSE);
			refresh();		
		}
		else
			mvwprintw(w, par_y / 2 + y, par_x / 2 - 4, "%s", ch2[i]);
		++y;
	}
	wrefresh(w);
}
void weapon(void) {
	WINDOW *w;
	int rev = 1;
	int choice = 0;	
	int input;	
	initscr();
	noecho();
	curs_set(0);
	getmaxyx(stdscr, par_y, par_x);
	w = newwin(par_y, par_x, 0, 0);
	box(w, 2, 2);
	keypad(w, TRUE);
	pri_menu3(w, rev);
	while(1) {
		input = wgetch(w);
		switch(input) {
			case KEY_UP:
				if(rev == 1)
					rev = 2;
				else
					--rev;
				break;
			case 'k':
				if(rev == 1)
					rev = 2;
				else
					--rev;
				break;
			case KEY_DOWN:
				if(rev == 2)
					rev = 1;
				else
					++rev;
				break;
			case 'j':
				if(rev == 2)
					rev = 1;
				else
					++rev;
				break;
			case 10:
				choice = rev;
				break;
			case 27:
				return;
			default:
				refresh();
				break;
		}
		pri_menu3(w, rev);
		if(choice != 0)
			break;
	}
	if(choice == 1) {
		missile = '|';
	}
	if(choice == 2) {
		if(money > 200) {
			missile = '^';
			money = money - 200;
		}
		else {
			mvprintw(par_y - 2 , 2, "You don't have enough Star coins (%d)", money);
		}			
	}
	clrtoeol();
	refresh();
	getch();
	endwin();
	return;
}
void pri_menu3(WINDOW *w, int rev) {
	int y = 0, i;
	box(w, 2, 2);
	getmaxyx(w, par_y, par_x);
	for(i = 0; i < 2; i++) {
		if(rev == i + 1) {
			wattron(w, A_REVERSE);
			mvwprintw(w, par_y / 2 + y, par_x / 2 - 4, "%s", ch3[i]);
			wattroff(w, A_REVERSE);
			refresh();		
		}
		else
			mvwprintw(w, par_y / 2 + y, par_x / 2 - 4, "%s", ch3[i]);
		++y;
	}
	wrefresh(w);
}
void one_player(void) {
	clear();
	int i;
	char a[N][N];
	enemy_ship s[M], prev[M];
	player_ship player1;

	if(difficulty == 1) {
		player1.player_life = 3;
	}
	else if(difficulty == 2) {
		player1.player_life = 2;
	}
	else
		player1.player_life = 1;
	player1.points = 0;	
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
		while(!kbhit()) {
			change_refresh_time(player1);
			refresh();
			attron(A_BOLD);
			if(difficulty == 3) {
				attron(COLOR_PAIR(1));
				mvprintw(max_y - 2, 50, "Level : Hard");
				refresh();
				attroff(COLOR_PAIR);
			}
			else if(difficulty == 2) {
				attron(COLOR_PAIR(3));
				mvprintw(max_y - 2, 50, "Level : Medium");
				refresh();
				attroff(COLOR_PAIR);
			}
			else if(difficulty == 1) {
				attron(COLOR_PAIR(2));
				mvprintw(max_y - 2, 50, "Level : Easy");
				refresh();
				attroff(COLOR_PAIR);
			}
			attroff(A_BOLD);
			if (player1.points < 800) {
				if (player1.points >= 100) {
					change_no_of_ships(a, s, player1);
					if (player1.points >= 150)
						increase_difficulty(a, s, &player1, prev);
				}
			}
			if (player_no_of_shoots != 0)
				player_ammo_forward(a, s, &player1, prev);
			enemy_shoots(a, s, &player1);
			prev_shoots_recover(a, prev, &player1);
			mvprintw(max_y - 2, 30, "Highscore : %d", highscore);
			refresh();
		}
		move(row + i * vert_space, column + player1.column * horiz_space);
		switch (getch()) {
		case KEY_LEFT:
			if (player1.column > 0) {
				a[i][player1.column] = ' ';
				printw("%c", a[i][player1.column]);
				player1.column--;
				a[i][player1.column] = '*';
				mvprintw(row + i * vert_space, column + player1.column * horiz_space, "%c", a[i][player1.column]);
			}
			break;
		case KEY_RIGHT:
			if (player1.column < N - 1) {
				a[i][player1.column] = ' ';
				printw("%c", a[i][player1.column]);
				player1.column++;
				a[i][player1.column] = '*';
				mvprintw(row + i * vert_space, column + player1.column * horiz_space, "%c", a[i][player1.column]);
			}
			break;
		case KEY_UP:
			if (i > height + 1) {
				a[i][player1.column] = ' ';
				printw("%c", a[i][player1.column]);
				i--;
				player1.row = i;
				a[i][player1.column] = '*';
				mvprintw(row + i * vert_space, column + player1.column * horiz_space, "%c", a[i][player1.column]);
			}
			break;
		case KEY_DOWN:
			if (i < N - 1) {
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
			player_shoots_sort(&player1);
			player_no_of_shoots++;
			break;
		case 27:
			endwin();
			return;
		default:
			break;
		}
	}while(win);
	if(player1.points > highscore) {
		fp = fopen("Highscore.txt", "w+");
		fprintf(fp, "%d ", player1.points);
		fprintf(fp, "%d", player1.points + money);
		fclose(fp);	
	}
	else {
		fp = fopen("Highscore.txt", "w+");
		fprintf(fp, "%d ", highscore);
		fprintf(fp, "%d", player1.points + money);
		fclose(fp);	
	}
	game_end(player1);
	win = 1;
	return;
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
	if((max_x < 20) || (max_y < 20)) {
		printf("Increase the screen size to play the game\n");
		exit(0);
	}
	return 0;
}
void game_end(player_ship player1) {
	char exitmsg[] = "Better luck next time";
	wtimeout(stdscr, -1);
	clear();
	attron(COLOR_PAIR(rand() % 6 + 1));
	attron(A_BOLD);
	if (!win) {
		mvprintw(max_y / 2, (max_x - strlen("You scored %d points!")) / 2, "You scored %d points!", player1.points);
		mvprintw(max_y / 2 - 1, (max_x - strlen(exitmsg)) / 2, "%s", exitmsg);
	}	
	refresh();
	sleep(3);
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
void change_refresh_time(player_ship player1) {
	if (player1.points >= 400) {
		usleep(60000);
		return;
	}
	if ((player1.points <= 400) && (player1.points > 100)) {
		usleep(90000);
		return;
	}
	if ((player1.points <= 100) && (player1.points > 0)) {
		usleep(150000);
		return;
	}
	if (player1.points == 0) {
		usleep(180000);
		return;
	}
}
void increase_difficulty(char a[][N], enemy_ship s[M], player_ship *player1, enemy_ship prev[M]) {
	int prev_height = height, i, j;
	if (player1->points >= 800) {
		height = 5;
	} else {
		if (player1->points >= 650) {
			height = 4;
		} else {
			if (player1->points >= 500) {
				height = 3;
			} else {
				if (player1->points >= 300) {
					height = 2;
				} else {
					if (player1->points >= 150)
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
					bold_print(height, s[i].ship_column, a[height][s[i].ship_column]);
				else
					mvprintw(row + height * vert_space, column + s[i].ship_column * horiz_space, "%c", a[height][s[i].ship_column]);
			} else {
				if (s[i].life != 1) {
					a[height][s[i].ship_column] = 'M';
					mvprintw(row + height * vert_space, column + s[i].ship_column * horiz_space, "%c", a[height][s[i].ship_column]);
				}
				for (j = 0; j < N; j++) {
					if ((player1->player_shoot_column[j] == s[i].ship_column) && (player1->player_ammo_reach[j] == height)) {
						manage_hit(a, j, i, s, prev, player1);
						j = N;
					}
				}
				player1->player_shoot_column[j] = -1;
				player_no_of_shoots--;
			}
		}
	}
}
void change_no_of_ships(char a[][N], enemy_ship s[M], player_ship player1) {
	int prev_intra_diff = intra_diff;
	if (player1.points >= 750) {
		intra_diff = 5;
	} else {
		if (player1.points >= 600) {
			intra_diff = 4;
		} else {
			if (player1.points >= 450) {
				intra_diff = 3;
			} else {
				if (player1.points >= 250) {
					intra_diff = 2;
				} else {
					if (player1.points >= 100)
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
			} while(a[height][k] == 'M');
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
			}
			if (s[i].ship_shoot_row + 1 == N)
				s[i].ship_shoot_row = height;
		}
		s[i].ship_shoot_row++;
		if (a[s[i].ship_shoot_row + 1][s[i].ship_column] != missile) {
			a[s[i].ship_shoot_row][s[i].ship_column] = ':';
			attron(COLOR_PAIR(1));
			bold_print(s[i].ship_shoot_row, s[i].ship_column, a[s[i].ship_shoot_row][s[i].ship_column]);
			attroff(COLOR_PAIR);
		}
		else {
			if(difficulty == 1) {
				a[s[i].ship_shoot_row][s[i].ship_column] = ' ';
				mvprintw(row + s[i].ship_shoot_row * vert_space, column + s[i].ship_column * horiz_space, "%c", a[s[i].ship_shoot_row][s[i].ship_column]);
				s[i].ship_shoot_row = height;
			}	
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
void player_ammo_forward(char a[][N], enemy_ship s[M], player_ship *player1, enemy_ship prev[M]) {
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
						manage_hit(a, i, j, s, prev, player1);
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
void manage_hit(char a[][N], int i, int j, enemy_ship s[M], enemy_ship prev[M], player_ship *player) {
	if (s[j].life == 1) {
		player->points = player->points + s[j].value;
		delete_enemy_ship(a, j, s, prev);
		attron(COLOR_PAIR(3));
		attron(A_BOLD);
		mvprintw(max_y - 1, 1, "Points: %d", player->points);
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
			if (a[prev[i].ship_shoot_row + 1][prev[i].ship_column] != missile) {
				a[prev[i].ship_shoot_row][prev[i].ship_column] = ':';
				attron(COLOR_PAIR(1));
				bold_print(prev[i].ship_shoot_row, prev[i].ship_column,a[prev[i].ship_shoot_row][prev[i].ship_column]);
				attroff(COLOR_PAIR(1));
			}
			else {
				if(difficulty == 1) {
					a[prev[i].ship_shoot_row][prev[i].ship_column] = ' ';
					mvprintw(row + prev[i].ship_shoot_row * vert_space,column + prev[i].ship_column * horiz_space, "%c", a[prev[i].ship_shoot_row][prev[i].ship_column]);
					prev[i].ship_shoot_row = height;
				}	
			}

		}
		mvprintw(max_y - 2, 1, "Ship Damage: ");
		if(player1->player_life == 3) {
			attron(A_REVERSE);		
			mvprintw(max_y - 2, 14, "    ");
			attroff(A_REVERSE);
		}	
		else if(player1->player_life == 2) {
			attron(A_REVERSE);		
			mvprintw(max_y - 2, 16, "      ");
			attroff(A_REVERSE);
		}	
		else if(player1->player_life == 1) {
			attron(A_REVERSE);		
			mvprintw(max_y - 2, 18, "        ");
			attroff(A_REVERSE);
		}	
	}
}
void player_shoots_sort(player_ship *player1) {
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

void two_player(void) {
	clear();
	int i, j;
	char a[N][N];
	char ship1 = '*', ship2 = 'X';
	enemy_ship s[M], prev[M];
	player_shiptp player1, player2;
	if(difficulty == 1) {
		player1.player_life = 5;
		player2.player_life = 5;	
	}
	else if(difficulty == 2) {
		player1.player_life = 3;
		player2.player_life = 3;
	}
	else if(difficulty == 3){
		player1.player_life = 1;
		player2.player_life = 1;
	}	
	srand(time(NULL));
	initiate();
	space_create2(a);
	for (i = 0; i < M; i++) {
		s[i].ship_column = -1;
		prev[i].ship_column = -1;
	}
	enemy_ships_create2(a, s);
	for (i = 0; i < N; i++) {
		player1.player_shoot_column[i] = -1;
		player2.player_shoot_column[i] = -1;
	}
	player1.column = 0;
	player1.row = N - 1;
	player2.column = 1;
	player2.row = N -1;
	i--;
	j = i;
	a[i][player1.column] = ship1;
	a[j][player2.column] = ship2;
	player1.player_no_of_shoots = 0;
	player2.player_no_of_shoots = 0;
	player1.points = 0;
	player2.points = 0;
	player1.missile = '|';
	player2.missile = '^';	
	bold_print2(i, player1.column, a[i][player1.column]);
	bold_print2(j, player2.column, a[j][player2.column]);
	do {
		while(!kbhit()) {
			if (player1.player_no_of_shoots != 0)
				player_ammo_forward2(a, s, &player1, prev);
			if (player2.player_no_of_shoots != 0)
				player_ammo_forward2(a, s, &player2, prev);
			enemy_shoots2(a, s, &player1);
			enemy_shoots2(a, s, &player2);
			prev_shoots_recover2(a, prev, &player1);
			prev_shoots_recover2(a, prev, &player2);
			change_refresh_time2(player1, player2);
			refresh();
		}
		move(row + i * vert_space, column + player1.column * horiz_space);
		switch (getch()) {
		case KEY_LEFT:
			if ((player1.column > 0) && (a[i][player1.column - 1] != ':')) {
				a[i][player1.column] = ' ';
				printw("%c", a[i][player1.column]);
				player1.column--;
				a[i][player1.column] = ship1;
				mvprintw(row + i * vert_space, column + player1.column * horiz_space, "%c", a[i][player1.column]);
			}
			break;
		case KEY_RIGHT:
			if ((player1.column < N - 1) && (a[i][player1.column + 1] != ':')) {
				a[i][player1.column] = ' ';
				printw("%c", a[i][player1.column]);
				player1.column++;
				a[i][player1.column] = ship1;
				mvprintw(row + i * vert_space, column + player1.column * horiz_space, "%c", a[i][player1.column]);
			}
			break;
		case KEY_UP:
			if ((i > height + 1) && (a[i][player1.column + 1] != ':')) {
				a[i][player1.column] = ' ';
				printw("%c", a[i][player1.column]);
				i--;
				player1.row = i;
				a[i][player1.column] = ship1;
				mvprintw(row + i * vert_space, column + player1.column * horiz_space, "%c", a[i][player1.column]);
			}
			break;
		case KEY_DOWN:
			if ((i < N - 1) && (a[i][player1.column + 1] != ':')) {
				a[i][player1.column] = ' ';
				printw("%c", a[i][player1.column]);
				i++;
				player1.row = i;
				a[i][player1.column] = ship1;
				mvprintw(row + i * vert_space, column + player1.column * horiz_space, "%c", a[i][player1.column]);
			}
			break;

		case 32:
			player_shoots2(&player1);
			player_shoots_sort2(&player1);
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
			if ((j > height + 1) && (a[j][player2.column + 1] != ':')) {
				a[j][player2.column] = ' ';
				mvprintw(row + j * vert_space, column + player2.column * horiz_space, "%c", a[j][player2.column]);
				j--;
				player2.row = j;
				a[j][player2.column] = ship2;
				mvprintw(row + j * vert_space, column + player2.column * horiz_space, "%c", a[j][player2.column]);
			}
			break;
		case 's':
			if ((i < N - 1) && (a[i][player1.column + 1] != ':')) {
				a[j][player2.column] = ' ';
				mvprintw(row + j * vert_space, column + player2.column * horiz_space, "%c", a[j][player2.column]);
				j++;
				player2.row = j;
				a[j][player2.column] = ship2;
				mvprintw(row + j * vert_space, column + player2.column * horiz_space, "%c", a[j][player2.column]);
			}
			break;
		case 'f':
			player_shoots2(&player2);
			player_shoots_sort2(&player2);			
			player2.player_no_of_shoots++;
			break;
		case 27:
			endwin();
			return;
		}
		if ((player1.points < 800) || (player2.points < 800)) {
			if ((player1.points >= 100) || (player2.points >= 100)) {
				change_no_of_ships2(a, s, player1.points, player2.points);
				if ((player1.points >= 150) || (player2.points >=150))
					increase_difficulty2(a, s, &player1, prev, player1.points, player2.points);
			}
		}
	}while(win);
	game_end2(&player1, &player2);
	win = 1;
	return;
}
void game_end2(player_shiptp *player1, player_shiptp *player2) {
	char exitmsg[] = "Better luck next time";
	wtimeout(stdscr, -1);
	clear();
	attron(A_BOLD);
	if (!win) {
		attron(COLOR_PAIR(3));
		mvprintw(max_y / 2, (max_x - strlen("Player1 scored %d points!")) / 2, "Player1 scored %d points!", player1->points);
		attroff(COLOR_PAIR(3));
		attron(COLOR_PAIR(4));
		mvprintw(max_y / 2 + 1, (max_x - strlen("Player2 scored %d points!")) / 2, "Player2 scored %d points!", player2->points);
		attroff(COLOR_PAIR(4));
		mvprintw(max_y / 2 - 1, (max_x - strlen(exitmsg)) / 2, "%s", exitmsg);
	}	
	refresh();
	sleep(3);
	attroff(A_BOLD);
	endwin();
}
void space_create2(char a[][N]) {
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
void bold_print2(int i, int k, char c) {
	attron(A_BOLD);
	mvprintw(row + i * vert_space, column + k * horiz_space, "%c", c);
	attroff(A_BOLD);
}
void change_refresh_time2(player_shiptp player1, player_shiptp player2) {
	if ((player1.points >= 800) || (player2.points >= 800)) {
		usleep(50000);
		return;
	}
	if ((player1.points >= 400) || (player2.points >= 400)) {
		usleep(60000);
		return;
	}
	if ((player1.points >= 100) && (player2.points >= 100)) {
		usleep(90000);
		return;
	}
	if (((player1.points <= 100) && (player1.points >= 50)) || ((player2.points <= 100) && (player2.points >= 50))) {
		usleep(100000);
		return;
	}
	if(((player1.points > 0) && (player1.points < 50)) || ((player2.points > 0) && (player2.points < 50))) {
		usleep(140000);
		return;
	}
	if ((player1.points == 0) || (player2.points == 0)) {
		usleep(180000);
		return;
	}
}
void increase_difficulty2(char a[][N], enemy_ship s[M], player_shiptp *player, enemy_ship prev[M], int points1, int points2) {
	int prev_height = height, i, j;
	if ((points1 >= 800) || (points2 >= 800)) {
		height = 5;
	}
	else {
		if ((points1 >= 650) || (points2 >= 650)) {
			height = 4;
		}
		else {
			if ((points1 >= 500) || (points2 >= 500)) {
				height = 3;
			}
			else {
				if ((points1 >= 300) || (points2 >= 300)) {
					height = 2;
				}
				else {
					if ((points1 >= 150) || (points2 >= 150))
						height = 1;
				}
			}
		}
	}
	if (height != prev_height) {
		for (i = 0; i < enemy_ships_number + intra_diff; i++) {
			a[height - 1][s[i].ship_column] = ' ';
			mvprintw(row + (height - 1) * vert_space, column + s[i].ship_column * horiz_space, "%c", a[height - 1][s[i].ship_column]);
			if (a[height][s[i].ship_column] != player->missile) {
				a[height][s[i].ship_column] = 'M';
				if (s[i].life == 3)
					bold_print2(height, s[i].ship_column,a[height][s[i].ship_column]);
				else
					mvprintw(row + height * vert_space, column + s[i].ship_column * horiz_space, "%c", a[height][s[i].ship_column]);
			} else {
				if (s[i].life != 1) {
					a[height][s[i].ship_column] = 'M';
					mvprintw(row + height * vert_space, column + s[i].ship_column * horiz_space, "%c", a[height][s[i].ship_column]);
				}
				for (j = 0; j < N; j++) {
					if ((player->player_shoot_column[j] == s[i].ship_column) && (player->player_ammo_reach[j] == height)) {
						manage_hit2(a, j, i, s, prev, player);
						j = N;
					}
				}
				player->player_shoot_column[j] = -1;
				player->player_no_of_shoots--;
			}
		}
	}
}
void change_no_of_ships2(char a[][N], enemy_ship s[M], int points1, int points2) {
	int prev_intra_diff = intra_diff;
	if ((points1 >= 750) || (points2 >= 750)){
		intra_diff = 5;
	} else {
		if ((points1 >= 600) || (points2 >= 600)) {
			intra_diff = 4;
		} else {
			if ((points1 >= 450) || (points2 >= 450)){
				intra_diff = 3;
			} else {
				if ((points1 >= 250) || (points2 >= 250)){
					intra_diff = 2;
				} else {
					if ((points1 >= 100) || (points2 >= 100))
						intra_diff = 1;
				}
			}
		}
	}
	if (intra_diff != prev_intra_diff)
		enemy_ships_create2(a, s);
}
void enemy_ships_create2(char a[][N], enemy_ship s[M]) {
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
				bold_print2(height, s[i].ship_column, a[height][s[i].ship_column]);
			else
				mvprintw(row + height * vert_space,column + s[i].ship_column * horiz_space, "%c", a[height][s[i].ship_column]);
		}
	}
}
void enemy_shoots2(char a[][N], enemy_ship s[M], player_shiptp *player) {
	int i;
	for (i = 0; i < enemy_ships_number + intra_diff; i++) {
		if (s[i].ship_shoot_row > height) {
			if (a[s[i].ship_shoot_row][s[i].ship_column] == ':') {
				a[s[i].ship_shoot_row][s[i].ship_column] = ' ';
				mvprintw(row + s[i].ship_shoot_row * vert_space,column + s[i].ship_column * horiz_space, "%c", a[s[i].ship_shoot_row][s[i].ship_column]);
			}
			if ((s[i].ship_column == player->column) && (s[i].ship_shoot_row == player->row)) {
				if(player->player_life == 1) {
					win = 0;
				}
				else
					--player->player_life;
				return;
			}
			if (s[i].ship_shoot_row + 1 == N)
				s[i].ship_shoot_row = height;
		}
		s[i].ship_shoot_row++;
		if (a[s[i].ship_shoot_row][s[i].ship_column] != player->missile) {
			a[s[i].ship_shoot_row][s[i].ship_column] = ':';
			attron(COLOR_PAIR(1));
			bold_print2(s[i].ship_shoot_row, s[i].ship_column, a[s[i].ship_shoot_row][s[i].ship_column]);
			attroff(COLOR_PAIR);
		}
		else {
			if(difficulty == 1) {
				a[s[i].ship_shoot_row][s[i].ship_column] = ' ';
				mvprintw(row + s[i].ship_shoot_row * vert_space,column + s[i].ship_column * horiz_space, "%c", a[s[i].ship_shoot_row][s[i].ship_column]);
				s[i].ship_shoot_row = height;
			}	
		}
	}
}
void player_shoots2(player_shiptp *player) {
	int i;
	for (i = 0; i < N; i++) {
		if (player->player_shoot_column[i] == -1) {
			player->player_shoot_column[i] = player->column;
			player->player_ammo_reach[i] = player->row - 1;
			return;
		}
	}
}
void player_ammo_forward2(char a[][N], enemy_ship s[M], player_shiptp *player, enemy_ship prev[M]) {
	int i, j;
	for (i = 0; i < N; i++) {
		if (player->player_shoot_column[i] != -1) {
			if (player->player_ammo_reach[i] != N - 1) {
				a[player->player_ammo_reach[i]][player->player_shoot_column[i]] = ' ';
				mvprintw(row + player->player_ammo_reach[i] * vert_space, column + player->player_shoot_column[i] * horiz_space, "%c", a[player->player_ammo_reach[i]][player->player_shoot_column[i]]);
			}
			if (player->player_ammo_reach[i] - 1 <= height) {
				for (j = 0; j < enemy_ships_number + intra_diff; j++) {
					if (s[j].ship_column == player->player_shoot_column[i]) {
						manage_hit2(a, i, j, s, prev, player);
						j = M;
					}
				}
				player->player_shoot_column[i] = -1;
				player->player_no_of_shoots--;
			} else {
				player->player_ammo_reach[i]--;
				a[player->player_ammo_reach[i]][player->player_shoot_column[i]] = player->missile;
				if(player->missile == '|') {
					attron(COLOR_PAIR(3));
					bold_print2(player->player_ammo_reach[i], player->player_shoot_column[i], a[player->player_ammo_reach[i]][player->player_shoot_column[i]]);
					attroff(COLOR_PAIR(3));
				}
				else if(player->missile == '^') {
					attron(COLOR_PAIR(4));
					bold_print2(player->player_ammo_reach[i], player->player_shoot_column[i], a[player->player_ammo_reach[i]][player->player_shoot_column[i]]);
					attroff(COLOR_PAIR(4));
				}
		
			}
		}
	}
}
void manage_hit2(char a[][N], int i, int j, enemy_ship s[M],enemy_ship prev[M], player_shiptp *player) {
	if (s[j].life == 1) {
		player->points = player->points + s[j].value;
		delete_enemy_ship2(a, j, s, prev);
		if(player->missile == '|') {
			attron(COLOR_PAIR(3));
			attron(A_BOLD);
			mvprintw(max_y - 1, 1, "Points: %d", player->points);
			attroff(COLOR_PAIR(3));
			attroff(A_BOLD);
		}
		else if(player->missile == '^') {	
			attron(COLOR_PAIR(4));
			attron(A_BOLD);
			mvprintw(max_y - 1, 15, "Points: %d", player->points);
			attroff(COLOR_PAIR(4));
			attroff(A_BOLD);
		}
	} else {
		s[j].life--;
	}
}
void delete_enemy_ship2(char a[][N], int j, enemy_ship s[M], enemy_ship prev[M]) {
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
	enemy_ships_create2(a, s);
}
void prev_shoots_recover2(char a[][N], enemy_ship prev[M], player_shiptp *player) {
	int i;
	for (i = 0; i < enemy_ships_number + intra_diff; i++) {
		if (prev[i].ship_column != -1) {
			if (a[prev[i].ship_shoot_row][prev[i].ship_column] == ':') {
				a[prev[i].ship_shoot_row][prev[i].ship_column] = ' ';
				mvprintw(row + prev[i].ship_shoot_row * vert_space,column + prev[i].ship_column * horiz_space, "%c", a[prev[i].ship_shoot_row][prev[i].ship_column]);
			}
			if ((prev[i].ship_column == player->column) && (prev[i].ship_shoot_row == player->row)) {
				if(player->player_life == 1) {
					win = 0;
				}
				else
					--player->player_life;				
				return;
			}
			if (prev[i].ship_shoot_row + 1 == N) {
				prev[i].ship_column = -1;
				return;
			}
			prev[i].ship_shoot_row++;
			if (a[prev[i].ship_shoot_row][prev[i].ship_column] != player->missile) {
				a[prev[i].ship_shoot_row][prev[i].ship_column] = ':';
				attron(COLOR_PAIR(1));
				bold_print2(prev[i].ship_shoot_row, prev[i].ship_column,a[prev[i].ship_shoot_row][prev[i].ship_column]);
				attroff(COLOR_PAIR(1));
			}
			else {
				if(difficulty == 1) {
					a[prev[i].ship_shoot_row][prev[i].ship_column] = ' ';
					mvprintw(row + prev[i].ship_shoot_row * vert_space,column + prev[i].ship_column * horiz_space, "%c", a[prev[i].ship_shoot_row][prev[i].ship_column]);
					prev[i].ship_shoot_row = height;
				}	
			}
		}
	}
}
void player_shoots_sort2(player_shiptp *player) {
	int i, j, higher;
	for (i = 0; i < N - 1; i++) {
		for (j = i + 1; j < N; j++) {
			if ((player->player_shoot_column[i] == player->player_shoot_column[j]) && (player->player_ammo_reach[i] > player->player_ammo_reach[j])) {
				higher = player->player_ammo_reach[i];
				player->player_ammo_reach[i] = player->player_ammo_reach[j];
				player->player_ammo_reach[j] = higher;
			}
		}
	}
}
