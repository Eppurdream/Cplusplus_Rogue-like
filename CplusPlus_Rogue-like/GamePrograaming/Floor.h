#pragma once
#include <map>
#include <time.h>
#include <vector>

#include "Vector2.h"
#include "Stage.h"
#include "StageList.h"

using namespace std;

class Floor
{
private:
	void checkMap(Vector2);
public:
	inline Floor()
	{
		
	}

	map<Vector2, Stage> floor;
	vector<Vector2> floorVec;
	Vector2 currentPos;
	Vector2 bossRoom;
	StageList stageList;

	void InitFloor();
	bool moveFloor(char);
	void addStage(Vector2 vec, Stage stage);
	
};

