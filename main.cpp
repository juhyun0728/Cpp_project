#include <ncurses.h>
#include <stdlib.h>
#include <iostream>
#define N 10
using namespace std;
#include "pushBox_H.h"

extern bool clearStage;
extern bool want_play;
extern int lev;

int main()
{
	pushBox a;
	int ch;
	initscr();
	resize_term(30, 40);
	noecho();
	keypad(stdscr,TRUE);

	curs_set(0);

	if (!has_colors())
	{
		endwin();
		printf("ERROR INITIALISING COLORS.n");
		exit(1);
	}
	start_color();
	a.palette();

	while (1)
	{
		if (want_play)
		{
			a.Level(lev);
			while((ch=getch())&&(clearStage!=true))
			{
				a.Play(ch);
				if (ch=='q' || ch=='Q')
				{
					clear();
					break;
				}
			}

			if (clearStage) a.clear_lev();
		}
		else a.HOME(ch);
	}

	endwin();
	return 0;
}
