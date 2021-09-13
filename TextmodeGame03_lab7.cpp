#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>

int c=0;
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

void draw_ship(int x,int y)
{
	gotoxy(x,y); printf(" <-0-> ");
}

void draw_bullet(int x,int y)
{
	gotoxy(x,y); printf("^");
}

void clear_bullet(int x,int y)
{
	gotoxy(x,y); printf(" ");
}

void star(int x,int y)
{
	gotoxy(x,y); printf("*");
}

void score(int x,int y)
{
	gotoxy(x,y); 
	printf("                    "); 
	gotoxy(x,y);
	printf("Points = %d",c);
}

char cursor(int x, int y){
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = {x,y}; DWORD num_read;
	
	if(!ReadConsoleOutputCharacter(hStd,(LPTSTR)buf,1,c,(LPDWORD)&num_read) )
		return '\0';
	else
		return buf[0];
}

int main()
{
	char ch='.';
	int x=38,y=20;
	int bx,by,i;
	int bullet = 0;
	int randY,randX;
	score(60,0);
	draw_ship(x,y);
	setcursor(0);
	srand(time(NULL));
	
	for(int i=0;i<20;i++) 
	{
		randX = rand()%(70-10 + 1)+10;
		randY = rand()%(5-2 + 1)+2;
		if(cursor(randX,randY) != '*')
			star(randX,randY);
		else
			i--;
	}
	
	do 
	{
		if (_kbhit())
		{
			ch=_getch();
			if(ch=='a') 
			{
				draw_ship(--x,y);
			}
			if(ch=='s') 
			{
				draw_ship(++x,y);
			}
			if(bullet!=1 && ch==' ') 
			{
				bullet=1; bx=x+3; by=y-1;
			}
			fflush(stdin);
		}
		if (bullet==1) 
		{
			clear_bullet(bx,by);
			if (by==2) 
			{
				bullet=0;
			}
			else 
			{
				if(cursor(bx,by-1) != '*')
				{
					draw_bullet(bx,--by); 
					Beep(300,100);
				}
				else
				{
					c++;
					score(60,0);
					clear_bullet(bx,--by);
					bullet=0;
					Beep(700,100);
					while(1)
					{
						randX = rand()%(70-10 + 1)+10;
						randY = rand()%(5-2 + 1)+2;
						if(cursor(randX,randY) != '*')
						{
							star(randX,randY);
							break;
						}
					}
				}
			}
		}
		Sleep(100);
	} while (ch!='x');
	
	return 0;
}
