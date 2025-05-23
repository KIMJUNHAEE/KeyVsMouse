#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>	
#include <vector>

#include "MONSTER.h"

HINSTANCE g_hlnst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Key Vs Mouse";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);

int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	srand((unsigned)time(NULL));

	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hlnst = hlnstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hlnstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_ERROR);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_ERROR);
	RegisterClassExW(&WndClass); // RegisterClassExW -> 유니코드 지원

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME, 0, 0, 1600, 900, NULL, (HMENU)NULL, hlnstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC, hMem1DC, hMem2DC;
	HBITMAP hBitmap;

	static RECT ViewRect;
	static HPEN hPen, hOldPen;
	static HBRUSH hBrush, hOldBrush;

	static POINT cursor; // 마우스 커서 좌표
	static float deltaTime = 16.0f / 1000.0f; // 60fps 기준 1초 재기 위한 단위;
	
	static std::vector<MONSTER> monsters; // 몬스터 벡터 선언

	switch (iMessage) {

	case WM_CREATE:
		SetTimer(hWnd, 1, 16, NULL); // 60프레임 타이머 생성
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		for (auto& monster : monsters) { // monster를 참조자로  monsters vector 전체 순회하며 루프
			monster.Draw(hDC);
		}
		break;
	case WM_CHAR:

		
		break;

	case WM_TIMER:
		
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_KEYDOWN:

		break;
	case WM_LBUTTONDOWN:
		monsters.push_back({ 1,cursor.x,cursor.y }); // 몬스터 생성
		break;
	case WM_MOUSEMOVE:
		cursor.x = LOWORD(lParam);
		cursor.y = HIWORD(lParam);
		
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1); // 타이머 제거
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
