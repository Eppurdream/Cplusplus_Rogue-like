#pragma once
#include <vector>
#include <Windows.h>
#include "Player.h"
#include "Vector2.h"
using namespace std;

class Enemy
{
private:
	int speed;
public:
	Vector2 position;

	inline Enemy(Vector2 pos, int _speed)
	{
		position = pos;
		speed = _speed;
	}
	void enemyMove(Vector2 playerPos, CHAR_INFO* screen, Player* player);
	bool checkMove(CHAR_INFO* screen, Vector2 pos, Player* player);
};
