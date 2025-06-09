#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>	
#include <vector>
#include <string.h>

#include "PLAYER1.h"
#include "MONSTER.h"
#include "TEARS.h"
#include "RoundTear.h"
#include "SHOP.h"

#define WINDOW_WIDTH 4000
#define WINDOW_HEIGHT 4000
int worldX; // 마우스->월드 x좌표
int worldY; // 마우스->월드 y좌표

int MoveCheck = 0; // 0: 정지, 1: 위, 2: 아래, 3: 왼쪽, 4: 오른쪽
int MoveCount = 0; // 움직임 카운트 (애니메이션 프레임을 위한 카운트)

// 플레이어 눈물 폭발 관련 변수
int ShootCheck;
int BoomX = 0;
int BoomY = 0;
bool BoomCheck = FALSE;
int BoomCount = 0;
void DrawBoom(HDC nhDC, int x, int y);
HBITMAP TearsBoomBitMap[15];
HBITMAP TearoldBitmap = NULL; 
HDC TearhMemDC = NULL; 

// 플레이어 체력 UI 관련 변수
RECT HeartRect;
HBITMAP HeatBitmap;

int DieX, DieY; // 플레이어 사망 좌표
HBITMAP DieBitmap; // 플레이어 사망 이미지 비트맵
HDC DieBitDC; // 플레이어 사망 이미지 DC
bool isPlayerDead = false;

bool showLevelUpChoices = false;
int LevelUpChoices[3]; // 선택지 배열
char LC[3][100]; // 선택지 텍스트

//미니맵 관련 변수
HDC hMiniMapDC = NULL;
HBITMAP hMiniMapBitmap = NULL;
void DrawMiniMap(HDC hDC, const PLAYER1& player, const std::vector<MONSTER>& monsters);

// 플레이 관련 변수
bool StartPlay = FALSE;
bool click_play = FALSE;
bool click_exit = FALSE;
HDC StartBitMapDC = NULL; // 시작 화면 DC
HBITMAP StartBitMap = NULL; // 시작 화면 비트맵
RECT StartRect; // 시작화면 사진영역
HFONT hFont = CreateFont(
	150,           // Height (150px)
	0,             // Width (자동 조정)
	0, 0,          // Escapement, Orientation
	FW_BOLD,       // Weight
	FALSE, FALSE, FALSE,    // Italic, Underline, StrikeOut
	ANSI_CHARSET,
	OUT_DEFAULT_PRECIS,
	CLIP_DEFAULT_PRECIS,
	DEFAULT_QUALITY,
	DEFAULT_PITCH | FF_DONTCARE,
	_T("Arial")    // Font name
);

