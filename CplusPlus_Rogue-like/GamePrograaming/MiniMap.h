#pragma once
#include <Windows.h>

#include "Floor.h"

class MiniMap
{
public:
	Floor floor;
	bool miniMapOnOff;
	Vector2 position;
	inline MiniMap(Floor f, Vector2 minimapPos)
	{
		floor = f;
		miniMapOnOff = true;
		position = minimapPos;
	}
	inline MiniMap() { }

	void showMiniMap(CHAR_INFO*, Vector2);
};

