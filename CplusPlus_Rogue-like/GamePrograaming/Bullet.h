#pragma once
#include "Vector2.h"

class Bullet
{
public:
	Vector2 dir;
	Vector2 position;
	int speed;
	int damage;

	inline Bullet(Vector2 dir, Vector2 position, int speed, int damage) : dir(dir), position(position), speed(speed), damage(damage) { }
};

