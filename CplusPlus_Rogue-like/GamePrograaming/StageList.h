#pragma once
#include <vector>
#include <map>
#include <time.h>

#include "Stage.h"
#include "Vector2.h"
using namespace std;

/// <summary>
/// �⺻���� Ʋ�� ���� �ʵ��� ��Ƴ��� Ŭ����
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

