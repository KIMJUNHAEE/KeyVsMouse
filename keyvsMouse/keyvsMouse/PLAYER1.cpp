#include "PLAYER1.h"
#include <cstdio> 
#include <tchar.h>

static HDC P1BitDC = NULL; // 플레이어 비트맵 DC
static HBITMAP P1BitMap[6]; // 플레이어 비트맵
static HBITMAP oldBitmap = NULL; // 이전 비트맵 저장용

PLAYER1::PLAYER1(int nhp, int nx, int ny, int nMspeed, float nAspeed, int nrange, int nsize, int nAct, int nview) { // 생성자
	hp = nhp;
	x = nx;
	y = ny;
	Mspeed = nMspeed;
	Aspeed = nAspeed;
	range = nrange;
	size = nsize;
	Act = nAct;
	view = nview;
	Damage = 200; // 기본 공격력
	for (int i = 0; i < 6; i++) {
		// 각 이미지 파일 경로를 넣어야 합니다
		TCHAR filePath[256];
		_stprintf_s(filePath, _T("P1_graphics/P1_%d.bmp"), (i + 1)); // 예시: "resources/player0.bmp", "resources/player1.bmp" 등
		P1BitMap[i] = (HBITMAP)LoadImage(NULL, filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (P1BitMap[i] == NULL) {
			MessageBox(NULL, _T("비트맵 로딩 실패!"), _T("오류"), MB_OK);
		}
	}

	P1BitDC = CreateCompatibleDC(NULL); // 메모리 DC 생성
	oldBitmap = (HBITMAP)SelectObject(P1BitDC, P1BitMap[0]);


};

PLAYER1::~PLAYER1() { // 소멸자
	for (int i = 0; i < 6; i++) {
		if (P1BitMap[i]) {
			DeleteObject(P1BitMap[i]);  // GDI 리소스 해제
			P1BitMap[i] = nullptr;      // 포인터 무효화 (안전)
		}
	}
};

// 값 변경 함수
void PLAYER1::SetSpot(int nx, int ny) { // 좌표 설정
	x = nx;
	y = ny;
};

void PLAYER1::SetMspeed(int nMspeed) { // 이동속도 설정
	Mspeed = nMspeed;

};

void PLAYER1::SetAspeed(int nAspeed) { // 공격속도 설정
	Aspeed = nAspeed;

};
void PLAYER1::SetRange(int nrange) { // 공격 사거리 설정
	range = nrange;

};

void PLAYER1::SetSize(int nsize) { // 플레이어 크기 설정
	size = nsize;

};

void PLAYER1::SetAct(int nAct) { // 액티브 아이템 시드값 설정
	Act = nAct;

};

void PLAYER1::SetPct(int nPct) { // 패시브 아이템 시드값 배열 설정
	for (int i = 0; i < 80; i++) {
		if (Pct[i] == -1) {
			Pct[i] = nPct;
			break;
		}
	}

};

void PLAYER1::SetHeadRect() { // 플레이어 머리 그리기용 좌표

	HeadRect.left = x;
	HeadRect.top = y;
	HeadRect.right = x + (31 * size);
	HeadRect.bottom = y + (26 * size);

};

void PLAYER1::SetBodyRect() { // 플레이어 몸통 그리기용 좌표

	BodyRect.left = HeadRect.left + (5 * size);
	BodyRect.top = HeadRect.top + (21 * size);
	BodyRect.right = HeadRect.right - (5 * size);
	BodyRect.bottom = HeadRect.bottom + (9 * size);

};

void PLAYER1::SetTarget() { // 플레이어 타겟 좌표 설정
	Tx = (HeadRect.right + HeadRect.left) / 2; // 타겟 X좌표
	Ty = (HeadRect.top + BodyRect.bottom) / 2; // 타겟 Y좌표
};

void PLAYER1::SetCamera() { // 카메라 업데이트
	int camWidth = 1000;
	int camHeight = 1000;

	int newLeft = Tx - camWidth / 2;
	int newTop = Ty - 400;

	// 카메라가 맵 밖으로 나가지 않도록 제한
	if (newLeft < 0) newLeft = 0;
	if (newTop < 0) newTop = 0;
	if (newLeft + camWidth > 4000) newLeft = 4000 - camWidth;
	if (newTop + 1100 > 4000) newTop = 4000 - 1100;

	// 최종 설정
	Came.left = newLeft;
	Came.top = newTop;
	Came.right = newLeft + camWidth;
	Came.bottom = newTop + camHeight;
};

// 이동함수
void PLAYER1::MoveLeft() { // 좌로 이동 함수
	if (HeadRect.left - Mspeed >= 0) {
		x -= Mspeed;
		SetHeadRect();
		SetBodyRect();
		SetCamera();
	}
};

void PLAYER1::MoveRight() { // 우로 이동 함수
	if (HeadRect.right + Mspeed <= 4000) {
		x += Mspeed;
		SetHeadRect();
		SetBodyRect();
		SetCamera();
	}
};

void PLAYER1::MoveUp() { // 위로 이동 함수
	if (HeadRect.top - Mspeed >= 0) {
		y -= Mspeed;
		SetHeadRect();
		SetBodyRect();
		SetCamera();
	}
};

void PLAYER1::MoveDown() { // 아래로 이동 함수
	if (BodyRect.bottom + Mspeed <= 4000) {
		y += Mspeed;
		SetHeadRect();
		SetBodyRect();
		SetCamera();
	}
};

void PLAYER1::MoveUpLeft() { // 좌상단 대각선 이동 함수
	if ((HeadRect.left - Mspeed >= 0) && (HeadRect.top - Mspeed >= 0)) {
		x -= Mspeed;
		y -= Mspeed;
		SetHeadRect();
		SetBodyRect();
		SetCamera();
	}
}; 

void PLAYER1::MoveUpRight() { // 우상단 대각선 이동 함수
	if ((HeadRect.right + Mspeed <= 4000) && (HeadRect.top - Mspeed >= 0)) {
		x += Mspeed;
		y -= Mspeed;
		SetHeadRect();
		SetBodyRect();
		SetCamera();
	}

};

void PLAYER1::MoveDownLeft() { // 좌하단 대각선 이동 함수
	if ((HeadRect.left - Mspeed >= 0) && (BodyRect.bottom + Mspeed <= 4000)) {
		x -= Mspeed;
		y += Mspeed;
		SetHeadRect();
		SetBodyRect();
		SetCamera();
	}
}; 

void PLAYER1::MoveDownRight() {// 우하단 대각선 이동 함수
	if ((HeadRect.right + Mspeed <= 4000) && (BodyRect.bottom + Mspeed <= 4000)) {
		x += Mspeed;
		y += Mspeed;
		SetHeadRect();
		SetBodyRect();
		SetCamera();
	}
}; 



// 부가요소 함수
void PLAYER1::Update(float deltaTime) { // 내부 타이머 업데이트 함수
	InTimer += deltaTime;
	if (InTimer >= 3.0f) {
		InTimer = 0.0f;

	}

};

void PLAYER1::Draw(HDC nhDC) { // 출력 dc, 메모리 dc 받음, 정지상태 그리기
	SetHeadRect();
	SetBodyRect();
	view = down; // 시선 설정

	//몸통 메모리 -> 출력디시로
	TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 5, 44, 21, 14, RGB(255, 200, 200));
	//머리 메모리 -> 출력디시로
	TransparentBlt(nhDC, HeadRect.left, HeadRect.top, (HeadRect.right - HeadRect.left), (HeadRect.bottom - HeadRect.top), P1BitDC, 0, 0, 31, 26, RGB(255, 200, 200));
	//SelectObject(nMemDC, oldBitmap);
}; // 그리기

