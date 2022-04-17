#pragma once
#include <Windows.h>

class Input
{
public:
	bool leftClickDown;
	bool rightClickDown;
	bool upClickDown;
	bool downClickDown;
	bool testKey;
	bool mapKey;

	void checkClick();
};

