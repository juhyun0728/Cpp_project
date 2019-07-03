#include <ncurses.h>
#include <stdlib.h>
#include <iostream>
#define N 10
using namespace std;
#include "pushBox_H.h"

pushBox obj[N] = {};

extern bool clearStage=false;
extern bool want_play=false;
extern int lev = 0;

int wbox=0;
int goal=0;
int count=0;
int count_box=0;

pushBox g[N]={};

WINDOW *win, *home;

bool compare ( chtype *a, chtype *b, int size)
{
	for (int i=0; i<size; i++)
	{
		if (a[i]!=b[i]) return false;
	}
	return true;
}

void pushBox::isclear()
{
	chtype now[wbox]={};
	chtype goal[wbox];

	for (int i=0; i<wbox; i++)
	{
		goal[i]='x';
	}
	clearStage=false;

	for (int i=0; i<wbox; i++)
	{
		now[i] = (mvinch(obj[i+1].yP, obj[i+1].xP) & A_CHARTEXT);
	}
	if (compare(now, goal, wbox))
	{
		clearStage=true;
		lev++;
	}
}

void pushBox::clear_lev()
{
	win=newwin(5,14,9,13);
	wbkgd(win,COLOR_PAIR(4));
	wborder(win,'|', '|', '-', '-', '+', '+', '+', '+');
  	wattron(win,COLOR_PAIR(4));
  	wattroff(win,COLOR_PAIR(4));
	int ch;

	if (lev==5)
	{
		mvwprintw(win,1,2,"ALL CLEAR!");
		mvwprintw(win,2,2,"SCORE = %d",count);
		mvwprintw(win,3,4,">quit");
		wmove(win,3,4);
		wrefresh(win);
		while ((ch=wgetch(win))!='\n') {}
		lev=0;
		want_play=false;
	}
	else
	{
		mvwprintw(win,1,4,"CLEAR!");
		mvwprintw(win,2,2,"SCORE = %d",count);
		mvwprintw(win,3,1,">next   quit");
		keypad(win,TRUE);
		wmove(win,3,1);
		wrefresh(win);

		wrefresh(win);
		while ((ch=wgetch(win))!='\n')
		{
			switch(ch)
			{
    			case KEY_LEFT:
					mvwprintw(win,3,1,">next   quit");
					wmove(win,3,1);
      				break;
    			case KEY_RIGHT:
					mvwprintw(win,3,1,"next   >quit");
					wmove(win,3,8);
      				break;
				default:
					break;
			}
		}
	}

	int x, y;
	getyx(win,y,x);

	if (x==1)
	{
		clearStage=false;
		want_play=true;
	}
	else want_play=false;

	count=0;
	count_box=0;

	delwin(win);
	clear();
}

void pushBox::levList(int *h, int *w, int *array, int y, int x, int n)
{
	if (n==0)
	{
		*h=9;
		*w=7;
		int map0[9][7]={
		{1, 1, 1, 1, 4, 4, 4},
		{1, 3, 0, 1, 1, 4, 4},
		{1, 3, 5, 0, 1, 4, 4},
		{1, 3, 0, 2, 1, 4, 4},
		{1, 1, 2, 0, 1, 1, 1},
		{4, 1, 0, 2, 0, 0, 1},
		{4, 1, 0, 0, 0, 0, 1},
		{4, 1, 0, 0, 1, 1, 1},
		{4, 1, 1, 1, 1, 4, 4}};

		*array=map0[y][x];
	}
	else if(n==1)
	{
		*h=7;
		*w=6;
		int map1[7][6]={
			{1,1,1,1,1,4},
			{1,0,0,0,1,4},
			{1,3,3,3,1,4},
			{1,2,2,2,1,1},
			{1,0,0,0,0,1},
			{1,0,5,0,0,1},
			{1,1,1,1,1,1}};
		*array=map1[y][x];
	}
	else if(n==2)
	{
		*h=6;
		*w=8;
		int map2[6][8]={
			{1,1,1,1,1,1,1,1},
			{1,3,0,0,0,0,0,1},
			{1,0,3,2,2,2,5,1},
			{1,3,0,0,0,0,0,1},
			{1,1,1,1,1,0,0,1},
			{4,4,4,4,1,1,1,1}};
		*array=map2[y][x];
	}
	else if(n==3)
	{
		*h=8;
		*w=7;
		int map3[8][7]={
			{1,1,1,1,1,1,1},
			{1,0,0,0,0,0,1},
			{1,0,3,2,3,0,1},
			{1,0,2,3,2,0,1},
			{1,0,3,2,3,0,1},
			{1,0,2,3,2,0,1},
			{1,0,0,5,0,0,1},
			{1,1,1,1,1,1,1}};
		*array=map3[y][x];
	}
	else if(n==4)
	{
		*h=8;
		*w=10;
		int map4[8][10]={
			{4,1,1,1,1,4,4,4,4,4},
			{4,1,0,0,1,1,1,1,4,4},
			{4,1,0,0,0,0,0,1,1,4},
			{1,1,0,1,1,0,0,0,1,4},
			{1,3,0,3,1,0,5,2,1,1},
			{1,0,0,0,1,0,2,2,0,1},
			{1,0,0,3,1,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1}};
		*array=map4[y][x];
	}
}

