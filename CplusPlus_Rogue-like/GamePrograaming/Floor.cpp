#include "Floor.h"
#include <conio.h>

void Floor::InitFloor()
{
	currentPos = Vector2::zero;

	addStage(currentPos, stageList.stages[0]);

	int mapListSize = stageList.stages.size();

	for (int n = 0; n < 15; n++)
	{
		int random = rand() % 4;
		switch (random)
		{
		case 1:
			currentPos = currentPos + Vector2::up;
			break;
		case 2:
			currentPos = currentPos + Vector2::down;
			break;
		case 3:
			currentPos = currentPos + Vector2::left;
			break;
		case 4:
			currentPos = currentPos + Vector2::right;
			break;
		}
		checkMap(currentPos);
	}


	for (int i = 1; i < floorVec.size(); i++)
	{
		if (floorVec[i - 1] > floorVec[i])
		{
			bossRoom = floorVec[i - 1];
		}
		else
		{
			bossRoom = floorVec[i];
		}
	}
	currentPos = Vector2::zero;
}

void Floor::checkMap(Vector2 vec)
{
	if (find(floorVec.begin(), floorVec.end(), currentPos) == floorVec.end())
	{
		addStage(currentPos, stageList.stages[0]);
	}
}

bool Floor::moveFloor(char c)
{
	switch (c)
	{
	case 'u':
		if (find(floorVec.begin(), floorVec.end(), currentPos + Vector2::up) == floorVec.end())
		{
			return false;
		}
		currentPos.y += -1;
		break;
	case 'd':
		if (find(floorVec.begin(), floorVec.end(), currentPos + Vector2::down) == floorVec.end())
		{
			return false;
		}
		currentPos.y += 1;
		break;
	case 'l':
		if (find(floorVec.begin(), floorVec.end(), currentPos + Vector2::left) == floorVec.end())
		{
			return false;
		}
		currentPos.x += -1;
		break;
	case 'r':
		if (find(floorVec.begin(), floorVec.end(), currentPos + Vector2::right) == floorVec.end())
		{
			return false;
		}
		currentPos.x += 1;
		break;
	}
	return true;
}

void Floor::addStage(Vector2 vec, Stage stage)
{
	floorVec.push_back(vec);
	floor[vec] = stage;
}