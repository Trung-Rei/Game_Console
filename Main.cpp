#include <windows.h>
#include <conio.h>
#include <chrono>
#include "Physic.h"

#define KEY_ESC 27
#define KEY_JUMP 32

void gotoXY(int x, int y)
{
	static HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { x, y };
	SetConsoleCursorPosition(out, coord);
}

int main()
{
	Physic::PhysicObject Ball;
	Physic::Init(Ball, 100, -300);
	Physic::SetOriginPosi(Ball, 50, 50);
	char Char;
	double Delta_t;
	std::chrono::time_point<std::chrono::system_clock> PreTime, NextTime;
	PreTime = std::chrono::system_clock::now();
	while (true)
	{
		if (_kbhit())
		{
			Char = _getch();
			switch (Char)
			{
			case KEY_ESC: return 0;
			case KEY_JUMP: Physic::ResetTime(Ball);
				break;
			}
		}
		NextTime = std::chrono::system_clock::now();
		Delta_t = std::chrono::duration_cast<std::chrono::nanoseconds>(NextTime - PreTime).count() / 1000000000.0;
		PreTime = NextTime;
		Physic::MoveObject_Height(Ball, Delta_t);
		if (Ball.Moved) gotoXY(Ball.CurrentX + Ball.SideInt, Ball.CurrentY - Ball.HeightInt);
	}
}