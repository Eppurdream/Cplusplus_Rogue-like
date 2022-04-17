#include "Enemy.h"

void Enemy::enemyMove(Vector2 playerPos, CHAR_INFO* screen, Player* player)
{
	int x = position.x - playerPos.x;
	int y = position.y - playerPos.y;
	static int count = speed;

	if (count <= 0)
	{
		if (x < 0)
		{
			if (checkMove(screen, Vector2(position.x + 1, position.y), player))
			{
				position.x++;
				count = speed;
			}
		}
		if (x > 0)
		{
			if (checkMove(screen, Vector2(position.x - 1, position.y), player))
			{
				position.x--;
				count = speed;
			}
		}
		if (y < 0)
		{
			if (checkMove(screen, Vector2(position.x, position.y + 1), player))
			{
				position.y++;
				count = speed;
			}
		}
		if (y > 0)
		{
			if (checkMove(screen, Vector2(position.x, position.y - 1), player))
			{
				position.y--;
				count = speed;
			}
		}
	}
	else
	{
		count--;
	}
}

bool Enemy::checkMove(CHAR_INFO* screen, Vector2 pos, Player* player)
{
	if (screen[(pos.y * 101) + pos.x].Char.UnicodeChar == '#')
	{
		return false;
	}
	else if (screen[(pos.y * 101) + pos.x].Char.UnicodeChar == '+')
	{
		player->onDamage();
		return false;
	}
	else if (screen[(pos.y * 101) + pos.x].Char.UnicodeChar == '@')
	{
		return false;
	}
	return true;
}