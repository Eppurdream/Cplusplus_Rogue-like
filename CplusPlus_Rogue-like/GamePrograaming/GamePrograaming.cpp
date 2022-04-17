#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h>
#include <vector>
#include <time.h>

#include "Vector2.h"
#include "System.h"
#include "Input.h"
#include "Player.h"
#include "Bullet.h"
#include "StageList.h"
#include "Floor.h"
#include "MiniMap.h"
#include "Enemy.h"

#define X 101
#define Y 30

using namespace std;

System Csystem(60);					// 인수 60은 1초당 몇번 update를 실행할지
Input input;						// 입력 받은 키 값들을 정리해놓은 것
Player player = Player(Vector2(10, 10), 3, 9);	// 플레이어의 정보를 담아둔 거

CHAR_INFO screen[X * Y];			// 화면을 나타내는 배열
COORD bufferSize = { X, Y };
COORD pos = { 0, 0 };
SMALL_RECT rect = { 0, 0, X, Y };

vector<Bullet> bullets;

Floor oneStage;

MiniMap minimap;

void update();
void startUpdate();
void start();
void endGame();
void monsterSpawn();

void keyEvent();

void (*inGame)();
void (*startGame)();

bool isEnd = false;
bool isStart = false;

vector<Enemy> enemys;

string hpUI = { "HP : " };

int main()
{
	start();
	inGame = update;
	startGame = startUpdate;
	while (!isStart) // 시작 씬
	{
		Csystem.update(startGame);
	}
	while (!isEnd) // 게임 씬
	{
		Csystem.update(inGame);
	}
	
	return 0;
}

/// <summary>
/// 가장 처음 실행하는 함수
/// </summary>
void start()
{
	system("mode con:cols=100 lines=30");

	srand(time(NULL));

	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

	SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));

	oneStage.InitFloor();
	minimap = MiniMap(oneStage, Vector2(90, 6));
}

// - 색깔들 -
//0 = 검은색       8 = 회색
//1 = 파란색        9 = 연한 파란색
//2 = 녹색       A = 연한 녹색
//3 = 청록색        B = 연한 청록색
//4 = 빨간색         C = 연한 빨간색
//5 = 자주색      D = 연한 자주색
//6 = 노란색      E = 연한 노란색
//7 = 흰색       F = 밝은 흰색

/// <summary>
/// 정해진 프레임당 계속 반복해서 실행하는 함수
/// </summary>
void update()
{
	static DWORD currentTime = timeGetTime();
	static DWORD lastTime = timeGetTime();

	float resultTime = (currentTime - lastTime) * 0.001f;

	Csystem.cls(X, Y, screen);	//프레임 마다 화면을 지워줌

	if (player.isDead)
	{
		isEnd = true;
		return;
	}

	for (int i = 0; i < Y; i++)
	{
		for (int n = 0; n < X; n++)
		{
			screen[(i * X) + n].Char.UnicodeChar = '.';
			screen[(i * X) + n].Attributes = 8;
		}
	}

	if (player.isDamage && resultTime > 1.0f)
	{
		player.hp -= 1;
		player.isDamage = false;
		lastTime = timeGetTime();
	}
	currentTime = timeGetTime();

	if (find(oneStage.floorVec.begin(), oneStage.floorVec.end(), oneStage.currentPos) != oneStage.floorVec.end())
	{
		if (oneStage.currentPos == oneStage.bossRoom)
		{
			oneStage.stageList.stages[1].drawMap(screen);
		}
		else
		{
			oneStage.floor[oneStage.currentPos].drawMap(screen);
		}
	}

	if (screen[(player.position.y * X) + player.position.x].Char.UnicodeChar == '!')
	{
		endGame();
		return;
	}

	for (int i = 0; i < enemys.size(); i++)
	{
		screen[(X * enemys[i].position.y) + enemys[i].position.x].Char.UnicodeChar = '@';
		screen[(X * enemys[i].position.y) + enemys[i].position.x].Attributes = 12;
	}
	screen[(player.position.y * X) + player.position.x].Char.UnicodeChar = '+';
	screen[(player.position.y * X) + player.position.x].Attributes = 15;

	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i].enemyMove(player.position, screen, &player);
	}



	input.checkClick();
	keyEvent();

	minimap.showMiniMap(screen, oneStage.currentPos);

	for (int i = 4; i < 4 + hpUI.size(); i++)
	{
		screen[(4 * X) + i].Char.UnicodeChar = hpUI[i - 4];
	}
	string hp = to_string(player.hp);
	screen[(4 * X) + 4 + hpUI.size()].Char.UnicodeChar = hp[0];

	WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), screen, bufferSize, pos, &rect);
}

