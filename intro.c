#include "intro.h"
#include "options.h"
int main() {
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
			case KEY_DOWN:
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
		if(choice != 0)
			break;
	}
	clrtoeol();
	refresh();
	if(!(strcmp(ch[rev - 1], "New game")))
		main();
	if(!(strcmp(ch[rev - 1], "Options")))
		setting();
	if(!(strcmp(ch[rev - 1], "About game")))
		abou();
	if(!(strcmp(ch[rev - 1], "Exit"))) {
		endwin();		
		exit(0);
	}
	getch();
	endwin();
}
void pri_menu(WINDOW *w,int rev) {
	int y = -2;
	box(w, 2, 2);
	getmaxyx(w, par_y, par_x);
	for(int i = 0; i < 5; i++) {
		if(rev == i + 1) {
			wattron(w, A_REVERSE);
			mvwprintw(w, par_y / 2 + y, par_x / 2 - 6, "%s", ch[i]);
			wattroff(w, A_REVERSE);
			refresh();		
		}
		else
			mvwprintw(w, par_y / 2 + y, par_x / 2 - 6, "%s", ch[i]);
		++y;
	}
	wrefresh(w);
}
void abou(void){
	clear();
	mvprintw(par_y / 2 - 5, par_x / 2 - 35, "Hello friends!!");
	mvprintw(par_y / 2 - 4, par_x / 2 - 35, "-This is a simple shooting game created using c language");
	mvprintw(par_y / 2 - 3, par_x / 2 - 35, "-You have to navigate your ship using up, down, right and left arrow keys");
	mvprintw(par_y / 2 - 2, par_x / 2 - 35, "-Use spacebar to shoot");
	mvprintw(par_y / 2 - 1, par_x / 2 - 35, "-Avoid being hit by enemy missiles");	
	mvprintw(par_y / 2, par_x / 2 - 35, "-Press esc to exit");	
	refresh();
	getch();
	main();
}
