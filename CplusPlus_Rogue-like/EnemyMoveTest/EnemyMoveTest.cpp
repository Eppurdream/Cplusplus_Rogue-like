#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
using namespace std;
#pragma comment(lib, "winmm.lib")

const int x = 100;
const int y = 50;

void deltaTime(float dTime);
void update();

char map[y][x + 1] = {
	"####################################################################################################",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"#                                                                                                  #",
	"####################################################################################################"
};

class Bullet
{
private:
	int range;
	int whereToMove;
	int bulletX;
	int bulletY;
public:
	inline Bullet(int _range, int _whereToMove, int x, int y)// 1은 위 2는 아래 3은 오른 4는 왼
	{
		range = _range;
		whereToMove = _whereToMove;
		bulletX = x;
		bulletY = y;
	}
	bool bulletMove();
	int getX();
	int getY();
};

bool Bullet::bulletMove()
{
	if (whereToMove == 1)
	{
		if (map[bulletY - 1][bulletX] != '#')
		{
			bulletY--;
		}
	}
	else if (whereToMove == 2)
	{
		if (map[bulletY + 1][bulletX] != '#')
		{
			bulletY++;
		}
	}
	else if (whereToMove == 3)
	{
		if (map[bulletY][bulletX + 1] != '#')
		{
			bulletX++;
		}
	}
	else if (whereToMove == 4)
	{
		if (map[bulletY][bulletX - 1] != '#')
		{
			bulletX--;
		}
	}
	range--;
	return range <= 0;
}

int Bullet::getX()
{
	return bulletX;
}

int Bullet::getY()
{
	return bulletY;
}

class Enemy
{
private:
	int enemyX;
	int enemyY;
	int hp;
	int speed;
	int enemySpeed;
public:
	inline Enemy(int x, int y, int _hp, int _speed)
	{
		enemyX = x;
		enemyY = y;
		hp = _hp;
		speed = _speed;
		enemySpeed = 0;
	}
	void enemyMove(int playerX, int playerY, vector<Enemy> enemys);
	int getX();
	int getY();
	bool damage(int damage);
	bool isFull(int x, int y, vector<Enemy> enemys);
};

void Enemy::enemyMove(int playerX, int playerY, vector<Enemy> enemys)
{
	if (enemyX > playerX && !isFull(enemyX - 1, enemyY, enemys))
	{
		enemySpeed++;
		if (enemySpeed > speed)
		{
			enemyX--;
			enemySpeed = 0;
		}
	}
	if (enemyX < playerX && !isFull(enemyX + 1, enemyY, enemys))
	{
		enemySpeed++;
		if (enemySpeed > speed)
		{
			enemyX++;
			enemySpeed = 0;
		}
	}
	if (enemyY > playerY && !isFull(enemyX, enemyY - 1, enemys))
	{
		enemySpeed++;
		if (enemySpeed > speed)
		{
			enemyY--;
			enemySpeed = 0;
		}
	}
	if (enemyY < playerY && !isFull(enemyX, enemyY + 1, enemys))
	{
		enemySpeed++;
		if (enemySpeed > speed)
		{
			enemyY++;
			enemySpeed = 0;
		}
	}
}

int Enemy::getX()
{
	return enemyX;
}

int Enemy::getY()
{
	return enemyY;
}

bool Enemy::damage(int damage)
{
	hp -= damage;
	return hp <= 0;
}

bool Enemy::isFull(int x, int y, vector<Enemy> enemys)
{
	for (int i = 0; i < enemys.size(); i++)
	{
		if (enemys[i].getX() == x && enemys[i].getY() == y) 
		{
			return true;
		}
	}
	return false;
}

HANDLE screen;
CHAR_INFO info[x * y];
COORD scrSize = { x, y };
COORD pos = { 0, 0 };
SMALL_RECT rect = { 0, 0, x, y };

vector<Bullet> bullets;
vector<Enemy> enemys;

int main()
{
	system("mode con: cols=100 lines=50");
	screen = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, 0, 0, CONSOLE_TEXTMODE_BUFFER, 0);
	SetConsoleActiveScreenBuffer(screen);
	while (true)
	{
		deltaTime(20);
	}
	CloseHandle(screen);
	return 0;
}

