#pragma once
#include <Windows.h>
#include <string>

#include "Vector2.h"
#include "Input.h"

class Player
{
public:
	int speed;
	int hp;
	bool isDead;
	bool isDamage;
	Vector2 position;
	Player(Vector2 pos, int speed, int hp) 
		: position(pos), speed(speed), hp(hp) 
	{ isDead = false; isDamage = false; }
	void move(CHAR_INFO*, Vector2);
	void onDamage();
};