int moveCount = 3;
int c = 0;

char startGameArr[10] = { "startGame" };
char pressS[10] = { "press : S" };

int temp = 0;
bool breverse = false;

void startUpdate()
{
	Csystem.cls(X, Y, screen);	//프레임 마다 화면을 지워줌
	
	if (_kbhit())
	{
		isStart = true;
	}
	int arrc = 0;
	for (int i = 0; i < Y; i++)
	{
		for (int n = 0; n < X; n++)
		{
			if (i == Y / 2 - 4 && n > temp % X - 1 && n < temp + 10 % 20 - 1)
			{
				screen[(i * X) + n].Char.UnicodeChar = startGameArr[arrc];
				screen[((i + 2) * X) + n].Char.UnicodeChar = pressS[arrc];
				screen[(i * X) + n].Attributes = 15;
				screen[((i + 2) * X) + n].Attributes = 15;
				arrc++;
			}
		}
	}

	if (c == 0)
	{
		if (temp > X - 11 || temp < 0)
		{
			breverse = !breverse;
		}

		if (breverse)
		{
			temp--;
		}
		else
		{
			temp++;
		}
		c = moveCount;
	}
	else
	{
		c--;
	}

	WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), screen, bufferSize, pos, &rect);
}

string endStr = "Congratulations, you got out of here";

/// <summary>
/// 마지막에 실행하는 함수
/// </summary>
void endGame()
{
	int count = 0;
	for (int i = 0; i < Y; i++)
	{
		for (int n = 0; n < X; n++)
		{
			if (i == Y / 2 && n > X / 2 - (endStr.size() / 2) && n < X / 2 + (endStr.size() / 2) + 1)
			{
				screen[(i * X) + n].Char.UnicodeChar = endStr[count];
				screen[(i * X) + n].Attributes = 15;
				count++;
			}
			else
			{
				screen[(i * X) + n].Char.UnicodeChar = ' ';
			}
		}
	}

	WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), screen, bufferSize, pos, &rect);
	for (int i = 0; i < 30; i++)
	{
		cout << endl;
	}
	isEnd = true;
}

/// <summary>
/// 입력 받은 키 값에 따라서 이벤트를 발생시키기는 함수
/// </summary>
void keyEvent()
{
	static int moveCount = player.speed;

	// w, s, a, d 순으로 키를 누르면 플레이어의 위치를 움직일 수 있다
	if (_kbhit())
	{
		if (moveCount == 0)
		{
			if (input.upClickDown)
			{
				if (screen[((player.position.y - 1) * 101) + player.position.x].Attributes == 6)
				{
					if (oneStage.moveFloor('u'))
					{
						monsterSpawn();
						player.position = Vector2(50, 28);
					}
				}
				player.move(screen, Vector2::up);
			}
			if (input.downClickDown)
			{
				if (screen[((player.position.y + 1) * 101) + player.position.x].Attributes == 6)
				{
					if (oneStage.moveFloor('d'))
					{
						monsterSpawn();
						player.position = Vector2(50, 1);
					}
				}
				player.move(screen, Vector2::down);
			}
			if (input.leftClickDown)
			{
				if (screen[((player.position.y) * 101) + player.position.x - 1].Attributes == 6)
				{
					if (oneStage.moveFloor('l'))
					{
						monsterSpawn();
						player.position = Vector2(98, 15);
					}
				}
				player.move(screen, Vector2::left);
			}
			if (input.rightClickDown)
			{
				if (screen[((player.position.y) * 101) + player.position.x + 1].Attributes == 6)
				{
					if (oneStage.moveFloor('r'))
					{
						monsterSpawn();
						player.position = Vector2(1, 15);
					}
				}
				player.move(screen, Vector2::right);
			}
			moveCount = player.speed;
		}
		else
		{
			moveCount--;
		}

		if (input.mapKey)
		{
			minimap.miniMapOnOff = !minimap.miniMapOnOff;
		}
	}
}

void monsterSpawn()
{
	enemys.clear();
	int randomSpawn = rand() % 10 + 5;
	for (int i = 0; i < randomSpawn; i++)
	{
		enemys.push_back(Enemy(Vector2(rand() % 60 + 20, rand() % 20 + 4), 10));
	}
}