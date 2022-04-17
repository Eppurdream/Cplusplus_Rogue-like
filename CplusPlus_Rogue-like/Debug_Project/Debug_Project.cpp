#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

void prnMap(char arr[][200], int x, int y)
{
	system("cls");
	for (int i = y; i < y + 30; i++)
	{
		for (int n = x; n < x + 60; n++)
		{
			cout << arr[i][n];
		}
		cout << endl;
	}
}

int main()
{
	system("mode con: cols=200 lines=100");
	char arr[100][200];
	for (int i = 0; i < 100; i++)
	{
		for (int n = 0; n < 200; n++)
		{
			if ((n + i) % 2 == 0)
			{
				arr[i][n] = ' ';
			}
			else
			{
				arr[i][n] = '0' + (i % 10);
			}
		}
	}

	int x = 0;
	int y = 0;
	char key = 0;
	prnMap(arr, x, y);
	while (true) // 이정도로 하면 되지 않을까??
	{
		if (_kbhit())
		{
			key = _getch();
			key = tolower(key);
			if (key == 'w'){
				if (y > 0)
				{
					y--;
					prnMap(arr, x, y);
				}
			} else if (key == 's') {
				if (y < 70)
				{
					y++;
					prnMap(arr, x, y);
				}
			} else if (key == 'a') {
				if (x > 0)
				{
					x--;
					prnMap(arr, x, y);
				}
			} else if (key == 'd') {
				if (x < 150)
				{
					x++;
					prnMap(arr, x, y);
				}
			}
		}
	}

	for (int i = 0; i < 100; i++)
	{
		for (int n = 0; n < 200; n++)
		{
			cout << arr[i][n];
		}
		cout << endl;
	}
	cout << "Hello world!";
	return 0;
}