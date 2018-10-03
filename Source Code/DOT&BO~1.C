/*========================================================
Note: Write your BGI folder path of respective C compiler
	  into parameter 
		E.g.
		initgraph(&gd,&gm,"C:\\TURBOC3\\bgi");
		initgraph(&gd,&gm,"C:\\TC\\BGI");

Developed by Hardik R Thakkar
==========================================================*/

#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
#include<stdlib.h>
#include<string.h>
# define DISTANCE 50
# define R 5
# define FULL 15

int x,y,midx,midy,k,j,box=0,line_counter=0;
int horizontal[4][5],vertical[3][6];
int XPOINTS[8][8],YPOINTS[8][8];     // Used to Store X and Y points of Grid Dots(Center of Circle).

struct player{
	char name[15];
	int score;
}p[2];

union REGS i,o;

int round(float x);
void showmouseptr();
void getmousepos(int *button, int *x, int *y);
void restrictmouseptr(int x1, int y1, int x2, int y2);
void WelcomePage();
char MainMenu();
void playerInfo();
void GAME();
void left_check();
void right_check();
void top_check();
void bottom_check();
void player_moves();
void alternate();
void final_score();
void ExitScreen();


void main()
{
	int gd=DETECT,gm,s,button;
	char c,score[2];
	clrscr();
	initgraph(&gd,&gm,"C:\\TURBOC3\\bgi");
	cleardevice();

	x=getmaxx();
	y=getmaxy();
	midx =x/2;
	midy= y/2;
	clrscr();
	WelcomePage();
	start: c=MainMenu();
	if(c=='1')
	{
		settextstyle(3,HORIZ_DIR,3);
		outtextxy(midx,midy+50,"Starting New Game.....");
		delay(1000);
		playerInfo();
	}
	else if(c=='2')
	{
		settextstyle(3,HORIZ_DIR,3);
		outtextxy(midx,midy+50,"Exiting.....");
		delay(1000);
		ExitScreen();
	}

	else
	{
		settextstyle(3,HORIZ_DIR,3);
		outtextxy(midx,midy+50,"Invalid Input.");
		delay(1000);
		goto start;
	}
	cleardevice();
	ExitScreen();
	getch();
	closegraph();
}

/*==================All Functions ===================*/

int round(float x)
{
	int temp = (int)x;

	if((x-temp)>=0.5)
		return (temp+1);
	else
		return temp;
}

/*===================MOUSE FUNCTIONS=======================*/


void showmouseptr()
{
	i.x.ax = 1;
	int86(0X33,&i,&o);
}

void getmousepos(int *button, int *x, int *y)
{
	i.x.ax = 3;
	int86(0X33,&i,&o);

	*button = o.x.bx;
	*x = o.x.cx;
	*y = o.x.dx;
}
void restrictmouseptr(int x1, int y1, int x2, int y2)
{
	i.x.ax = 7;
	i.x.cx = x1;
	i.x.dx = x2;
	int86(0X33,&i,&o);

	i.x.ax = 8;
	i.x.cx = y1;
	i.x.dx = y2;
	int86(0X33,&i,&o);
}

/*===================================================================*/

void WelcomePage()
{
	cleardevice();
	setbkcolor(GREEN);
	setcolor(WHITE);
	settextstyle(TRIPLEX_FONT,0,5);
	outtextxy(midx-90,50,"WELCOME");
	outtextxy(midx-25,100,"TO");


	setlinestyle(DASHED_LINE,1,3);
	rectangle(25,25,x-25,y-25);

	rectangle(30,30,x-30,y-30);

	settextstyle(TRIPLEX_FONT,0,6);
	setfillstyle(HATCH_FILL,RED);
	bar(midx-175,175,x-140,midy+150);

	textcolor(2);
	settextstyle(DEFAULT_FONT,0,5);
	outtextxy(midx-50,200,"DOT");
	outtextxy(midx-50,250,"&");
	outtextxy(midx-50,300,"BOX");
	delay(2000);

	setcolor(RED+BLINK);
	settextstyle(0,0,1);
	outtextxy(midx-175,midy+160,"Press Any Key To Continue...");
	getch();

}


