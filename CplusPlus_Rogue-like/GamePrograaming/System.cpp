#include "System.h"

void System::update(void (*func)())
{
	static DWORD currentTime = timeGetTime();
	static DWORD lastTime = timeGetTime();
	static float resultTime;
	resultTime = (currentTime - lastTime) * 0.001;
	
	if (resultTime > 1.0f / fps)
	{
		lastTime = currentTime;
		func();
	}
	currentTime = timeGetTime();
}

void System::cls(int x, int y,CHAR_INFO *cinfo)
{
	for (int i = 0; i < y; i++)
	{
		for (int n = 0; n < x; n++)
		{
			cinfo[(i * x) + n].Char.UnicodeChar = ' ';
		}
	}
}