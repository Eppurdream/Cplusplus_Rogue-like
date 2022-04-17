#include "Stage.h"

void Stage::setMap(CHAR_INFO* map)
{
	for (int i = 0; i < mapSizeY; i++)
	{
		for (int n = 0; n < mapSizeX; n++)
		{
			cinfoMap[(i * mapSizeX) + n].Char.UnicodeChar = map[(i * mapSizeX) + n].Char.UnicodeChar;
		}
	}
}

void Stage::drawMap(CHAR_INFO* screen)
{
	for (int i = 0; i < mapSizeY; i++)
	{
		for (int n = 0; n < mapSizeX; n++)
		{
			if (cinfoMap[(i * mapSizeX) + n].Char.UnicodeChar != ' ')
			{
				if (cinfoMap[(i * mapSizeX) + n].Char.UnicodeChar == '/')
				{
					screen[(i * mapSizeX) + n].Attributes = 6;
				}
				else
				{
					screen[(i * mapSizeX) + n].Char.UnicodeChar = cinfoMap[(i * mapSizeX) + n].Char.UnicodeChar;
				}
			}
		}
	}
}