void deltaTime(float dTime)
{
	static DWORD currentTime = timeGetTime();
	static DWORD lastTime = timeGetTime();
	static float resultTime;
	resultTime = (float)(currentTime - lastTime) * 0.001f;

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
	static int playerX = 50;
	static int playerY = 25;

	static int count = 0;

	static int enemyCountY = 5;

	static bool testb = false;

	for (int i = 0; i < y; i++)
	{
		for (int n = 0; n < x; n++)
		{
			info[(i * x) + n].Char.UnicodeChar = map[i][n];
			info[(i * x) + n].Attributes = 15;
		}
	}
	if (GetKeyState('W') & 0x8000)
	{
		if (map[playerY - 1][playerX] != '#')
			playerY--;
	}
	if (GetKeyState('S') & 0x8000)
	{
		if (map[playerY + 1][playerX] != '#')
			playerY++;
	}
	if (GetKeyState('A') & 0x8000)
	{
		if (map[playerY][playerX - 1] != '#')
			playerX--;
	}
	if (GetKeyState('D') & 0x8000)
	{
		if (map[playerY][playerX + 1] != '#')
			playerX++;
	}
	bool isbullethere = false;
	if (GetKeyState(VK_UP) & 0x8000)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i].getX() == playerX && bullets[i].getY() == playerY - 1)
			{
				isbullethere = true;
			}
		}
		if (!isbullethere)
		{
			Bullet bullet(50, 1, playerX, playerY - 1);
			bullets.push_back(bullet);
		}
		isbullethere = false;
	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i].getX() == playerX && bullets[i].getY() == playerY + 1)
			{
				isbullethere = true;
			}
		}
		if (!isbullethere)
		{
			Bullet bullet(50, 2, playerX, playerY + 1);
			bullets.push_back(bullet);
		}
		isbullethere = false;
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i].getX() == playerX + 1 && bullets[i].getY() == playerY)
			{
				isbullethere = true;
			}
		}
		if (!isbullethere)
		{
			Bullet bullet(50, 3, playerX + 1, playerY);
			bullets.push_back(bullet);
		}
		isbullethere = false;
	}
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i].getX() == playerX - 1 && bullets[i].getY() == playerY)
			{
				isbullethere = true;
			}
		}
		if (!isbullethere)
		{
			Bullet bullet(50, 4, playerX - 1, playerY);
			bullets.push_back(bullet);
		}
		isbullethere = false;
	}

	if (GetKeyState('O') & 0x8000)
	{
		bool isFull = false;
		for (int i = 0; i < enemys.size(); i++)
		{
			if (enemys[i].getX() == 10 && enemys[i].getY() == enemyCountY)
			{
				isFull = true;
			}
		}
		if (!isFull)
		{
			if (enemyCountY == 1 || enemyCountY == 48)
				testb = !testb;
			enemyCountY += testb ? 1 : -1;
			Enemy enemy(10, enemyCountY, 4, 2);
			enemys.push_back(enemy);
		}
	}

	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i].enemyMove(playerX, playerY, enemys);
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].bulletMove())
		{
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}
	//enemys의 x, bullets의 x 가 같은 것과
	//enemys의 y, bullets의 y 가 같은 것을 찾는 거


	vector<Bullet>::iterator bulletIter;
	vector<Enemy>::iterator EnemyIter;

	for (int i = 0; i < bullets.size(); i++)
	{
		for (int n = 0; n < enemys.size(); n++)
		{
			if (bullets[i].getX() == enemys[n].getX() && bullets[i].getY() == enemys[n].getY())
			{
				if (enemys[n].damage(1))
				{
					enemys.erase(enemys.begin() + n);
					n--;
				}
				bullets.erase(bullets.begin() + i);
				i--;
			}
		}
	}

	//for (int i = 0; i < bullets.size(); i++)
	//{
	//	for (int n = 0; n < enemys.size(); n++)
	//	{
	//		if (bullets[i].getX() == enemys[n].getX() && bullets[i].getY() == enemys[n].getY())
	//		{
	//			if (enemys[n].damage(1)) 
	//			{
	//				enemys.erase(enemys.begin() + n);
	//				n--;
	//			}
	//			bullets.erase(bullets.begin() + i);
	//			i--;
	//		}
	//	}
	//}

	for (int i = 0; i < bullets.size(); i++)
	{
		info[((bullets[i].getY() * x) + bullets[i].getX())].Char.UnicodeChar = '+';
	}

	for (int i = 0; i < enemys.size(); i++)
	{
		info[((enemys[i].getY() * x) + enemys[i].getX())].Char.UnicodeChar = '@';
	}

	info[(playerY * x) + playerX].Char.UnicodeChar = '&';
	string bulletsStr = to_string(bullets.size());
	string enemysStr = to_string(enemys.size());
	for(int i = 0; i < bulletsStr.size(); i++)
	{
		info[(49 * x) + i].Char.UnicodeChar = bulletsStr[i];
	}
	for (int i = 0; i < enemysStr.size(); i++)
	{
		info[i].Char.UnicodeChar = enemysStr[i];
	}
	count++;
	WriteConsoleOutput(screen, info, scrSize, pos, &rect);
}