HFONT hFont2 = CreateFont(
	100,           // Height (150px)
	0,             // Width (자동 조정)
	0, 0,          // Escapement, Orientation
	FW_BOLD,       // Weight
	FALSE, FALSE, FALSE,    // Italic, Underline, StrikeOut
	ANSI_CHARSET,
	OUT_DEFAULT_PRECIS,
	CLIP_DEFAULT_PRECIS,
	DEFAULT_QUALITY,
	DEFAULT_PITCH | FF_DONTCARE,
	_T("Arial")    // Font name
);


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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME, 0, 0, 1000, 1000, NULL, (HMENU)NULL, hlnstance, NULL);
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

	static HDC hDC, hMem2DC, BGBitDC, HeartBitDC;
	static HBITMAP BackGroundhBitmap, hBitmap, hOldBitmap, oldBitmap, HeartOldBitmap;
	static HBITMAP CameraBitmap, WorldBitmap;

	static RECT ViewRect;

	static PLAYER1 player(60, 500, 400, 5, 1.0f, 10, 2, 0, down); // 생성자
	static RoundTear Rt(player.Tx, player.Ty); // 눈물 생성자

	static POINT cursor; // 마우스 커서 좌표
	static float DeltaTime = 16.0f / 1000.0f; // 60fps 기준 1초 재기 위한 단위;

	static std::vector<MONSTER> monsters; // 몬스터 벡터 선언
	static std::vector<TEARS> tears; // 눈물 백터 선언

	static int Mtype = 0;

	static SHOP shop;
	static bool clicked;
	static bool draw = true;

	static char LVbuf[100];
	static char LPbuf[100];

	switch (iMessage) {
	case WM_CREATE:

		// 비트맵 생성 (카메라 크기에 맞게 1000x1000)
		CameraBitmap = CreateCompatibleBitmap(GetDC(hWnd), 1000, 1000);
		SelectObject(hMem2DC, CameraBitmap);

		TEARS::LoadTearsBitMap();
		player.SetCamera();

		// 눈물 폭발 비트맵 로드
		TCHAR Tb_filePath[256];
		for (int i = 0; i < 15; i++) {
			_stprintf_s(Tb_filePath, _T("P1_graphics/Tb_%d.bmp"), i + 1); 
			TearsBoomBitMap[i] = (HBITMAP)LoadImage(NULL, Tb_filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			if (TearsBoomBitMap[i] == NULL) {
				MessageBox(NULL, _T("비트맵 로딩 실패!"), _T("오류"), MB_OK);
			}
		}
		TearhMemDC = CreateCompatibleDC(NULL);
		// 배경 이미지 로드
		TCHAR BGfilepath[256];
		_stprintf_s(BGfilepath, _T("Play_graphics/background.bmp")); 
		BackGroundhBitmap = (HBITMAP)LoadImage(NULL, BGfilepath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		BGBitDC = CreateCompatibleDC(NULL);
		if (BackGroundhBitmap == NULL) {
			MessageBox(hWnd, _T("Failed to load background image"), _T("Error"), MB_OK | MB_ICONERROR);
			return -1;
		}
		// 플레이어 사망 이미지 로드
		TCHAR DIefilepath[256];
		_stprintf_s(DIefilepath, _T("P1_graphics/DieP.bmp")); 
		DieBitmap = (HBITMAP)LoadImage(NULL, DIefilepath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (DieBitmap == NULL) {
			MessageBox(hWnd, _T("Failed to load DieP image"), _T("Error"), MB_OK | MB_ICONERROR);
			return -1;
		}
		DieBitDC = CreateCompatibleDC(NULL);
		// Heart 이미지 로드
		TCHAR Heartfilepath[256];
		_stprintf_s(Heartfilepath, _T("P1_graphics/ui_hearts.bmp")); 
		HeatBitmap = (HBITMAP)LoadImage(NULL, Heartfilepath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (HeatBitmap == NULL) {
			MessageBox(hWnd, _T("Failed to load ui_hearts image"), _T("Error"), MB_OK | MB_ICONERROR);
			return -1;
		}
		HeartBitDC = CreateCompatibleDC(NULL);
		HeartRect.left = player.Came.left + 10;
		HeartRect.right = HeartRect.left + 49;
		HeartRect.top = player.Came.top + 10;
		HeartRect.bottom = HeartRect.top + 15;
		// 시작화면 비트맵 로드
		TCHAR StartBGfilepath[256];
		_stprintf_s(StartBGfilepath, _T("Play_graphics/KvsM.bmp"));
		StartBitMap = (HBITMAP)LoadImage(NULL, StartBGfilepath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (StartBitMap == NULL) {
			MessageBox(hWnd, _T("Failed to load KvsM image"), _T("Error"), MB_OK | MB_ICONERROR);
			return -1;
		}
		StartBitMapDC = CreateCompatibleDC(NULL);
		StartRect.left = player.Came.left + 300;
		StartRect.right = StartRect.left + 400;
		StartRect.top = player.Came.top + 20;
		StartRect.bottom = StartRect.top + 400;

		ImageCreate();
		GetClientRect(hWnd, &ViewRect);

		break;
	case WM_PAINT: {
		hDC = BeginPaint(hWnd, &ps);

		if (StartPlay) {
			//더블버퍼링
			hMem2DC = CreateCompatibleDC(hDC); // hMem2DC에다가 다 그림
			hBitmap = CreateCompatibleBitmap(hDC, 4000, 4000); // 4000x4000 크기의 비트맵 생성
			hOldBitmap = (HBITMAP)SelectObject(hMem2DC, hBitmap); // hMem2DC에 hBitmap을 선택

			oldBitmap = (HBITMAP)SelectObject(BGBitDC, BackGroundhBitmap); // 배경비트맵 사용
			BitBlt(hMem2DC, 0, 0, 4000, 4000, BGBitDC, 0, 0, SRCCOPY); // 배경 그리기
			SelectObject(BGBitDC, oldBitmap); // 이전 비트맵으로 되돌리기

			// 미니맵 복사
			hMiniMapDC = CreateCompatibleDC(hDC);
			hMiniMapBitmap = CreateCompatibleBitmap(hDC, 200, 200);
			SelectObject(hMiniMapDC, hMiniMapBitmap);
			

			// 플레이어 그리기
			if (!isPlayerDead) {
				if (MoveCheck == 0) {
					player.Draw(hMem2DC);
				}
				else if (MoveCheck == 1) {
					player.UMDraw(hMem2DC, MoveCount);
				}
				else if (MoveCheck == 2) {
					player.DMDraw(hMem2DC, MoveCount);
				}
				else if (MoveCheck == 3) {
					player.LMDraw(hMem2DC, MoveCount);
				}
				else if (MoveCheck == 4) {
					player.RMDraw(hMem2DC, MoveCount);
				}
				else if (MoveCheck == 5) {
					player.LMDraw(hMem2DC, MoveCount);
				}
				else if (MoveCheck == 6) {
					player.RMDraw(hMem2DC, MoveCount);
				}
				else if (MoveCheck == 7) {
					player.LMDraw(hMem2DC, MoveCount);
				}
				else if (MoveCheck == 8) {
					player.RMDraw(hMem2DC, MoveCount);
				}
				Rt.Update(player.Tx, player.Ty, DeltaTime);
				Rt.SetRtTearRect();
				Rt.Draw(hMem2DC);
			}
			else if (isPlayerDead) {
				HBITMAP DoldBitmap = (HBITMAP)SelectObject(DieBitDC, DieBitmap);
				if (MoveCheck == 9) {
					TransparentBlt(hMem2DC, player.DieRect.left, player.DieRect.top, 29 * 2, 34 * 2, DieBitDC, 0, 0, 29, 34, RGB(255, 200, 200));
				}
				else if (MoveCheck == 10) {
					TransparentBlt(hMem2DC, player.DieRect.left, player.DieRect.top, 80, 28 * 2, DieBitDC, 30, 0, 37, 28, RGB(255, 200, 200));
				}
				SelectObject(DieBitDC, DoldBitmap);
			}

			// 몬스터와 눈물 그리기
			for (auto& monster : monsters) { // monster를 참조자로  monsters vector 전체 순회하며 루프
				monster.Draw(hMem2DC);
			}

			for (auto& tear : tears) {
				tear.Draw(hMem2DC);
			}
			if (BoomCheck) {
				DrawBoom(hMem2DC, BoomX, BoomY);
			}

			// 플레이어 체력 UI 그리기
			HeartRect.left = player.Came.left + 10;
			HeartRect.right = HeartRect.left + 45;
			HeartRect.top = player.Came.top + 10;
			HeartRect.bottom = HeartRect.top + 14;

			HeartOldBitmap = (HBITMAP)SelectObject(HeartBitDC, HeatBitmap);
			if (player.hp > 50) {
				TransparentBlt(hMem2DC, HeartRect.left, HeartRect.top, 15, 14, HeartBitDC, 0, 0, 15, 14, RGB(255, 200, 200));
				TransparentBlt(hMem2DC, HeartRect.left + 15, HeartRect.top, 15, 14, HeartBitDC, 0, 0, 15, 14, RGB(255, 200, 200));
				TransparentBlt(hMem2DC, HeartRect.left + 30, HeartRect.top, 15, 14, HeartBitDC, 0, 0, 15, 14, RGB(255, 200, 200));
			}
			else if (player.hp > 40 && player.hp <= 50) {
				TransparentBlt(hMem2DC, HeartRect.left, HeartRect.top, 15, 14, HeartBitDC, 0, 0, 15, 14, RGB(255, 200, 200));
				TransparentBlt(hMem2DC, HeartRect.left + 15, HeartRect.top, 15, 14, HeartBitDC, 0, 0, 15, 14, RGB(255, 200, 200));
				TransparentBlt(hMem2DC, HeartRect.left + 30, HeartRect.top, 15, 14, HeartBitDC, 16, 0, 15, 14, RGB(255, 200, 200));
			}
			else if (player.hp > 30 && player.hp <= 40) {
				TransparentBlt(hMem2DC, HeartRect.left, HeartRect.top, 15, 14, HeartBitDC, 0, 0, 15, 14, RGB(255, 200, 200));
				TransparentBlt(hMem2DC, HeartRect.left + 15, HeartRect.top, 15, 14, HeartBitDC, 0, 0, 15, 14, RGB(255, 200, 200));
				TransparentBlt(hMem2DC, HeartRect.left + 30, HeartRect.top, 15, 14, HeartBitDC, 32, 0, 15, 14, RGB(255, 200, 200));
			}
			else if (player.hp > 20 && player.hp <= 30) {
				TransparentBlt(hMem2DC, HeartRect.left, HeartRect.top, 15, 14, HeartBitDC, 0, 0, 15, 14, RGB(255, 200, 200));
				TransparentBlt(hMem2DC, HeartRect.left + 15, HeartRect.top, 15, 14, HeartBitDC, 16, 0, 15, 14, RGB(255, 200, 200));
				TransparentBlt(hMem2DC, HeartRect.left + 30, HeartRect.top, 15, 14, HeartBitDC, 32, 0, 15, 14, RGB(255, 200, 200));
			}
			else if (player.hp > 10 && player.hp <= 20) {
				TransparentBlt(hMem2DC, HeartRect.left, HeartRect.top, 15, 14, HeartBitDC, 0, 0, 15, 14, RGB(255, 200, 200));
				TransparentBlt(hMem2DC, HeartRect.left + 15, HeartRect.top, 15, 14, HeartBitDC, 32, 0, 15, 14, RGB(255, 200, 200));
				TransparentBlt(hMem2DC, HeartRect.left + 30, HeartRect.top, 15, 14, HeartBitDC, 32, 0, 15, 14, RGB(255, 200, 200));
			}
			else if (player.hp > 0 && player.hp <= 10) {
				TransparentBlt(hMem2DC, HeartRect.left, HeartRect.top, 15, 14, HeartBitDC, 16, 0, 15, 14, RGB(255, 200, 200));
				TransparentBlt(hMem2DC, HeartRect.left + 15, HeartRect.top, 15, 14, HeartBitDC, 32, 0, 15, 14, RGB(255, 200, 200));
				TransparentBlt(hMem2DC, HeartRect.left + 30, HeartRect.top, 15, 14, HeartBitDC, 32, 0, 15, 14, RGB(255, 200, 200));
			}
			else if (player.hp <= 0) {
				TransparentBlt(hMem2DC, HeartRect.left, HeartRect.top, 15, 14, HeartBitDC, 32, 0, 15, 14, RGB(255, 200, 200));
				TransparentBlt(hMem2DC, HeartRect.left + 15, HeartRect.top, 15, 14, HeartBitDC, 32, 0, 15, 14, RGB(255, 200, 200));
				TransparentBlt(hMem2DC, HeartRect.left + 30, HeartRect.top, 15, 14, HeartBitDC, 32, 0, 15, 14, RGB(255, 200, 200));
			}
			SelectObject(HeartBitDC, HeartOldBitmap);

			if (showLevelUpChoices) {
				TextOutA(hMem2DC, player.Came.left + 10, player.Came.top + 80, LC[0], strlen(LC[0]));
				TextOutA(hMem2DC, player.Came.left + 10, player.Came.top + 100, LC[1], strlen(LC[1]));
				TextOutA(hMem2DC, player.Came.left + 10, player.Came.top + 120, LC[2], strlen(LC[2]));
			}

			// 플레이어 레벨과 LP 표시
			sprintf_s(LVbuf, "Lv : %d", player.Level);
			sprintf_s(LPbuf, "Lp : %d", player.Lp);
			TextOutA(hMem2DC, player.Came.left + 10, player.Came.top + 40, LVbuf, strlen(LVbuf));
			TextOutA(hMem2DC, player.Came.left + 10, player.Came.top + 60, LPbuf, strlen(LPbuf));

			DrawMiniMap(hMem2DC, player, monsters); // 미니맵 그리기

			//상점 그리기
			shop.DrawShop(hMem2DC, player.Came.left, player.Came.bottom - 210);
			if (clicked) {
				if (draw) {
					IMGparabite[3].Draw(hMem2DC, player.Came.left + cursor.x, player.Came.top + cursor.y, 32, 32, 0, 0, 32, 32);
					draw = !draw;
				}
				else {
					draw = !draw;
				}
			}

			BitBlt(hDC, 0, 0, 1000, 1000, hMem2DC, player.Came.left, player.Came.top, SRCCOPY); // 카메라 영역만 복사

			SelectObject(hMem2DC, hOldBitmap);
			DeleteObject(hBitmap);
			DeleteObject(hOldBitmap);
			DeleteObject(hMiniMapBitmap);
			DeleteDC(hMem2DC);
			DeleteDC(hMiniMapDC);
		}
		else {
			SelectObject(StartBitMapDC, StartBitMap);
			StretchBlt(hDC, StartRect.left, StartRect.top, StartRect.right - StartRect.left, StartRect.bottom - StartRect.top, StartBitMapDC, 0, 0, 400, 400, SRCCOPY); // 시작 화면 그리기
			HFONT hOldFont1 = (HFONT)SelectObject(hDC, hFont);
			SetTextColor(hDC, RGB(0, 0, 0)); // 흰 글자
			SetBkMode(hDC, TRANSPARENT);           // 배경 투명

			// 텍스트 출력
			TextOut(hDC, StartRect.left - 250, StartRect.bottom, _T("Key Vs Mouse"), _tcslen(_T("Key Vs Mouse")));
			
			HFONT hOldFont2 = (HFONT)SelectObject(hDC, hFont2);
			Rectangle(hDC, StartRect.left, StartRect.bottom + 200, StartRect.right, StartRect.bottom + 300);
			TextOut(hDC, StartRect.left + 35, StartRect.bottom + 200, _T("게임 시작"), _tcslen(_T("게임 시작")));

			Rectangle(hDC, StartRect.left, StartRect.bottom + 350, StartRect.right, StartRect.bottom + 450);
			TextOut(hDC, StartRect.left + 35, StartRect.bottom + 350, _T("게임 종료"), _tcslen(_T("게임 종료")));

			SelectObject(hDC, hOldFont1); // 폰트 원복
			SelectObject(hDC, hOldFont2); // 폰트 원복
		}

		

		EndPaint(hWnd, &ps);
		break;
	}
	case WM_CHAR:
		break;

	case WM_TIMER: {
		player.SetHeadRect();
		player.SetBodyRect();
		player.SetTarget();

		ShootCheck = player.ShootTime(DeltaTime); // 플레이어 눈물발사 시간 체크, 기본 3초마다 쏨

		if (!isPlayerDead) {
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
						if (monster->hp <= 0) {
							monster->killedByTear = TRUE; // 눈물에 의해 몬스터 죽음
						}
						break;
					}
					else {
						monster++;
					}
				}

				if (hit || tear->IsOutOfRange()) {
					BoomX = tear->x;
					BoomY = tear->y;
					BoomCheck = TRUE;
					tear = tears.erase(tear);
					hit = FALSE;
				}
				else {
					tear++;
				}
			}

			// 눈물 터짐
			if (BoomCheck) {
				BoomCount++;
				if (BoomCount >= 14) {
					BoomCheck = FALSE;
					BoomCount = 0;
				}
			}
		}

		POINT point = { player.Tx, player.Ty };

		for (auto monster = monsters.begin(); monster != monsters.end();) {
			if (monster->Update(DeltaTime)) {
				if (monster->killedByTear) {
					player.AddLp(10); // 눈물로 죽인 경우만 LP 추가
				}
				monster = monsters.erase(monster);
			}
			else {
				player.hp -= monster->MoveToPlayer(point, player.HeadRect, player.BodyRect, DeltaTime);
				monster++;
			}
		}

		if (!isPlayerDead) {
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
		}

		// 플레이어 주금
		if (player.hp <= 0) {
			MoveCheck = player.SetDieRect(DeltaTime);
			isPlayerDead = TRUE;
			//MessageBox(hWnd, _T("Game Over!"), _T("Game Over"), MB_OK | MB_ICONERROR);
			//PostQuitMessage(0); // 게임 종료
		}

		// 레벨업 후 선택지
		if (player.LevelUp) {
			showLevelUpChoices = true;

			for (int i = 0; i < 3; i++) {
				LevelUpChoices[i] = rand() % 3 + 1;

				if (LevelUpChoices[i] == 1) {
					strcpy_s(LC[i], "이동속도 증가");
				}
				else if (LevelUpChoices[i] == 2) {
					strcpy_s(LC[i], "공격력 증가");
				}
				else if (LevelUpChoices[i] == 3) {
					if (player.Aspeed == 0.1f) {
						strcpy_s(LC[i], "이미 최대 공격속도 입니다");
					}
					else {
						strcpy_s(LC[i], "공격속도 증가");
					}
				}
			}
			player.LevelUp = false;
		}

		InvalidateRect(hWnd, NULL, FALSE);
		break;
	}
	case WM_KEYDOWN:
		if (showLevelUpChoices) {
			switch (wParam) {
			case '1':
				if (LevelUpChoices[0] == 1) { // 1 = 이속증가
					player.Mspeed += 2;
				}
				else if (LevelUpChoices[0] == 2) { // 2 = 공격력 증가
					player.Damage += 5;
				}
				else if (LevelUpChoices[0] == 3) { // 3 = 공속 증가
					if (player.Aspeed > 0.2f) {
						player.Aspeed -= 0.1f;
					}
				}
				showLevelUpChoices = false;
				break;
			case '2':
				if (LevelUpChoices[1] == 1) { // 1 = 이속증가
					player.Mspeed += 2;
				}
				else if (LevelUpChoices[1] == 2) { // 2 = 공격력 증가
					player.Damage += 5;
				}
				else if (LevelUpChoices[1] == 3) { // 3 = 공속 증가
					if (player.Aspeed > 0.2f) {
						player.Aspeed -= 0.1f;
					}
				}
				showLevelUpChoices = false;
				break;
			case '3':
				if (LevelUpChoices[2] == 1) { // 1 = 이속증가
					player.Mspeed += 2;
				}
				else if (LevelUpChoices[2] == 2) { // 2 = 공격력 증가
					player.Damage += 5;
				}
				else if (LevelUpChoices[2] == 3) { // 3 = 공속 증가
					if (player.Aspeed > 0.2f) {
						player.Aspeed -= 0.1f;
					}
				}
				showLevelUpChoices = false;
				break;
			}
			break;
		}
		break;


		break;
	case WM_KEYUP:

		break;
	case WM_LBUTTONDOWN: {
		worldX = cursor.x + player.Came.left;
		worldY = cursor.y + player.Came.top;

		if (StartPlay) {
			POINT Wcursor = { worldX, worldY };

			RECT rect;
			rect.left = player.Came.left + 100;
			rect.top = player.Came.top + 800;
			rect.right = player.Came.left + 300;
			rect.bottom = player.Came.bottom;

			if (PtInRect(&rect, Wcursor)) {
				clicked = true;
				Mtype = 2;
			}
		}
		else {
			if (worldX >= StartRect.left && worldX <= StartRect.right && worldY >= StartRect.bottom + 200 && worldY <= StartRect.bottom + 300) {
				StartPlay = true; // 게임 시작
				SetTimer(hWnd, 1, 16, NULL); // 60프레임 타이머 생성
			}
			else if (worldX >= StartRect.left && worldX <= StartRect.right && worldY >= StartRect.bottom + 350 && worldY <= StartRect.bottom + 450) {
				exit(1); // 게임 종료
			}
		}
	
		break;
	}
	case WM_LBUTTONUP: {
		worldX = cursor.x + player.Came.left;
		worldY = cursor.y + player.Came.top;
		if (StartPlay) {
			if (clicked) {
				monsters.emplace_back();
				monsters.back().SetSpot(worldX, worldY);
				monsters.back().SetRect();
				monsters.back().SetMonster(Mtype);
				clicked = false;
			}
		}
	}
	case WM_MOUSEMOVE:
		cursor.x = LOWORD(lParam);
		cursor.y = HIWORD(lParam);

		worldX = cursor.x + player.Came.left;
		worldY = cursor.y + player.Came.top;
		break;
	case WM_DESTROY:
		DeleteObject(hBitmap);
		DeleteObject(BackGroundhBitmap);
		DeleteObject(HeatBitmap);
		DeleteObject(DieBitmap);
		for (int i = 0; i < 15; i++) {
			DeleteObject(TearsBoomBitMap[i]);
		}
		DeleteDC(hMem2DC);
		KillTimer(hWnd, 1); // 타이머 제거
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void DrawBoom(HDC nhDC, int x, int y) { // 눈물 폭발 그리기 함수

	TearoldBitmap = (HBITMAP)SelectObject(TearhMemDC, TearsBoomBitMap[BoomCount]); // 0번 비트맵 사용
	TransparentBlt(nhDC, x - 8, y - 8, 64, 64, TearhMemDC, 0, 0, 64, 64, RGB(255, 200, 200)); // 눈물 그리기
	SelectObject(TearhMemDC, TearoldBitmap); // 이전 비트맵으로 되돌리기

};

void DrawMiniMap(HDC hDC, const PLAYER1& player, const std::vector<MONSTER>& monsters) {
	// 1. 전체 배경 클리어 (배경 브러시 생성 및 정리)
	HBRUSH bgBrush = CreateSolidBrush(RGB(70, 70, 70)); // 연회색 배경
	HBRUSH oldBrush = (HBRUSH)SelectObject(hMiniMapDC, bgBrush);

	RECT miniRect = { 0, 0, 200, 200 };
	FillRect(hMiniMapDC, &miniRect, bgBrush);

	SelectObject(hMiniMapDC, oldBrush);
	DeleteObject(bgBrush); // 안전하게 제거

	// 2. 월드 크기 대비 비율 계산
	float scaleX = 200.0f / WINDOW_WIDTH;
	float scaleY = 200.0f / WINDOW_HEIGHT;

	// 3. 몬스터 그리기 (빨간 점)
	HBRUSH monsterBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hMiniMapDC, monsterBrush);

	for (const auto& m : monsters) {
		int mx = static_cast<int>(m.x * scaleX);
		int my = static_cast<int>(m.y * scaleY);
		Ellipse(hMiniMapDC, mx - 2, my - 2, mx + 2, my + 2); // 4x4 점
	}

	SelectObject(hMiniMapDC, oldBrush);
	DeleteObject(monsterBrush);

	// 4. 플레이어 그리기 (파란 점)
	HBRUSH playerBrush = CreateSolidBrush(RGB(255, 200, 200));
	oldBrush = (HBRUSH)SelectObject(hMiniMapDC, playerBrush);

	int px = static_cast<int>(player.Tx * scaleX);
	int py = static_cast<int>(player.Ty * scaleY);
	Ellipse(hMiniMapDC, px - 3, py - 3, px + 3, py + 3); // 6x6 점

	SelectObject(hMiniMapDC, oldBrush);
	DeleteObject(playerBrush);

	// 5. 출력 위치 계산 (화면 오른쪽 아래)
	int miniMapX = player.Came.right - 210;
	int miniMapY = player.Came.bottom - 210;

	BitBlt(hDC, miniMapX, miniMapY, 200, 200, hMiniMapDC, 0, 0, SRCCOPY);
}