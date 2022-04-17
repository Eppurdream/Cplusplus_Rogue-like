#pragma once
#include <Windows.h>
#pragma comment(lib, "winmm.lib")

class System
{
private:
	float fps;
public:
	System(float fps) : fps(fps) {}

	void update(void (*func)());
	void cls(int x, int y, CHAR_INFO *cinfo);
};