void PLAYER1::DMDraw(HDC nhDC, int nCount) { // 아래로 움직임 그리기
	SetHeadRect();
	SetBodyRect();
	view = down; // 시선 설정
	
	if (nCount == 0) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 197, 12, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 1) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 229, 12, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 2) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 5, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 3) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 37, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 4) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 70, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 5) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 101, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 6) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 133, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 7) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 165, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 8) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 197, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 9) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 228, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	TransparentBlt(nhDC, HeadRect.left, HeadRect.top, (HeadRect.right - HeadRect.left), (HeadRect.bottom - HeadRect.top), P1BitDC, 0, 0, 31, 26, RGB(255, 200, 200)); // 머리 그리기

	//SelectObject(nMemDC, oldBitmap); // 이전 비트맵으로 되돌리기

};

void PLAYER1::UMDraw(HDC nhDC, int nCount) { // 위로 움직임 그리기
	SetHeadRect();
	SetBodyRect();
	view = up; // 시선 설정	

	if (nCount == 9) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 197, 12, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 8) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 229, 12, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 7) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 5, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 6) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 37, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 5) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 70, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 4) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 101, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 3) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 133, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 2) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 165, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 1) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 197, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 0) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 228, 44, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	TransparentBlt(nhDC, HeadRect.left, HeadRect.top, (HeadRect.right - HeadRect.left), (HeadRect.bottom - HeadRect.top), P1BitDC, 128, 0, 31, 26, RGB(255, 200, 200)); // 머리 그리기

	//SelectObject(nMemDC, oldBitmap); // 이전 비트맵으로 되돌리기

};

