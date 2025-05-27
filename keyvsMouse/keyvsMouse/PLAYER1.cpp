#include "PLAYER1.h"
#include <cstdio> 
#include <tchar.h>

PLAYER1::PLAYER1(int nhp, int nx, int ny, int nMspeed, int nAspeed, int nrange, int nsize, int nAct, int nview) {
	hp = nhp;
	x = nx;
	y = ny;
	Mspeed = nMspeed;
	Aspeed = nAspeed;
	range = nrange;
	size = nsize;
	Act = nAct;
	view = nview;


	for (int i = 0; i < 6; i++) {
		// 각 이미지 파일 경로를 넣어야 합니다
		TCHAR filePath[256];
		_stprintf_s(filePath, _T("P1_graphics/P1_%d.bmp"), (i + 1)); // 예시: "resources/player0.bmp", "resources/player1.bmp" 등
		P1BitMap[i] = (HBITMAP)LoadImage(NULL, filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (P1BitMap[i] == NULL) {
			MessageBox(NULL, _T("비트맵 로딩 실패!"), _T("오류"), MB_OK);
		}
	}



};// 생성자

PLAYER1::~PLAYER1() {
	for (int i = 0; i < 6; i++) {
		if (P1BitMap[i]) {
			DeleteObject(P1BitMap[i]);  // GDI 리소스 해제
			P1BitMap[i] = nullptr;      // 포인터 무효화 (안전)
		}
	}
}; // 소멸자



// 값 변경 함수
void PLAYER1::SetSpot(int nx, int ny) {
	x = nx;
	y = ny;
}; // 좌표 설정

void PLAYER1::SetMspeed(int nMspeed) {
	Mspeed = nMspeed;

}; // 이동속도 설정

void PLAYER1::SetAspeed(int nAspeed) {
	Aspeed = nAspeed;

}; // 공격속도 설정
void PLAYER1::SetRange(int nrange) {
	range = nrange;

}; // 공격 사거리 설정

void PLAYER1::SetSize(int nsize) {
	size = nsize;

}; // 플레이어 크기 설정

void PLAYER1::SetAct(int nAct) {
	Act = nAct;

}; // 액티브 아이템 시드값 설정

void PLAYER1::SetPct(int nPct) {
	for (int i = 0;i < 80;i++) {
		if (Pct[i] == -1) {
			Pct[i] = nPct;
			break;
		}
	}

}; // 패시브 아이템 시드값 배열 설정


void PLAYER1::SetView(int nview) {
	view = nview;

	if (view == left) {

	}
	else if (view == right) {

	}
	else if (view == up) {

	}
	else if (view == down) {

	}

}; // 플레이어 시선 설정

void PLAYER1::SetHeadRect() {

	HeadRect.left = x;
	HeadRect.top = y;
	HeadRect.right = x + (31 * size);
	HeadRect.bottom = y + (26 * size);

}; // 플레이어 머리 그리기용 좌표 // 30X20

void PLAYER1::SetBodyRect() {

	BodyRect.left = HeadRect.left + (5 * size);
	BodyRect.top = HeadRect.top + (21 * size);
	BodyRect.right = HeadRect.right - (5 * size);
	BodyRect.bottom = HeadRect.bottom + (9 * size);

}; // 플레이어 몸통 그리기용 좌표 // 30X10

void PLAYER1::SetCamera() {
	Came.left = x - 500;
	Came.right = x + 500;
	Came.top = y - 500;
	Came.bottom = y + 500;
}; // 카메라 업데이트

void SetBitMap(HBITMAP nhBitmap, int nindex) {
	


}// 플레이어 비트맵 설정


// 이동함수
void PLAYER1::MoveLeft() {
	if (HeadRect.left - Mspeed >= 0) {
		x -= Mspeed;
		
		PLAYER1::SetCamera();

	}

}; // 좌로 이동 함수

void PLAYER1::MoveRight() {
	if (HeadRect.right + Mspeed <= 1000) {
		x += Mspeed;
	}

}; // 우로 이동 함수

void PLAYER1::MoveUp() {
	if (HeadRect.top - Mspeed >= 0) {
		y -= Mspeed;
	}

}; // 위로 이동 함수

void PLAYER1::MoveDown() {
	if (BodyRect.bottom + Mspeed <= 1000) {
		y += Mspeed;
		SetHeadRect();
		SetBodyRect();
		SetCamera();
	}

}; // 아래로 이동 함수

// 부가요소 함수
void PLAYER1::Update(float deltaTime) {

}; // 위치 업데이트

void PLAYER1::Draw(HDC nhDC, HDC nMemDC) { // 출력 dc, 메모리 dc 받음
	SetHeadRect();
	SetBodyRect();
	HBITMAP oldBitmap = (HBITMAP)SelectObject(nMemDC, P1BitMap[0]);

	//몸통 메모리 -> 출력디시로
	TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 5, 44, 21, 14, RGB(255, 200, 200));
	

	//머리 메모리 -> 출력디시로
	TransparentBlt(nhDC, HeadRect.left, HeadRect.top, (HeadRect.right - HeadRect.left), (HeadRect.bottom - HeadRect.top), nMemDC, 0, 0, 31, 26, RGB(255, 200, 200));

}; // 그리기

