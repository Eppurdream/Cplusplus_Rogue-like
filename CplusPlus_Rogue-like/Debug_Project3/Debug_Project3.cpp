#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <ctime>

static int g_nScreenIndex; // bss메모리에 들어가며 0으로 초기화, 0과 1의 값만 가진 변수로 활용
static HANDLE g_hScreen[2]; // 화면 버퍼들
int g_numofFPS; // 1초딩 fps의 값
clock_t CurTime, OldTime; // 1초가 지나는 걸 알아내는 변수
char* FPSTextInfo; // sprintf 할때 문자열을 넣을 변수

void ScreenInit() // 화면 버퍼 2개 만들고 커서 숨기는 함수
{
    CONSOLE_CURSOR_INFO cci;

    // 화면 버퍼 2개를 만든다.
    g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    // 커서를 숨긴다.
    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(g_hScreen[0], &cci);
    SetConsoleCursorInfo(g_hScreen[1], &cci);
}

void ScreenFlipping() // 화면 체인지 하는거
{
    SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
    g_nScreenIndex = !g_nScreenIndex;
}

void ScreenClear()
{
    COORD Coor = { 0, 0 };
    DWORD dw;
    FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 80 * 25, Coor, &dw);
}

void ScreenRelease()
{
    CloseHandle(g_hScreen[0]);
    CloseHandle(g_hScreen[1]);
}

void ScreenPrint(int x, int y, char* string)
{
    DWORD dw;
    COORD CursorPosition = { x, y };
    SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
    WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
}

void Render()
{
    //ScreenClear();

    if (CurTime - OldTime >= 1000) // 출력 코드
    {
        sprintf(FPSTextInfo, "FPS : %d", g_numofFPS);
        OldTime = CurTime;
        g_numofFPS = 0;
    }

    g_numofFPS++;
    ScreenPrint(0, 0, FPSTextInfo);
    ScreenFlipping();
}

void Release() // 삭제하는거
{
    delete[] FPSTextInfo;
}

int main()
{
    g_numofFPS = 0;
    FPSTextInfo = new char[128];
    memset(FPSTextInfo, '\0', 128);

    ScreenInit();

    OldTime = clock(); // 시간을 측정한다. 1초마다 갱신한다.

    while (1)
    {
        CurTime = clock();
        Render();
    }

    Release();
    ScreenRelease();

    return 0;
}


//#include <iostream>
//#include <Windows.h>
//#include <conio.h>
//using namespace std;
//
//int main()
//{
//	CONSOLE_CURSOR_INFO Cur = { 100, FALSE };
//	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Cur);
//	return 0;
//}