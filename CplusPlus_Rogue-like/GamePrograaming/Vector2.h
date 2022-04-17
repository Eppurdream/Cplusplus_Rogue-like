#pragma once
#include <iostream>
using namespace std;

// ����Ƽ�� Vector2�� ����ϰ� �����Ծ��
// x, y ���� ������ �ִ� Ŭ��������
class Vector2
{
public:
	int x;
	int y;

	inline Vector2(int x, int y) : x(x), y(y) {	}
	inline Vector2() { x = 0; y = 0; }
	inline ~Vector2() {}

	static Vector2 one;
	static Vector2 left;
	static Vector2 right;
	static Vector2 up;
	static Vector2 down;
	static Vector2 zero;

	inline const bool operator < (Vector2 vec) const
	{
		return x < vec.x && y < vec.y;
	}
	inline const bool operator > (Vector2 vec) const
	{
		return x > vec.x && y > vec.y;
	}
	inline const bool operator <= (Vector2 vec) const
	{
		return x <= vec.x&& y <= vec.y;
	}
	inline const bool operator >= (Vector2 vec) const
	{
		return x >= vec.x && y >= vec.y;
	}

	inline const bool operator == (Vector2 vec) const
	{
		return x == vec.x && y == vec.y;
	}

	inline const bool operator != (Vector2 vec) const
	{
		return x != vec.x || y != vec.y;
	}

	inline const Vector2 operator + (Vector2 vec) const
	{
		return Vector2(x + vec.x, y + vec.y);
	}
};