char MainMenu()
{
	clrscr();
	cleardevice();
	setbkcolor(RED);
	setcolor(WHITE);
	setlinestyle(DASHED_LINE,1,3);
	rectangle(50,50,x-50,y-125);
	rectangle(60,60,x-60,y-135);


	settextstyle(3,HORIZ_DIR,4);
	settextjustify(CENTER_TEXT,BOTTOM_TEXT);
	outtextxy(midx,midy-125,"MAIN MENU");

	settextstyle(0,HORIZ_DIR,2);
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	outtextxy(midx,midy-50,"1. START NEW GAME");
	outtextxy(midx,midy,"2. END GAME");

	return getch();
}


void playerInfo()
{
	clrscr();
	cleardevice();
	setbkcolor(0);
	setlinestyle(SOLID_LINE,1,3);
	setfillstyle(SOLID_FILL,RED);
	bar(midx-200,midy-75,midx+200,midy+75);

	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar(midx-200,midy-50,midx+200,midy-75);
	settextstyle(0,0,2);
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	setcolor(0);
	outtextxy(midx,midy-60,"Enter Player's Name");

	settextstyle(0,0,2);
	setcolor(15);
	outtextxy(midx-90,midy-10,"Player 1 :");
	outtextxy(midx-90,midy+30,"Player 2 :");

	scanf("%s",p[0].name);
	scanf("%s",p[1].name);

	setcolor(3);
	outtextxy(midx+50,midy-10,p[0].name);
	outtextxy(midx+50,midy+30,p[1].name);
	delay(1000);
	cleardevice();
	settextstyle(0,0,3);
	setcolor(15);
	outtextxy(midx,midy,"Let's Start The Game ");
	delay(1500);
	GAME();
}



void GAME()
{
	int left,top,right,bottom,i,j;
	cleardevice();
	setfillstyle(SOLID_FILL,1);
	bar(0,20,x,40);
	settextstyle(0,0,2);
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	outtextxy(midx,30,"DOT & BOX GAME");

	setfillstyle(SOLID_FILL,8);
	bar(0,y,x,y-20);
	settextstyle(0,0,2);
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	outtextxy(midx,y-10,"Left Click for Vertical & Right Click for Horizontal");

	rectangle(20,50,x-200,y-30);
	rectangle(x-180,50,x-20,midy);
	top=100;

	setfillstyle(1,10);
	for(i=0;i<4;i++)
	{
		left= 50;

		for(j=0;j<6;j++)
		{
			XPOINTS[i][j]=left;
			YPOINTS[i][j]=top;
			circle(left,top,R);

			left=left+DISTANCE;
		}

		top=top+100;
	}

	settextstyle(0,0,2);
	setcolor(10);
	outtextxy(x-100,80,p[0].name);
	setcolor(11);
	outtextxy(x-100,160,p[1].name);
	alternate();
}

void left_check(int y1, int x1, int PLAYER)
{
	char id[1];
	itoa(PLAYER+1,id,10);
	if(vertical[y1][x1-1] && horizontal[y1][x1-1] && horizontal[y+1][x1-1])
	{
		outtextxy(XPOINTS[y][x]-25,YPOINTS[y][x]+50,id);
		p[PLAYER].score++;
		box++;
	}
}


void right_check(int y1, int x1, int PLAYER)
{
	char id[1];
	itoa(PLAYER+1,id,10);
	if(vertical[y1][x1+1] && horizontal[y1][x1] && horizontal[y1+1][x1])
	{
		outtextxy(XPOINTS[y][x]+25,YPOINTS[y][x]+50,id);
		p[PLAYER].score++;
		box++;
	}
}

void top_check(int y1, int x1,int PLAYER)
{
	char id[1];
	itoa(PLAYER+1,id,10);
	if(horizontal[y1-1][x1] && vertical[y1-1][x1] && vertical[y1-1][x1+1])
	{
		outtextxy(XPOINTS[y][x]+25,YPOINTS[y][x]-50,id);
		p[PLAYER].score++;
		box++;
	}
}

