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
#define KEY_S 115
#define KEY_E 101

struct Pen
{
	char Char;
	int Color;
};

struct Buff
{
	COORD Start, End;
	unsigned char Char[256][256];
	unsigned char Color[256][256];
};

void InitBuff(Buff &Scr)
{
	Scr.Start = Scr.End = {0, 0};
	memset(&Scr.Char, 32, sizeof(Scr.Char));
	memset(&Scr.Color, 15, sizeof(Scr.Color));
}

void ExportBuff(Buff &Scr)
{
	std::ifstream Data;
	Data.open("Path.txt");
	std::string Path;
	getline(Data, Path, '\n');
	Data.close();
	std::ofstream Ex(Path);
	Ex << Scr.End.Y - Scr.Start.Y + 1 << " " << Scr.End.X - Scr.Start.X + 1 << std::endl;
	for (int i = Scr.Start.Y; i <= Scr.End.Y; i++)
	{
		for (int j = Scr.Start.X; j <= Scr.End.X; j++) Ex << (int) Scr.Char[j][i] << " ";
		Ex << std::endl;
	}
	for (int i = Scr.Start.Y; i <= Scr.End.Y; i++)
	{
		for (int j = Scr.Start.X; j <= Scr.End.X; j++) Ex << (int) Scr.Color[j][i] << " ";
		Ex << std::endl;
	}
	Ex.close();
}

void gotoXY(int x, int y)
{
	static HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = {x, y};
	SetConsoleCursorPosition(out, coord);
}

void SetColor(int value)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
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

void Color_Generate()
{
	for (int i = 0; i < 16; i++)
	{
		gotoXY(i, 16);
		SetColor(i);
		std::cout << (char) 219;
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
	Status.Color = 15;
}

void PenExe(COORD CCP, Pen &Status, Buff &Scr)
{
	if (CCP.X < 16 && CCP.Y < 16)
		Status.Char = CCP.X * 16 + CCP.Y;
	else
		if (CCP.X < 16 && CCP.Y == 16)
		{
			SetColor(CCP.X);
			Status.Color = CCP.X;
		}
		else
		{
			
			std::cout << Status.Char;
			Scr.Char[CCP.X][CCP.Y] = Status.Char;
			Scr.Color[CCP.X][CCP.Y] = Status.Color;
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
	Color_Generate();
	Pen Status;
	InitPen(Status);
	Buff Scr;
	InitBuff(Scr);
	char Char;
	while (true)
	{
		//Sleep(100);
		if (!_kbhit()) continue;
		Char = _getch();
		if (Char == KEY_ESC) return;
		switch (Char)
		{
			case KEY_ENTER:
				PenExe(GetConsoleCursorPosition(), Status, Scr);
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
			case KEY_S:
				Scr.Start = GetConsoleCursorPosition();
				break;
			case KEY_E:
				Scr.End = GetConsoleCursorPosition();
				ExportBuff(Scr);
				break;
		}
	}
}