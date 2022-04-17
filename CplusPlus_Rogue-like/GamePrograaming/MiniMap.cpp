#include "MiniMap.h"

void MiniMap::showMiniMap(CHAR_INFO* screen, Vector2 currentPos)
{
	if (miniMapOnOff)
	{
		for (int i = 0; i < floor.floorVec.size(); i++)
		{
			if (floor.floorVec[i] == currentPos)
			{
				screen[((position.y + floor.floorVec[i].y) * 101) + position.x + floor.floorVec[i].x].Char.UnicodeChar = '+';
				continue;
			}
			screen[((position.y + floor.floorVec[i].y) * 101) + position.x + floor.floorVec[i].x].Char.UnicodeChar = '@';

		}
	}
}