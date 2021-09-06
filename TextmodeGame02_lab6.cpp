#include<stdio.h>
#include<windows.h>
#include<conio.h>

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE) , c);
}

void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console,&lpCursor);
}

void setcolor(int fg,int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg*16+fg);
}

void draw_ship(int x,int y)
{
	gotoxy(x,y); 
	setcolor(2,4);
	printf(" <-0-> ");
}

void delete_ship(int x,int y)
{
	gotoxy(x,y); 
	setcolor(0,0);
	printf("       ");
}

void draw_bullet(int x,int y)
{
	gotoxy(x,y); 
	setcolor(2,4);
	printf("I");
}

void delete_bullet(int x,int y)
{
	gotoxy(x,y); 
	setcolor(0,0);
	printf(" ");
}

int main()
{
	int direct=0;
	bool bullet[5];
	char ch='.';
	int x=38,y=20;
	int x1[5],y1[5];
	draw_ship(x,y);
	setcursor(0);
	
	do {
		if (kbhit())
		{
			ch=getch();
			if(ch=='a')
			{
				direct=-1;
			}
			if(ch=='d') 
			{
				direct=1;
			}
			if(ch=='s')
			{
				direct=0;
			}
			if(ch=='f')
			{
				if(bullet[0] == false)
				{	
					bullet[0]=true;
					x1[0]=(x+3); y1[0]=(y-1);
					draw_bullet(x1[0],y1[0]);
				}
				else if(bullet[1] == false)
				{	
					bullet[1]=true;
					x1[1]=(x+3); y1[1]=(y-1);
					draw_bullet(x1[1],y1[1]);
				}
				else if(bullet[2] == false)
				{	
					bullet[2]=true;
					x1[2]=(x+3); y1[2]=(y-1);
					draw_bullet(x1[2],y1[2]);
				}
				else if(bullet[3] == false)
				{	
					bullet[3]=true;
					x1[3]=(x+3); y1[3]=(y-1);
					draw_bullet(x1[3],y1[3]);
				}
				else if(bullet[4] == false)
				{	
					bullet[4]=true;
					x1[4]=(x+3); y1[4]=(y-1);
					draw_bullet(x1[4],y1[4]);
				}
			}
			fflush(stdin);
		}
		
		// Move Ship
		if(direct == -1 && x > 0)
		{
			delete_ship(x,y);
			x--;
			draw_ship(x,y);
		}
		else if(direct == 1 && x < 73)
		{
			delete_ship(x,y);
			x++;
			draw_ship(x,y);
		}
		
		// Bullet
		//////////////////////////////////////  1
		if(bullet[0] == true && y1[0] > 0)
		{
			delete_bullet(x1[0],y1[0]);
			y1[0]--;
			draw_bullet(x1[0],y1[0]);
		}
		else if(bullet[0] == true && y1[0] == 0)
		{
			delete_bullet(x1[0],y1[0]);
			bullet[0]=false;
		}
		//////////////////////////////////////  2
		if(bullet[1] == true && y1[1] > 0)
		{
			delete_bullet(x1[1],y1[1]);
			y1[1]--;
			draw_bullet(x1[1],y1[1]);
		}
		else if(bullet[1] == true && y1[1] == 0)
		{
			delete_bullet(x1[1],y1[1]);
			bullet[1]=false;
		}
		//////////////////////////////////////  3
		if(bullet[2] == true && y1[2] > 0)
		{
			delete_bullet(x1[2],y1[2]);
			y1[2]--;
			draw_bullet(x1[2],y1[2]);
		}
		else if(bullet[2] == true && y1[2] == 0)
		{
			delete_bullet(x1[2],y1[2]);
			bullet[2]=false;
		}
		//////////////////////////////////////  4
		if(bullet[3] == true && y1[3] > 0)
		{
			delete_bullet(x1[3],y1[3]);
			y1[3]--;
			draw_bullet(x1[3],y1[3]);
		}
		else if(bullet[3] == true && y1[3] == 0)
		{
			delete_bullet(x1[3],y1[3]);
			bullet[3]=false;
		}
		//////////////////////////////////////  5
		if(bullet[4] == true && y1[4] > 0)
		{
			delete_bullet(x1[4],y1[4]);
			y1[4]--;
			draw_bullet(x1[4],y1[4]);
		}
		else if(bullet[4] == true && y1[4] == 0)
		{
			delete_bullet(x1[4],y1[4]);
			bullet[4]=false;
		}
		
		Sleep(100);
	} while (ch!='x');
	
	return 0;
}
