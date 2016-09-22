#include"options.h"
int par_x, par_y;
char *ch1[] = { "Easy", "Medium", "Hard"};
int setting() {
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
	pri_menu1(w, rev);
	while(1) {
		input = wgetch(w);
		switch(input) {
			case KEY_UP:
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
			case 10:
				choice = rev;
				break;
			case 27:
				main();
			default:
				refresh();				
				break;
		}
		pri_menu1(w, rev);
		if(choice != 0)
			break;
	}
	clrtoeol();
	refresh();
	getch();
	endwin();
	return 0;
}
void pri_menu1(WINDOW *w,int rev) {
	int y = 0;
	box(w, 2, 2);
	getmaxyx(w, par_y, par_x);
	for(int i = 0; i < 3; i++) {
		if(rev == i + 1) {
			wattron(w, A_REVERSE);
			mvwprintw(w, par_y / 2 + y , par_x / 2 - 4, "%s", ch1[i]);
			wattroff(w, A_REVERSE);
			refresh();		
		}
		else
			mvwprintw(w, par_y / 2 + y, par_x / 2 - 4, "%s", ch1[i]);
		++y;
	}
	wrefresh(w);
}
