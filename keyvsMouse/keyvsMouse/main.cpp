#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>	
#include <vector>

#include "PLAYER1.h"
#include "MONSTER.h"
#include "TEARS.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

int MoveCheck = 0; // 0: ����, 1: ��, 2: �Ʒ�, 3: ����, 4: ������
int MoveCount = 0; // ������ ī��Ʈ (�ִϸ��̼� �������� ���� ī��Ʈ)
float dx; // �÷��̾�-���� �Ÿ� x
float dy; // �÷��̾�-���� �Ÿ� y
float Length; // �÷��̾�-���� �Ÿ�
float MinLength = 10000;// �÷��̾�-���� �ּ� �Ÿ�
float stocktime = 1.0f;
float closestX = 0, closestY = 0;
float minDist = FLT_MAX;

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
	RegisterClassExW(&WndClass); // RegisterClassExW -> �����ڵ� ����

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
	HDC hDC, hMem1DC, hMem2DC, hMem3DC;
	HBITMAP OldBit[3];
	static HBITMAP BackGroundhBitmap;
	HBITMAP hBitmap, hOldBitmap;

	static RECT ViewRect;
	static HPEN hPen, hOldPen;
	static HBRUSH hBrush, hOldBrush;
	static PLAYER1 player(10, 500, 500, 5, 3.0f, 10, 2, 0, down); // ������

	static POINT cursor; // ���콺 Ŀ�� ��ǥ
	static float DeltaTime = 16.0f / 1000.0f; // 60fps ���� 1�� ��� ���� ����;

	static std::vector<MONSTER> monsters; // ���� ���� ����
	static std::vector<TEARS> tears; // ���� ���� ����

	static int Mtype = 0;

	switch (iMessage) {
	case WM_CREATE:
		ImageCreate();
		GetClientRect(hWnd, &ViewRect);


		player.SetCamera();

		TCHAR BGfilepath[256];
		_stprintf_s(BGfilepath, _T("Play_graphics/background.bmp")); // ����: "resources/player0.bmp", "resources/player1.bmp" ��
		BackGroundhBitmap = (HBITMAP)LoadImage(NULL, BGfilepath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (BackGroundhBitmap == NULL) {
			MessageBox(hWnd, _T("Failed to load background image"), _T("Error"), MB_OK | MB_ICONERROR);
			return -1;
		}

		SetTimer(hWnd, 1, 16, NULL); // 60������ Ÿ�̸� ����
		break;
	case WM_PAINT: {
		hDC = BeginPaint(hWnd, &ps);
		
		// Mem2DC �� ���� ������۸�
		hMem2DC = CreateCompatibleDC(hDC); // hMem2DC���ٰ� �� �׸�
		hMem1DC = CreateCompatibleDC(hMem2DC); // hMem1DC�� �÷��̾� ���ۿ�, 1�̶� 2 ��������ִ� ��
		hMem3DC = CreateCompatibleDC(hMem2DC); // hMem3DC�� ������, 2�� 3 ��������ִ� ��
		hBitmap = CreateCompatibleBitmap(hDC, WINDOW_WIDTH, WINDOW_HEIGHT);
		hOldBitmap = (HBITMAP)SelectObject(hMem2DC, hBitmap);
		FillRect(hMem2DC, &ViewRect, (HBRUSH)GetStockObject(WHITE_BRUSH));
		
		
		if (MoveCheck == 0) {
			player.Draw(hMem2DC, hMem1DC);
		}
		else if (MoveCheck == 1) {
			player.UMDraw(hMem2DC, hMem1DC, MoveCount);
		}
		else if (MoveCheck == 2) {
			player.DMDraw(hMem2DC, hMem1DC, MoveCount);
		}
		else if (MoveCheck == 3) {
			player.LMDraw(hMem2DC, hMem1DC, MoveCount);
		}
		else if (MoveCheck == 4) {
			player.RMDraw(hMem2DC, hMem1DC, MoveCount);
		}
		else if (MoveCheck == 5) {
			player.LMDraw(hMem2DC, hMem1DC, MoveCount);
		}
		else if (MoveCheck == 6) {
			player.RMDraw(hMem2DC, hMem1DC, MoveCount);
		}
		else if (MoveCheck == 7) {
			player.LMDraw(hMem2DC, hMem1DC, MoveCount);
		}
		else if( MoveCheck == 8) {
			player.RMDraw(hMem2DC, hMem1DC, MoveCount);
		}

		for (auto& monster : monsters) { // monster�� �����ڷ�  monsters vector ��ü ��ȸ�ϸ� ����
			monster.Draw(hMem2DC);
		}

		for (auto& tear : tears) {
			tear.Draw(hMem2DC, hMem3DC);
		}
		
		BitBlt(hDC, ViewRect.left, ViewRect.top, ViewRect.right, ViewRect.bottom, hMem2DC, 0, 0, SRCCOPY);

		SelectObject(hMem2DC, hOldBitmap);
		DeleteObject(hBitmap);
		DeleteDC(hMem2DC);
		DeleteDC(hMem1DC);

		EndPaint(hWnd, &ps);
		break;
	}
	case WM_CHAR:
		break;

	case WM_TIMER: {
		player.SetHeadRect();
		player.SetBodyRect();
		player.SetTarget();
		int ShootCheck = player.ShootTime(DeltaTime); // �÷��̾� �����߻� �ð� üũ, �⺻ 3�ʸ��� ��

		if (ShootCheck == 1) {
			if (monsters.empty()) break;
			TEARS tear(player.Tx, player.Ty);

			minDist = FLT_MAX;
			bool foundTarget = false;
			for (auto& monster : monsters) {
				float dx = monster.GetX() - player.Tx;
				float dy = monster.GetY() - player.Ty;
				float dist = sqrt(dx * dx + dy * dy);
				if (dist < minDist) {
					minDist = dist;
					closestX = monster.GetX();
					closestY = monster.GetY();
					foundTarget = true;
				}
			}

			if (foundTarget) {
				tear.Shoot(closestX, closestY);
				tears.push_back(tear);
			}
		}

		// ���� �̵� �� ����
		for (auto tear = tears.begin(); tear != tears.end(); ) {
			tear->Update(DeltaTime);
			if (tear->IsOutOfRange()) {
				tear = tears.erase(tear);
			}
			else {
				tear++;
			}
		}

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

		SHORT w = GetAsyncKeyState('W');
		SHORT s = GetAsyncKeyState('S');
		SHORT a = GetAsyncKeyState('A');
		SHORT d = GetAsyncKeyState('D');

		bool W = w & 0x8000;
		bool S = s & 0x8000;
		bool A = a & 0x8000;
		bool D = d & 0x8000;

		// ���� �켱 ����: �밢�� > ���� ����
		if (W && A) {
			player.MoveUpLeft();     // �»�
			MoveCheck = 5;
		}
		else if (W && D) {
			player.MoveUpRight();    // ���
			MoveCheck = 6;
		}
		else if (S && A) {
			player.MoveDownLeft();   // ����
			MoveCheck = 7;
		}
		else if (S && D) {
			player.MoveDownRight();  // ����
			MoveCheck = 8;
		}
		else if (W) {
			player.MoveUp();
			MoveCheck = 1;
		}
		else if (S) {
			player.MoveDown();
			MoveCheck = 2;
		}
		else if (A) {
			player.MoveLeft();
			MoveCheck = 3;
		}
		else if (D) {
			player.MoveRight();
			MoveCheck = 4;
		}
		else {
			MoveCheck = 0; // ����
		}

		// �ִϸ��̼� ������ ī��Ʈ ����
		if (MoveCheck != 0) {
			MoveCount++;
			if (MoveCount >= 9) MoveCount = 0;
		}


		InvalidateRect(hWnd, NULL, FALSE);
		break;
	}
	case WM_KEYDOWN:

		
		break;
	case WM_KEYUP:

		
		break;

	case WM_RBUTTONDOWN:
		Mtype++;
		break;

	case WM_LBUTTONDOWN:
		monsters.emplace_back();
		monsters.back().SetSpot(cursor.x, cursor.y);
		monsters.back().SetRect();
		monsters.back().SetMonster((Mtype % 2) + 1);

		break;
	case WM_MOUSEMOVE:

		cursor.x = LOWORD(lParam);
		cursor.y = HIWORD(lParam);

		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1); // Ÿ�̸� ����
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}