void PLAYER1::DMDraw(HDC nhDC, HDC nMemDC, int nCount) {
	SetHeadRect();
	SetBodyRect();
	HBITMAP oldBitmap = (HBITMAP)SelectObject(nMemDC, P1BitMap[0]); // 아래로 움직임 비트맵 선택

	
	if (nCount == 0) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 197, 12, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}else if(nCount == 1) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 229, 12, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}else if(nCount == 2) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 5, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}else if(nCount == 3) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 37, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}else if(nCount == 4) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 70, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}else if(nCount == 5) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 101, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}else if(nCount == 6) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 133, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}else if(nCount == 7) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 165, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}else if(nCount == 8) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 197, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}else if (nCount == 9) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 228, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	TransparentBlt(nhDC, HeadRect.left, HeadRect.top, (HeadRect.right - HeadRect.left), (HeadRect.bottom - HeadRect.top), nMemDC, 0, 0, 31, 26, RGB(255, 200, 200)); // 머리 그리기

	SelectObject(nMemDC, oldBitmap); // 이전 비트맵으로 되돌리기

}; // 아래로 움직임 그리기

void PLAYER1::UMDraw(HDC nhDC, HDC nMemDC, int nCount) {
	SetHeadRect();
	SetBodyRect();
	HBITMAP oldBitmap = (HBITMAP)SelectObject(nMemDC, P1BitMap[0]); // 아래로 움직임 비트맵 선택


	if (nCount == 9) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 197, 12, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 8) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 229, 12, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 7) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 5, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 6) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 37, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 5) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 70, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 4) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 101, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 3) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 133, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 2) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 165, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 1) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 197, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 0) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 228, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	TransparentBlt(nhDC, HeadRect.left, HeadRect.top, (HeadRect.right - HeadRect.left), (HeadRect.bottom - HeadRect.top), nMemDC, 128, 0, 31, 26, RGB(255, 200, 200)); // 머리 그리기

	SelectObject(nMemDC, oldBitmap); // 이전 비트맵으로 되돌리기

}; // 위로 움직임 그리기

void PLAYER1::RMDraw(HDC nhDC, HDC nMemDC, int nCount) {
	SetHeadRect();
	SetBodyRect();
	HBITMAP oldBitmap = (HBITMAP)SelectObject(nMemDC, P1BitMap[0]); // 아래로 움직임 비트맵 선택

	if (nCount == 0) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 5, 76, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 1) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 37, 76, 21, 14, RGB(255, 200, 200)); // 몸통 그리기	
	}
	else if (nCount == 2) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 70, 76, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 3) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 101, 76, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 4) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 133, 76, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 5) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 165, 76, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 6) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 197, 76, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 7) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 228, 76, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 8) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 5, 107, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 9) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 37, 107, 21, 14, RGB(255, 200, 200)); // 몸통 그리기	
	}

	TransparentBlt(nhDC, HeadRect.left, HeadRect.top, (HeadRect.right - HeadRect.left), (HeadRect.bottom - HeadRect.top), nMemDC, 64, 0, 31, 26, RGB(255, 200, 200)); // 머리 그리기

	SelectObject(nMemDC, oldBitmap); // 이전 비트맵으로 되돌리기

}; // 오른쪽으로 움직임 그리기

void PLAYER1::LMDraw(HDC nhDC, HDC nMemDC, int nCount) {
	SetHeadRect();
	SetBodyRect();
	HBITMAP oldBitmap = (HBITMAP)SelectObject(nMemDC, P1BitMap[0]); // 아래로 움직임 비트맵 선택

	if (nCount == 0) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 70, 107, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 1) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 101, 107, 21, 14, RGB(255, 200, 200)); // 몸통 그리기	
	}
	else if (nCount == 2) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 133,107, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 3) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 165, 107, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 4) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 197, 107, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 5) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 228, 107, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 6) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 5, 127, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 7) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 37, 127, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 8) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 70, 127, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 9) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 101, 127, 21, 14, RGB(255, 200, 200)); // 몸통 그리기	
	}

	TransparentBlt(nhDC, HeadRect.left, HeadRect.top, (HeadRect.right - HeadRect.left), (HeadRect.bottom - HeadRect.top), nMemDC, 64, 0, 31, 26, RGB(255, 200, 200)); // 머리 그리기

	SelectObject(nMemDC, oldBitmap); // 이전 비트맵으로 되돌리기

}; // 왼쪽으로 움직임 그리기