void pushBox::palette()
{
	init_color(COLOR_BLACK,0,0,0);
	init_pair(1,COLOR_WHITE, COLOR_BLACK);
	init_pair(2,COLOR_RED,COLOR_BLACK);
	init_pair(3,COLOR_GREEN, COLOR_BLACK);
	init_pair(4,COLOR_BLACK,COLOR_WHITE);
}

void pushBox::Level(int n){
	bkgd(COLOR_PAIR(1));
	attron(COLOR_PAIR(1));
	attroff(COLOR_PAIR(1));
	mvprintw(1,5,"Level %d  step = 0  push = 0",(lev+1));
	mvprintw(2,3,"Move=keypad, Restart-R, Exit-Q.");
    mvprintw(4,1,"   *               *      *");
	mvprintw(5,1,"      *              * ");
    mvprintw(6,1," *                        *");
	mvprintw(7,1,"                  *          ");
	mvprintw(8,1,"  *                  *      *");
	mvprintw(10,1,"      *                  *     ");
	mvprintw(12,1,"    *              *        *");

	int x=0,y=0, z=0,h=1,w=1,map;
	wbox=0;
	goal=0;

   	for(y=0;y<h;y++)
   	{
      	for(x=0;x<w;x++)
      	{
         	levList(&h,&w,&map,y,x,n);
         	switch(map)
         	{
            	case 0:
				 				mvaddch(y+4,x+10,' '|COLOR_PAIR(2));
								break;
							case 4:
								mvaddch(y+4,x+10,' '|COLOR_PAIR(1));
								break;
            	case 1:
								mvaddch(y+4,x+10,'#'|COLOR_PAIR(1));
								break;
            	case 3:mvaddch(y+4,x+10,'x'|COLOR_PAIR(2));
								g[goal].xP=x+10;
								g[goal].yP=y+4;
								goal++;
								break;
            	case 2:
               		mvaddch(y+4,x+10,' '|COLOR_PAIR(2));
               		wbox +=1;
               		obj[wbox].ozn=mvinch(y+4,x+10);
               		obj[wbox].yP=y+4;
               		obj[wbox].xP=x+10;
               		obj[wbox].zn='@';
									mvaddch(obj[wbox].yP,obj[wbox].xP,obj[wbox].zn|COLOR_PAIR(3));
               		break;
            	case 5:
               		mvaddch(y+4,x+10,' '|COLOR_PAIR(2));
               		obj[0].ozn=mvinch(y+4,x+10);
               		obj[0].yP=y+4;
									obj[0].xP = x+10;
               		obj[0].zn='8';
               		mvaddch(obj[0].yP,obj[0].xP,obj[0].zn|COLOR_PAIR(1));
               		break;
         	}
      	}
   	}
   	move(obj[0].yP, obj[0].xP);
}

