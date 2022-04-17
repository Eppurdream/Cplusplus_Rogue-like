#pragma once
#include <vector>
#include <map>
#include <time.h>

#include "Stage.h"
#include "Vector2.h"
using namespace std;

/// <summary>
/// 기본적인 틀을 가진 맵들을 모아놓은 클래스
/// </summary>
class StageList
{
private:
	int count = 0;
public:
	//map<Vector2, Stage> stages;
	vector<Stage> stages;
	StageList();
	Stage RandomStage();
};