void bottom_check(int y1, int x1,int PLAYER)
{
	char id[1];
	itoa(PLAYER+1,id,10);

	if(horizontal[y1+1][x1] && vertical[y1][x1] && vertical[y1][x1+1])
	{
		outtextxy(XPOINTS[y][x]+25,YPOINTS[y][x]+50,id);
		p[PLAYER].score++;
		box++;
	}
}

void player_moves(int PLAYER)
{

	int button=0,x1,x2,y1,y2,temp,done=0;


	showmouseptr();
	restrictmouseptr(50,100,300,400);

	while(done!=1 && box!=FULL)
	{
		temp=box;
		getmousepos(&button,&x,&y);
		setlinestyle(0,2,3);
		setcolor(PLAYER+10);
		if(button == 1 )
		{
			x=(float)x/50;
			y=(int)y/100;
			x=round(x);
			y--;x--;

			x1=x2=XPOINTS[y][x];
			y1=YPOINTS[y][x];
			y2=YPOINTS[y+1][x];

			if(vertical[y][x]!=1)
			{
				vertical[y][x]=1;
				line(x1,y1,x2,y2);
				done=1;

				if(x==0 &&vertical[y][x]==1)
				{
					right_check(y,x,PLAYER);

				}
				else if(x==5 && vertical[y][x]==1)
				{
					left_check(y,x,PLAYER);
				}
				else
				{
					left_check(y,x,PLAYER);
					right_check(y,x,PLAYER);
				}
			}
		}
		else if(button == 2)
		{
			x=(int)x/50;
			y=(float)y/100;
			y=round(y);
			y--;x--;
			y1=y2=YPOINTS[y][x];
			x1=XPOINTS[y][x];
			x2=XPOINTS[y][x+1];
			if(horizontal[y][x]!=1)
			{
				horizontal[y][x]=1;
				line(x1,y1,x2,y2);
				done=1;
				if(y==0 && horizontal[y][x]==1)
				{
					bottom_check(y,x,PLAYER);
				}
				else if(y==3 && horizontal[y][x]==1)
				{
					top_check(y,x,PLAYER);
				}
				else
				{
					top_check(y,x,PLAYER);
					bottom_check(y,x,PLAYER);

				}
			}

		}
		if(temp!=box)
			done=0;
	}
}


void alternate()
{
	int player1=0,player2=1;
	char score[5];
	while(1)
	{
		if(box==FULL || kbhit())
			break;
		player_moves(player1);
		player_moves(player2);
	}
	delay(1000);
	final_score();
}


void final_score()
{
	char score[5];
	cleardevice();
	setcolor(15);
	settextstyle(0,0,2);
	outtextxy(midx,midy-25,"Final Score is");
	itoa(p[0].score,score,10);
	setcolor(10);
	outtextxy(midx-30,midy,p[0].name);
	outtextxy(midx+50,midy,score);
	setcolor(11);
	outtextxy(midx-30,midy+25,p[1].name);
	itoa(p[1].score,score,10);
	outtextxy(midx+50,midy+25,score);
		outtextxy(midx+40,midy+65,"Congrats!!");
	if(p[1].score > p[0].score)
		outtextxy(midx+40,midy+65,"Player 2 has won the Game!");
	else if(p[1].score < p[0].score)
		outtextxy(midx+40,midy+65,"Player 1 has won the Game!");
	else
		outtextxy(midx,midy+65,"Tie !");
	delay(5000);
}

void ExitScreen()
{
	cleardevice();
	setbkcolor(BLUE);
	setcolor(WHITE);
	setlinestyle(DOTTED_LINE,2,4);
	rectangle(50,50,x-50,y-125);
	rectangle(60,60,x-60,y-135);
	settextstyle(1,HORIZ_DIR,5);
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	outtextxy(320,150,"Thanks! For Playing..");
	outtextxy(330,230,"Have a nice day :)");
	delay(2000);
}
/*========================================================================*/

/*
setlinestyle(fill_style,upattern,thickness)
setfillstyle(fill_style,Color)
settextstyle(font,direction,size)  //Horizontal or vertical direction
settextjustify(direction,position) // justifying text position
bar(tleft,top,right,bottom)  // filled Rectangle with same border color
*/
