#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>	
#include <vector>

#include "PLAYER1.h"
#include "MONSTER.h"
#include "TEARS.h"
#include "RoundTear.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

int MoveCheck = 0; // 0: 정지, 1: 위, 2: 아래, 3: 왼쪽, 4: 오른쪽
int MoveCount = 0; // 움직임 카운트 (애니메이션 프레임을 위한 카운트)

float dx; // 플레이어-몬스터 거리 x
float dy; // 플레이어-몬스터 거리 y
float Length; // 플레이어-몬스터 거리
float MinLength = 10000;// 플레이어-몬스터 최소 거리
float stocktime = 1.0f;
float closestX = 0, closestY = 0;
float minDist = FLT_MAX;
int BoomX = 0;
int BoomY = 0;
bool BoomCheck = FALSE;
int BoomCount = 0;
void DrawBoom(HDC nhDC, HDC nhMemDC, int x, int y);
HBITMAP TearsBoomBitMap[15];

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
	HDC hDC, hMem1DC, hMem2DC, hMem3DC;
	HBITMAP OldBit[3];
	static HBITMAP BackGroundhBitmap, HeatBitmap;
	HBITMAP hBitmap, hOldBitmap;

	static RECT ViewRect;
	static HPEN hPen, hOldPen;
	static HBRUSH hBrush, hOldBrush;
	static PLAYER1 player(60, 500, 500, 5, 1.0f, 10, 2, 0, down); // 생성자
	static RoundTear Rt(player.Tx,player.Ty); // 눈물 생성자

	static POINT cursor; // 마우스 커서 좌표
	static float DeltaTime = 16.0f / 1000.0f; // 60fps 기준 1초 재기 위한 단위;

	static std::vector<MONSTER> monsters; // 몬스터 벡터 선언
	static std::vector<TEARS> tears; // 눈물 백터 선언

	static int Mtype = 0;

	switch (iMessage) {
	case WM_CREATE:

		TCHAR Tb_filePath[256];
		for (int i = 0; i < 15; i++) {
			_stprintf_s(Tb_filePath, _T("P1_graphics/Tb_%d.bmp"), i + 1); // 예시: "resources/player0.bmp", "resources/player1.bmp" 등
			TearsBoomBitMap[i] = (HBITMAP)LoadImage(NULL, Tb_filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			if (TearsBoomBitMap[i] == NULL) {
				MessageBox(NULL, _T("비트맵 로딩 실패!"), _T("오류"), MB_OK);
			}
		}

		ImageCreate();
		GetClientRect(hWnd, &ViewRect);

		player.SetCamera();

		TCHAR BGfilepath[256];
		_stprintf_s(BGfilepath, _T("Play_graphics/background.bmp")); // 예시: "resources/player0.bmp", "resources/player1.bmp" 등
		BackGroundhBitmap = (HBITMAP)LoadImage(NULL, BGfilepath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (BackGroundhBitmap == NULL) {
			MessageBox(hWnd, _T("Failed to load background image"), _T("Error"), MB_OK | MB_ICONERROR);
			return -1;
		}

		TCHAR Heartfilepath[256];
		_stprintf_s(Heartfilepath, _T("P1_graphics/ui_hearts.bmp")); // 예시: "resources/player0.bmp", "resources/player1.bmp" 등
		HeatBitmap = (HBITMAP)LoadImage(NULL, Heartfilepath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (HeatBitmap == NULL) {
			MessageBox(hWnd, _T("Failed to load ui_hearts image"), _T("Error"), MB_OK | MB_ICONERROR);
			return -1;
		}


		SetTimer(hWnd, 1, 16, NULL); // 60프레임 타이머 생성
		break;
	case WM_PAINT: {
		hDC = BeginPaint(hWnd, &ps);
		// Mem2DC 에 몬스터 더블버퍼링
		hMem2DC = CreateCompatibleDC(hDC); // hMem2DC에다가 다 그림
		hMem1DC = CreateCompatibleDC(hMem2DC); // hMem1DC는 플레이어 버퍼용, 1이랑 2 연결시켜주는 줄
		hBitmap = CreateCompatibleBitmap(hDC, 4000, 4000); // 4000x4000 크기의 비트맵 생성
		hOldBitmap = (HBITMAP)SelectObject(hMem2DC, hBitmap);
		//FillRect(hMem2DC, &ViewRect, (HBRUSH)GetStockObject(WHITE_BRUSH));
		
		HBITMAP oldBitmap = (HBITMAP)SelectObject(hMem1DC, BackGroundhBitmap); // 배경비트맵 사용
		BitBlt(hMem2DC, 0, 0, 4000, 4000, hMem1DC, 0, 0, SRCCOPY); // 배경 그리기
		SelectObject(hMem1DC, oldBitmap); // 이전 비트맵으로 되돌리기

		
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
		

		Rt.Update(player.Tx, player.Ty, DeltaTime); 
		Rt.SetRtTearRect();
		Rt.Draw(hMem2DC, hMem1DC); // Rt 눈물 그리기


		for (auto& monster : monsters) { // monster를 참조자로  monsters vector 전체 순회하며 루프
			monster.Draw(hMem2DC);
		}

		for (auto& tear : tears) {
			tear.Draw(hMem2DC, hMem1DC);
		}

		if (BoomCheck) {
			DrawBoom(hMem2DC, hMem1DC, BoomX, BoomY);
			BoomCheck = FALSE;
		}
		
		// 플레이어 체력 UI 그리기
		if (player.hp > 50) {
			//TransparentBlt(hMem2DC,)
		}else if (player.hp > 40 && player.hp < 50) {

		}
		else if (player.hp > 30 && player.hp < 40) {
		
		}
		else if (player.hp > 20 && player.hp < 30) {
		
		}
		else if (player.hp > 10 && player.hp < 20) {
		
		}
		else if (player.hp > 0 && player.hp < 10) {
		
		}else if(player.hp <= 0) {
		
		}
		
		BitBlt(hDC, 0, 0, 1000, 1000, hMem2DC, player.Came.left, player.Came.top, SRCCOPY); // 카메라 영역만 복사
		


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
		int ShootCheck = player.ShootTime(DeltaTime); // 플레이어 눈물발사 시간 체크, 기본 3초마다 쏨

		if (ShootCheck == 1) {
			TEARS tear(player.Tx, player.Ty);
			tear.Shoot(Rt.x, Rt.y);
			tears.push_back(tear);
		
		}

		
		// 눈물 이동 및 제거
		for (auto tear = tears.begin(); tear != tears.end(); ) {
			tear->Update(DeltaTime);
			tear->SetTearRect();
			bool hit = false;
			
			for (auto monster = monsters.begin(); monster != monsters.end(); ) {
				RECT ResultRect;
				if (IntersectRect(&ResultRect, &tear->TearRect, &monster->rect)) {
					hit = TRUE;
					monster->hp -= player.Damage;
					break;
				}
				else {
					monster++;
				}
			}

			if (hit||tear->IsOutOfRange()) {
				BoomX = tear->x;
				BoomY = tear->y;
				BoomCheck = TRUE;
				tear = tears.erase(tear);
				hit = FALSE;
			}else {
				tear++;
			}
		}

		/*if (BoomCheck) {
			BoomCount++;
			if (BoomCount >= 16) {
				BoomCheck = FALSE;
				BoomCount = 0;
			}
			break;
		}*/

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

		// 방향 우선 순위: 대각선 > 단일 방향
		if (W && A) {
			player.MoveUpLeft();     // 좌상
			MoveCheck = 5;
		}
		else if (W && D) {
			player.MoveUpRight();    // 우상
			MoveCheck = 6;
		}
		else if (S && A) {
			player.MoveDownLeft();   // 좌하
			MoveCheck = 7;
		}
		else if (S && D) {
			player.MoveDownRight();  // 우하
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
			MoveCheck = 0; // 멈춤
		}

		SHORT h = GetAsyncKeyState('H');
		SHORT j = GetAsyncKeyState('J');

		bool H = h & 0x8000;
		bool J = j & 0x8000;

		// 회전 방향 설정
		if (H) {
			Rt.rotationDir = -1; // 반시계 방향
		}
		else if (J) {
			Rt.rotationDir = 1; // 시계 방향
		}
		else {
			Rt.rotationDir = 0; // 멈춤
		}

		// 애니메이션 프레임 카운트 증가
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
		monsters.back().SetMonster((Mtype % 3) + 1);

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

void DrawBoom(HDC nhDC, HDC nhMemDC, int x, int y) {
	
	HBITMAP oldBitmap = (HBITMAP)SelectObject(nhMemDC, TearsBoomBitMap[BoomCount]); // 0번 비트맵 사용
	TransparentBlt(nhDC, x-8, y-8, 64, 64, nhMemDC, 0, 0, 64, 64, RGB(255, 200, 200)); // 눈물 그리기
	SelectObject(nhMemDC, oldBitmap); // 이전 비트맵으로 되돌리기

};