void pushBox::Play(int input)
{
	bool restart = FALSE;
	clearStage=false;

	chtype up, lf, dw, rg, oup, olf, odw, org;

	up = (mvinch(obj[0].yP-1, obj[0].xP) & A_CHARTEXT);
	lf = (mvinch(obj[0].yP, obj[0].xP-1) & A_CHARTEXT);
	dw = (mvinch(obj[0].yP+1, obj[0].xP) & A_CHARTEXT);
	rg = (mvinch(obj[0].yP, obj[0].xP+1) & A_CHARTEXT);
	oup = (mvinch(obj[0].yP-2, obj[0].xP) & A_CHARTEXT);
	olf = (mvinch(obj[0].yP, obj[0].xP-2) & A_CHARTEXT);
	odw = (mvinch(obj[0].yP+2, obj[0].xP) & A_CHARTEXT);
	org = (mvinch(obj[0].yP, obj[0].xP+2) & A_CHARTEXT);

	for(int i=0;i<=wbox;i++)
	{
		mvaddch(obj[i].yP, obj[i].xP, obj[i].ozn);
	}

	switch (input)
	{
		case KEY_UP:
			if(up != 35)
			{
				if(up==64 && (oup==' ' || oup==120))
				{
					obj[0].yP -= 1;
					for(int i=1;i<=wbox;i++)
					{
						if((obj[0].yP==obj[i].yP) && (obj[0].xP==obj[i].xP))
						{
							obj[i].yP -= 1;
							count++;
							count_box++;
						}
					}
				}
				else if(up!=64)
				{
					obj[0].yP -= 1;
					count++;

				}
			}
			isclear();
			printCount(count, count_box);
			break;

		case KEY_DOWN:
			if(dw!=35)
			{
				if(dw==64 && (odw==' ' || odw==120))
				{
					obj[0].yP += 1;
					for(int i=1;i<=wbox;i++)
					{
						if((obj[0].yP==obj[i].yP) && (obj[0].xP==obj[i].xP))
						{
							obj[i].yP += 1;
							count++;
							count_box++;
						}
					}
				}
				else if(dw!=64)
				{
					obj[0].yP += 1;
					count++;
				}
			}
			isclear();
			printCount(count, count_box);
			break;

		case KEY_LEFT:

			if(lf!=35)
			{
				if(lf==64 && (olf==' ' || olf==120))
				{
					obj[0].xP -= 1;
					for(int i=1;i<=wbox;i++)
					{
						if((obj[0].yP==obj[i].yP) && (obj[0].xP==obj[i].xP))
						{
							obj[i].xP -= 1;
							count++;
							count_box++;
						}
					}
				}
				else if(lf!=64)
				{
					obj[0].xP -= 1;
					count++;
				}
			}
			isclear();
			printCount(count, count_box);
			break;

		case KEY_RIGHT:
			if (rg!=35)
			{
				if (rg==64 && (org == ' ' || org == 120))
				{
					obj[0].xP +=1;
					for (int i=1; i<=wbox; i++)
					{
						if ((obj[0].yP == obj[i].yP) && (obj[0].xP==obj[i].xP))
						{
							obj[i].xP+=1;
							count++;
							count_box++;

						}
					}
				}
				else if (rg!=64)
				{
					obj[0].xP+=1;
					count++;
				}

			}
			isclear();
			printCount(count, count_box);
			break;

		case 'r':
		case 'R':
			restart=TRUE;
			Level(lev);
			count=0;
			count_box=0;
			break;

		case 'Q':
		case 'q':
			want_play=false;
			count=0;
			count_box=0;
			break;

		default:
			break;
	}

	if (!restart)
	{
		for (int i=0; i<=wbox; i++)
		{
			obj[i].ozn=mvinch(obj[i].yP, obj[i].xP);
			mvaddch(obj[i].yP, obj[i].xP, obj[i].zn | ((i==0) ? COLOR_PAIR(1) : COLOR_PAIR(3)));
		}
		move(obj[0].yP, obj[0].xP);
	}
	else restart=FALSE;

}
void pushBox::HOME(int ch){

    border('|', '|', '-', '-', '+', '+', '+', '+');
    bkgd(COLOR_PAIR(4));
    attron(COLOR_PAIR(4));
    attroff(COLOR_PAIR(4));
    mvprintw(7,6," WELCOME TO THE SNOW WORLD!");

	mvprintw(9,6,"      *      *    *");
	mvprintw(10,6,"         *  /.\\       *");
	mvprintw(11,6,"   *       /..'\\    *");
	mvprintw(12,6,"       *   /'.'\\  *    *");
	mvprintw(13,6,"          /.''.'\\    *");
	mvprintw(14,6,"   *      /.'.'.\\  *    ");
	mvprintw(15,6,"      *  /'.''.'.\\      *  ");
	mvprintw(16,6,"    *    ^^^[_]^^^    *");

    mvprintw(18,17,">PLAY");
    mvprintw(20,16," QUIT  ");
    move( 18, 16);

    while((ch = getch()) != '\n')
	{
    	switch(ch)
		{
        	case KEY_UP:
          		mvprintw(18,17,">PLAY");
          		mvprintw(20,16," QUIT  ");
          		move( 18, 17);
          		break;

        	case KEY_DOWN:
          		mvprintw(18,16," PLAY  ");
          		mvprintw(20,17,">QUIT");
          		move( 20, 17);
          		break;

        	default:
          		break;
        }
    }
	int x, y;
	getyx(stdscr,y,x);

	if (y==18)
	{
		clearStage=false;
		want_play=true;
		delwin(home);
		clear();
	}
	else
	{
		want_play=false;
		delwin(home);
		endwin();
		exit(1);
	}
}

void pushBox::printCount(int count, int count_box)
{
	mvprintw(1,21, "%d", count);
	mvprintw(1,31, "%d", count_box);

}
