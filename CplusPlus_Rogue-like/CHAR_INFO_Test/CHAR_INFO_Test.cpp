#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

int main()
{
	const int width = 20;
	const int height = 7;

	CHAR_INFO ci[width * height];

	for (int i = 0; i < width * height; i++)
	{
		ci[i].Char.UnicodeChar = '1';
		ci[i].Attributes = 7;
	}

	COORD pos = { 0, 0 };
	COORD size = { width, height };
	SMALL_RECT rect = { 0, 0, width, height };
	WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), ci, size, pos, &rect);

	_getch();

	return 0;
}