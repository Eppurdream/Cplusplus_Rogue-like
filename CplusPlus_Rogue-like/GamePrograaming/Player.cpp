#include "Player.h"

void Player::move(CHAR_INFO* screen, Vector2 dir)
{
	if (screen[((position.y + dir.y) * 101) + position.x + dir.x].Char.UnicodeChar != '#' 
		&& screen[((position.y + dir.y) * 101) + position.x + dir.x].Attributes != 6)
	{
		position = position + dir;
	}
}

void Player::onDamage()
{
	isDamage = true;
	if (hp <= 0)
	{
		isDead = true;
	}
}