void PLAYER1::RMDraw(HDC nhDC, int nCount) { // 오른쪽으로 움직임 그리기
	SetHeadRect();
	SetBodyRect();
	view = right; // 시선 설정
	
	if (nCount == 0) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 5, 76, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 1) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 37, 76, 21, 14, RGB(255, 200, 200)); // 몸통 그리기	
	}
	else if (nCount == 2) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 70, 76, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 3) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 101, 76, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 4) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 133, 76, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 5) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 165, 76, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 6) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 197, 76, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 7) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 228, 76, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 8) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 5, 107, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 9) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 37, 107, 21, 14, RGB(255, 200, 200)); // 몸통 그리기	
	}

	TransparentBlt(nhDC, HeadRect.left, HeadRect.top, (HeadRect.right - HeadRect.left), (HeadRect.bottom - HeadRect.top), P1BitDC, 64, 0, 31, 26, RGB(255, 200, 200)); // 머리 그리기

	//SelectObject(nMemDC, oldBitmap); // 이전 비트맵으로 되돌리기

};

void PLAYER1::LMDraw(HDC nhDC, int nCount) { // 왼쪽으로 움직임 그리기
	SetHeadRect();
	SetBodyRect();
	view = left; // 시선 설정
	
	if (nCount == 0) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 70, 107, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 1) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 101, 107, 21, 14, RGB(255, 200, 200)); // 몸통 그리기	
	}
	else if (nCount == 2) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 133, 107, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 3) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 165, 107, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 4) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 197, 107, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 5) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 228, 107, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 6) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 5, 127, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 7) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 37, 127, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 8) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 70, 127, 21, 14, RGB(255, 200, 200)); // 몸통 그리기
	}
	else if (nCount == 9) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 101, 127, 21, 14, RGB(255, 200, 200)); // 몸통 그리기	
	}

	TransparentBlt(nhDC, HeadRect.left, HeadRect.top, (HeadRect.right - HeadRect.left), (HeadRect.bottom - HeadRect.top), P1BitDC, 259, 0, 31, 26, RGB(255, 200, 200)); // 머리 그리기

	//SelectObject(nMemDC, oldBitmap); // 이전 비트맵으로 되돌리기
};

int PLAYER1::ShootTime(float deltaTime) { // 공격 타이머 업데이트 함수
	InTimer += deltaTime;
	if (InTimer >= Aspeed) {
		InTimer = 0.0f; // 타이머 초기화
		return 1; // 공격!
	}
	return 0; // 쏘지마라!
};

int PLAYER1::SetDieRect(float deltaTime) {
	DieRect.left = HeadRect.left;
	DieRect.top = HeadRect.top;
	HeadRect.left = 0;
	HeadRect.right = 0;
	HeadRect.top = 0;
	HeadRect.bottom = 0;
	BodyRect.left = 0;
	BodyRect.right = 0;
	BodyRect.top = 0;
	BodyRect.bottom = 0;
	DieTimer += deltaTime;

	if (DieTimer <= 0.5f) {
		DieRect.right = 29*2;
		DieRect.bottom = 34*2;
		return 9;
	}
	else {
		DieRect.top += 7;
		DieRect.right = 67;
		DieRect.bottom = 28;
		return 10;
	}
};

void PLAYER1::AddLp(int nLp) {
	Lp += nLp;

	if (Lp >= 100) {
		Level += 1;
		Lp -= 100;
		LevelUp = TRUE; 
	}

}