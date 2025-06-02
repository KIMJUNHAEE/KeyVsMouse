#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>	
#include <vector>

#include "PLAYER1.h"
#include "MONSTER.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

int MoveCheck = 0; // 0: 정지, 1: 위, 2: 아래, 3: 왼쪽, 4: 오른쪽
int MoveCount = 0; // 움직임 카운트 (애니메이션 프레임을 위한 카운트)

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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, (HMENU)NULL, hlnstance, NULL);
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
	static HBITMAP BackGroundhBitmap;
	HBITMAP BGoldBitmap;
	HBITMAP hBitmap, hOldBitmap;

	static RECT ViewRect;
	static HPEN hPen, hOldPen;
	static HBRUSH hBrush, hOldBrush;
	static PLAYER1 player(10, 500, 500, 5, 10, 10, 2, 0, down); // 생성자

	static POINT cursor; // 마우스 커서 좌표
	static float DeltaTime = 16.0f / 1000.0f; // 60fps 기준 1초 재기 위한 단위;
	
	static std::vector<MONSTER> monsters; // 몬스터 벡터 선언

	switch (iMessage) {

	case WM_CREATE:
		GetClientRect(hWnd, &ViewRect);
		ImageCreate();

		player.SetCamera();

		TCHAR BGfilepath[256];
		_stprintf_s(BGfilepath, _T("Play_graphics/background.bmp")); // 예시: "resources/player0.bmp", "resources/player1.bmp" 등
		BackGroundhBitmap = (HBITMAP)LoadImage(NULL, BGfilepath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (BackGroundhBitmap == NULL) {
			MessageBox(hWnd, _T("Failed to load background image"), _T("Error"), MB_OK | MB_ICONERROR);
			return -1;
		}

		SetTimer(hWnd, 1, 16, NULL); // 60프레임 타이머 생성
		break;
	case WM_PAINT: {
		hDC = BeginPaint(hWnd, &ps);

		hMem1DC = CreateCompatibleDC(hDC);
		BGoldBitmap = (HBITMAP)SelectObject(hMem1DC, BackGroundhBitmap);
		FillRect(hMem1DC, &ViewRect, (HBRUSH)GetStockObject(WHITE_BRUSH));
		if (MoveCheck == 0) {
			player.Draw(hDC, hMem1DC);
		}
		else if (MoveCheck == 1) {
			player.UMDraw(hDC, hMem1DC, MoveCount);
		}
		else if (MoveCheck == 2) {
			player.DMDraw(hDC, hMem1DC, MoveCount);
		}
		else if (MoveCheck == 3) {
			player.LMDraw(hDC, hMem1DC, MoveCount);
		}
		else if (MoveCheck == 4) {
			player.RMDraw(hDC, hMem1DC, MoveCount);
		}
		DeleteDC(hMem1DC);


		// Mem2DC 에 몬스터 더블버퍼링
		hMem2DC = CreateCompatibleDC(hDC);
		hBitmap = CreateCompatibleBitmap(hDC, WINDOW_WIDTH, WINDOW_HEIGHT);
		hOldBitmap = (HBITMAP)SelectObject(hMem2DC, hBitmap);
		FillRect(hMem2DC, &ViewRect, (HBRUSH)GetStockObject(WHITE_BRUSH));
		for (auto& monster : monsters) { // monster를 참조자로  monsters vector 전체 순회하며 루프
			monster.Draw(hMem2DC);
		}
		BitBlt(hDC, ViewRect.left, ViewRect.top, ViewRect.right, ViewRect.bottom, hMem2DC, 0, 0, SRCCOPY);
		SelectObject(hMem2DC, hOldBitmap);
		DeleteObject(hBitmap);
		DeleteDC(hMem2DC);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_CHAR:
		break;

	case WM_TIMER: {
		player.SetHeadRect();
		player.SetBodyRect();
		player.SetTarget();
		POINT point = { player.Tx, player.Ty };
		for (auto monster = monsters.begin(); monster != monsters.end();) {
			if (monster->Update(DeltaTime)) {
				monster = monsters.erase(monster);
			}
			else {
				monster->MoveToPlayer(point, player.HeadRect, player.BodyRect, DeltaTime);
				monster++;
			}
		}

		InvalidateRect(hWnd, NULL, FALSE);
		break;
	}
	case WM_KEYDOWN:
		if (wParam == 'W') {
			player.MoveUp();
			MoveCheck = 1;
			InvalidateRect(hWnd, NULL, FALSE);
			MoveCount++;
			if (MoveCount >= 9) MoveCount = 0;
		}
		else if (wParam == 'S') {
			player.MoveDown();
			MoveCheck = 2;
			InvalidateRect(hWnd, NULL, FALSE);
			MoveCount++;
			if (MoveCount >= 9) MoveCount = 0;
		}else if(wParam == 'A') {
			player.MoveLeft();
			MoveCheck = 3;
			InvalidateRect(hWnd, NULL, FALSE);
			MoveCount++;
			if (MoveCount >= 9) MoveCount = 0;
		}
		else if (wParam == 'D') {
			player.MoveRight();
			MoveCheck = 4;
			InvalidateRect(hWnd, NULL, FALSE);
			MoveCount++;
			if (MoveCount >= 9) MoveCount = 0;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_KEYUP:
		if(wParam == 'W') {
			MoveCheck = 0;
			InvalidateRect(hWnd, NULL, FALSE);
			MoveCount = 0;
		}
		else if (wParam == 'S') {
			MoveCheck = 0;
			InvalidateRect(hWnd, NULL, FALSE);
			MoveCount = 0;
		}
		else if(wParam == 'A') {
			MoveCheck = 0;
			InvalidateRect(hWnd, NULL, FALSE);
			MoveCount = 0;
		}
		else if(wParam == 'D') {
			MoveCheck = 0;
			InvalidateRect(hWnd, NULL, FALSE);
			MoveCount = 0;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_LBUTTONDOWN:
		monsters.emplace_back();
		monsters.back().SetSpot(cursor.x, cursor.y);
		monsters.back().SetRect();
		monsters.back().SetMonster(1);

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
	
