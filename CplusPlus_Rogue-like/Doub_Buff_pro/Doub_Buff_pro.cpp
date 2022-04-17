#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>
using namespace std;

#define Y 30
#define X 141

char map[Y][X] = {
	"############################################################################################################################################",
	"#                                                                                                                                          #",
	"#                                                                                                                                          #",
	"#                                                                                                                                          #",
	"#                        Collection                              Game Start                              Making....                        #",
	"#                                                                                                                                          #",
	"#                   ####################                    ####################                    ####################                   #",
	"#                   #                  #                    #                  #                    #                  #                   #",
	"#                   #        @@        #                    #        @@        #                    #        @@        #                   #",
	"#                   #        @@        #                    #        @@        #                    ####################                   #",
	"#                                                                                                                                          #",
	"#                                                                                                                                          #",
	"#                                                                                                                                          #",
	"#                                                                                                                                          #",
	"#                                                                                                                                          #",
	"#                                                                                                                                          #",
	"#                                                                                                                                          #",
	"#                                                                                                                                          #",
	"#                                                                                                                                          #",
	"#                                                                                                                                          #",
	"#                                                                                                                                          #",
	"#                                                                                                                                          #",
	"#                                                                                                                                          #",
	"#                                                                                                                                          #",
	"#                                                                                                                                          #",
	"#                                                                                                                                          #",
	"#                                                                                                                                          #",
	"#                                                                                                                                          #",
	"#                                                                                                                                          #",
	"############################################################################################################################################"
};

const int width = 80;
const int height = 20;

int change;

CHAR_INFO ci[width * height];

HANDLE screen[2];

void setMap(char arr[][X], int x, int y)
{
	for (int i = 0; i < 20; i++)
	{
		for (int n = 0; n < 80; n++)
		{
			ci[i + n].Char.UnicodeChar = arr[i + y][n + x];
		}
	}

	DWORD dw;

	COORD size = { width, height };
	COORD pos = { 0, 0 };

	SMALL_RECT rect = { 0, 0, width, height };

	change = !change;
	WriteConsoleOutput(screen[change], ci, size, pos, &rect);
	SetConsoleActiveScreenBuffer(screen[change]);
}

int main()
{
	CONSOLE_CURSOR_INFO cci;

	screen[0] = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, 0, 0, CONSOLE_TEXTMODE_BUFFER, 0);
	screen[1] = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, 0, 0, CONSOLE_TEXTMODE_BUFFER, 0);

	cci.bVisible = FALSE;

	SetConsoleCursorInfo(screen[0], &cci);
	SetConsoleCursorInfo(screen[1], &cci);

	SetConsoleActiveScreenBuffer(screen[change]);

	char arr[2][10] = { "Hello?", "?olleH" };

	system("mode con: cols=80 lines=20");

	char key = 0;
	int y = 0;
	int x = 30;

	while (true)
	{

		if (_kbhit())
		{
			key = _getch();
			key = tolower(key);
			if (key == 'w') {
				if (y > 0)
				{
					y--;
					setMap(map, x, y);
				}
			}
			else if (key == 's') {
				if (y < 10)
				{
					y++;
					setMap(map, x, y);
				}
			}
			else if (key == 'a') {
				if (x >= 0)
				{
					x--;
					setMap(map, x, y);
				}
			}
			else if (key == 'd') {
				if (x < 60)
				{
					x++;
					setMap(map, x, y);
				}
			}
		}
	}

	CloseHandle(screen[0]);
	CloseHandle(screen[1]);

	return 0;
}