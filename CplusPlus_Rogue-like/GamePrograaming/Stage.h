#pragma once
#include <Windows.h>

class Stage
{
private:
	int mapSizeX;
	int mapSizeY;

public:
	CHAR_INFO* cinfoMap;
	inline Stage(int x, int y, CHAR_INFO* map) : mapSizeX(x), mapSizeY(y)
	{
		cinfoMap = new CHAR_INFO[x * y];
		for (int i = 0; i < y; i++)
		{
			for (int n = 0; n < x; n++)
			{
				cinfoMap[(i * x) + n].Char.UnicodeChar = map[(i * x) + n].Char.UnicodeChar;
			}
		}
	}
	inline Stage() { mapSizeX = 101, mapSizeY = 30; cinfoMap = new CHAR_INFO[mapSizeX * mapSizeY]; }
	void setMap(CHAR_INFO* map);
	void drawMap(CHAR_INFO* screen);

	inline const bool operator!=(Stage s) const
	{
		return cinfoMap != s.cinfoMap;
	}
	inline const bool operator==(Stage s) const
	{
		return cinfoMap == s.cinfoMap;
	}
};

