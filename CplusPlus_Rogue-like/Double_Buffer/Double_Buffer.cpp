#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#pragma comment(lib, "winmm.lib")
using namespace std;

void update();
void deltaTime(float dTime);
void setActiveCursor(HANDLE& handle, char isShow);
void init();
void endGame();

bool playerUpCheck(int x, int y, char c);
bool playerDownCheck(int x, int y, char c);
bool playerRightCheck(int x, int y, char c);
bool playerLeftCheck(int x, int y, char c);

// 화면 크기
const int X = 141; // + NULL문자
const int Y = 30;

// 커다란 맵... 배열...
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

HANDLE screen;

int main()
{
	init();

	SetConsoleTitle(TEXT("debug"));

	while (true)
	{
		deltaTime(20);

		if (GetAsyncKeyState(VK_RSHIFT))
		{
			SetConsoleTitle(TEXT("Text"));
		}
	}
	endGame();
	return 0;
}

void init()
{
	system("mode con: cols=140 lines=30"); // 콘솔 크기 설정
	screen = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, 0, 0, CONSOLE_TEXTMODE_BUFFER, 0); // 스크린 버퍼 생성
	SetConsoleActiveScreenBuffer(screen); // 콘솔에다 만든 스크린 버퍼를 넣어줌
	setActiveCursor(screen, 0); // 커서 삭제
}

void endGame()
{
	CloseHandle(screen);
}

void deltaTime(float dTime)
{
	static DWORD currentTime = timeGetTime();
	static DWORD lastTime = timeGetTime();
	static float resultTime;
	resultTime = (currentTime - lastTime) * 0.001;

	// 1초당 dTime만큼 순회
	if (resultTime > 1.0f / dTime) 
	{
		lastTime = currentTime;
		update();
	}
	currentTime = timeGetTime();
}

void update()
{
	static CHAR_INFO ci[X * Y];
	static COORD size = { X, Y };
	static COORD pos = { 0, 0 };
	static SMALL_RECT rect = { 0, 0, X, Y };

	static int x = 10;
	static int y = 10;

	static int count = 0;

	for (int i = 0; i < Y; i++)
	{
		for (int n = 0; n < X; n++)
		{
			ci[(i * X) + n].Char.UnicodeChar = map[i][n];
			ci[(i * X) + n].Attributes = count % 15;
		}
	}

	if (GetAsyncKeyState('W'))
	{
		if (playerUpCheck(x, y, '#')) 
		{
			y--;
		}
	}
	if (GetAsyncKeyState('S'))
	{
		if (playerDownCheck(x, y, '#'))
		{
			y++;
		}
	}
	if (GetAsyncKeyState('A'))
	{
		if (playerRightCheck(x, y, '#'))
		{
			x--;
		}
	}
	if (GetAsyncKeyState('D'))
	{
		if (playerLeftCheck(x, y, '#'))
		{
			x++;
		}
	}

	for (int i = 0; i < Y; i++)
	{
		for (int n = 0; n < X; n++)
		{
			ci[(i * X) + n].Char.UnicodeChar = map[i][n];
			ci[(i * X) + n].Attributes = count % 15;
		}
		ci[(y * X) + x].Char.UnicodeChar = '■';
	}

	//for (int i = 20; i < Y; i++)
	//{
	//	for (int n = 100; n < X; n++)
	//	{
	//		ci[(i * X) + n].Char.UnicodeChar = '0';
	//	}
	//}

	WriteConsoleOutput(screen, ci, size, pos, &rect);

	count++;
}

void setActiveCursor(HANDLE& handle, char isShow)//커서숨기기
{
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 3;

	SetConsoleCursorInfo(handle, &ConsoleCursor);
}

bool playerUpCheck(int x, int y, char c)
{
	if (map[y - 1][x] != c && map[y - 1][x + 1] != c)
	{
		return true;
	}
	return false;
}

bool playerDownCheck(int x, int y, char c)
{
	if (map[y + 1][x] != c && map[y + 1][x + 1] != c)
	{
		return true;
	}
	return false;
}

bool playerRightCheck(int x, int y, char c)
{
	if (map[y][x - 1] != c)
	{
		return true;
	}
	return false;
}

bool playerLeftCheck(int x, int y, char c)
{
	if (map[y][x + 2] != c)
	{
		return true;
	}
	return false;
}