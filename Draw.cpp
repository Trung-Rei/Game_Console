#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_ENTER 13

struct Pen
{
	char Char;
};

void gotoXY(int x, int y)
{
	static HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = {x, y};
	SetConsoleCursorPosition(out, coord);
}

void ASCII_Generate()
{
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
		{
			gotoXY(i, j);
			std::cout << (char) (i * 16 + j);
		}
}

COORD GetConsoleCursorPosition()
{
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
    {
        return cbsi.dwCursorPosition;
    }
    else
    {
        COORD invalid = {0, 0};
        return invalid;
    }
}

void InitPen(Pen &Status)
{
	Status.Char = 32;
}

void PenExe(COORD CCP, Pen &Status)
{
	if (CCP.X < 16 && CCP.Y < 16)
		Status.Char = CCP.X * 16 + CCP.Y;
	else
	{
		std::cout << Status.Char;
		gotoXY(CCP.X, CCP.Y);
	}
}

void MoveCursor(COORD CCP, int x, int y)
{
	if (CCP.X + x < 0 || CCP.Y + y < 0) return;
	gotoXY(CCP.X + x, CCP.Y + y);
}

void main()
{
	ASCII_Generate();
	Pen Status;
	InitPen(Status);
	char Char;
	while (true)
	{
		Char = _getch();
		if (Char == KEY_ESC) return;
		switch (Char)
		{
			case KEY_ENTER:
				PenExe(GetConsoleCursorPosition(), Status);
				break;
			case KEY_UP:
				MoveCursor(GetConsoleCursorPosition(), 0, -1);
				break;
			case KEY_DOWN:
				MoveCursor(GetConsoleCursorPosition(), 0, 1);
				break;
			case KEY_LEFT:
				MoveCursor(GetConsoleCursorPosition(), -1, 0);
				break;
			case KEY_RIGHT:
				MoveCursor(GetConsoleCursorPosition(), 1, 0);
				break;
		}
	}
}