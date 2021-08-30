#include<stdio.h>
#include<windows.h>
#include<conio.h>

void draw_ship(int x,int y)   // Assignment 2
{
	COORD c = { x, y };
	SetConsoleCursorPosition(
	GetStdHandle(STD_OUTPUT_HANDLE) , c);
	
	printf(" <-0-> ");
}

void erase_ship(int x,int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(
	GetStdHandle(STD_OUTPUT_HANDLE) , c);
	
	printf("       ");
}

int main()
{
	char ch=' ';
	int x,y,tempx,tempy;
	y=20;
	for(int i=0;i<73;i++)   // Assignment 1
	{
		x=i;
		draw_ship(x,20);
		Sleep(500);
	}
	
	do
	{
		if (_kbhit())
		{
			ch=_getch();
			if(ch=='a') 
				if(x > 0)
					draw_ship(--x,y);
			if(ch=='d') 
				if(x < 72)   // Assignment 3
					draw_ship(++x,y);
			if(ch=='w')   // Assignment 4
				if(y > 0)
				{
					erase_ship(x,y);
					y--;
					draw_ship(x,y);
				}
			if(ch=='s')   // Assignment 4
			
				if(y < 24){
					erase_ship(x,y);
					y++;
					draw_ship(x,y);
				}
			fflush(stdin);
		}
		
		Sleep(100);
	}while (ch!='x');
	
	return 0;
}
