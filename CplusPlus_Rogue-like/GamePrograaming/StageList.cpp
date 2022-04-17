#include "StageList.h"

//이놈이 x, y 6이상 나가면 이상해요

StageList::StageList()
{
	const int X = 101;
	const int Y = 30;

	CHAR_INFO defaultMap[X * Y];

	for (int i = 0; i < Y; i++)
	{
		for (int n = 0; n < X; n++)
		{
			if (i == 0 || i == 29 || n == 0 || n == 99)
			{
				if ((i > 12 && i < 18) || (n > 45 && n < 55))
				{
					defaultMap[(i * X) + n].Char.UnicodeChar = '/';
				}
				else
				{
					defaultMap[(i * X) + n].Char.UnicodeChar = '#';
				}
			}
			else
			{
				defaultMap[(i * X) + n].Char.UnicodeChar = ' ';
			}
		}
	}
	stages.push_back(Stage(X, Y, defaultMap));
	stages.push_back(Stage(X, Y, defaultMap));

	for (int i = 0; i < Y; i++)
	{
		for (int n = 0; n < X; n++)
		{
			if ((i > 13 && i < 17) && (n > 47 && n < 54))
			{
				stages[1].cinfoMap[(i * X) + n].Char.UnicodeChar = '!';
			}
		}
	}
}

Stage StageList::RandomStage()
{
	count = (count + 1) % stages.size();
	return stages[count];
}