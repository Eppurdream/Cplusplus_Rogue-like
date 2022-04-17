#include "Input.h"


void Input::checkClick()
{
	leftClickDown = GetAsyncKeyState('A');
	rightClickDown = GetAsyncKeyState('D');
	upClickDown = GetAsyncKeyState('W');
	downClickDown = GetAsyncKeyState('S');
	testKey = GetAsyncKeyState('R');
	mapKey = GetAsyncKeyState('M') & 1;
}