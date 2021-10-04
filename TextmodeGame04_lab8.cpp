#include <stdio.h>
#include <windows.h>
#include<math.h>
#include <time.h>
#define screen_x 80
#define screen_y 25
#define scount 80

HANDLE rHnd;
HANDLE wHnd;
DWORD fdwMode;
COORD bufferSize = { screen_x,screen_y };
SMALL_RECT windowSize = { 0,0,screen_x-1,screen_y-1 };
CHAR_INFO consoleBuffer[screen_x * screen_y];
COORD characterPos = { 0,0 };
COORD star[scount];

int posx,posy,life=10,colorfg,colorbg;

int setConsole(int x, int y)
{
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	return 0;
}

int setMode()
{
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT |
	ENABLE_MOUSE_INPUT;
	SetConsoleMode(rHnd, fdwMode);
	return 0;
}

void clear_buffer()
{
	for (int y = 0; y < screen_y; ++y) 
	{
		for (int x = 0; x < screen_x; ++x) 
		{
			consoleBuffer[x + screen_x * y].Char.AsciiChar = ' ';
			consoleBuffer[x + screen_x * y].Attributes = 0;
		}
	}
}

void fill_buffer_to_console()
{
	WriteConsoleOutputA(wHnd, consoleBuffer, bufferSize, characterPos,&windowSize);
}

void init_star()
{
	for(int i=0;i<80;i++)
	{
		star[i].X = rand() % screen_x;
		star[i].Y = rand() % screen_y;
	}
}

void star_fall()
{
	for (int i = 0; i < scount; i++) 
	{
		if (star[i].Y >= screen_y-1) 
		{
			star[i] = { (rand() % screen_x),1 };
		}
		else 
		{
			if(abs(star[i].X - posx) <= 2 && star[i].Y == posy)
			{
				Beep(700,100);
				life--;
				star[i] = { (rand() % screen_x),1 };
			}
			else
				star[i] = { star[i].X,star[i].Y+1 };
		}
	}
}

void fill_star_to_buffer()
{
	for(int i=0;i<80;i++)
	{
		consoleBuffer[star[i].X + screen_x * star[i].Y].Char.AsciiChar = '*';
		consoleBuffer[star[i].X + screen_x * star[i].Y].Attributes = 7;
	}
}

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
	setcolor(colorbg,colorfg);
	printf("<-0->");
}

void delete_ship(int x,int y)
{
	gotoxy(x,y); 
	printf("     ");
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
	int oldx,oldy;
	bool play = true;
	
	srand(time(NULL));
	colorfg = rand() % 16;
    colorbg = rand() % 16;
	init_star();
	setcursor(0);
	DWORD numEvents = 0;
	DWORD numEventsRead = 0;
	setConsole(screen_x, screen_y);
	setMode();
	
	while(play)
	{
		if(life < 0)
		{
			break;
		}
		star_fall();
		clear_buffer();
		fill_star_to_buffer();
		fill_buffer_to_console();
		draw_ship(posx-2,posy);
		GetNumberOfConsoleInputEvents(rHnd, &numEvents);
		if (numEvents != 0) 
		{
			INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
			ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);
			
			for (DWORD i = 0; i < numEventsRead; ++i) 
			{
				if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown == true) {
                    if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) 
					{
                        play = false;
                    }
                   	else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'c' || eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'C')
                    {
                    	colorfg = rand() % 16;
						colorbg = rand() % 16;
						while (colorbg == colorfg)
						{
							colorbg = rand() % 16;
						}
						draw_ship(posx-2,posy);
					}
                }
				else if (eventBuffer[i].EventType == MOUSE_EVENT) 
				{
					
					posx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
					posy = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
					
					if (eventBuffer[i].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
                    {
                    	colorfg = rand() % 16;
						colorbg = rand() % 16;
						while (colorbg == colorfg)
						{
							colorbg = rand() % 16;
						}
						draw_ship(posx-2,posy);
					}
					else if (eventBuffer[i].Event.MouseEvent.dwEventFlags & MOUSE_MOVED) 
					{
						delete_ship(oldx,oldy);
						draw_ship(posx-2,posy);	
					}
					oldx=posx-2; oldy=posy;
				}
			}
			delete[] eventBuffer;
		}
		Sleep(100);
	}
	return 0;
}
