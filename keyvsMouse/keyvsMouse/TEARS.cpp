#include "TEARS.h"
#include <stdio.h>
#include <math.h>
#include <cstdio> 
#include <tchar.h>


TEARS::TEARS(int Px, int Py) { // 생성자

	TCHAR filePath[256];
	for (int i = 0; i < 3; i++) {
		_stprintf_s(filePath, _T("P1_graphics/tears_%d.bmp"), i+1); // 예시: "resources/player0.bmp", "resources/player1.bmp" 등
		TearsBitMap[i] = (HBITMAP)LoadImage(NULL, filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (TearsBitMap[i] == NULL) {
			MessageBox(NULL, _T("비트맵 로딩 실패!"), _T("오류"), MB_OK);
		}
	}

	TCHAR Tb_filePath[256];
	for (int i = 0; i < 15; i++) {
		_stprintf_s(Tb_filePath, _T("P1_graphics/Tb_%d.bmp"), i + 1); // 예시: "resources/player0.bmp", "resources/player1.bmp" 등
		TearsBoomBitMap[i] = (HBITMAP)LoadImage(NULL, Tb_filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (TearsBoomBitMap[i] == NULL) {
			MessageBox(NULL, _T("비트맵 로딩 실패!"), _T("오류"), MB_OK);
		}
	}

	x = Px; // 눈물의 시작 x좌표
	y = Py; // 눈물의 시작 y좌표	
	size = 10;
	width = 16;
	height = 16;
	TearRect.left = x - (width/2);
	TearRect.top = y - (height/2);
	TearRect.right = x + (width/2) + size;
	TearRect.bottom = y + (height/2) + size;
	speed = 1000.0f;          // 눈물 속도 (픽셀/초 기준)
	maxDistance = 600.0f;    // 최대 이동 거리
	traveledDistance = 0.0f;
	isActive = true;         // 꼭 true로 초기화!
	vx = 0.0f;
	vy = 0.0f;
}; 


TEARS::~TEARS() { // 소멸자


}; 

void TEARS::SetTearRect() { // 눈물 RECT 설정 함수
	TearRect.left = x - (width / 2) - size;
	TearRect.top = y - (height / 2) - size;
	TearRect.right = x + (width / 2) + size;
	TearRect.bottom = y + (height / 2) + size;

};

void TEARS::Shoot(int Tx, int Ty) { // 눈물 발사 함수
	
	SetTearRect();
	float dx = Tx - x;
	float dy = Ty - y;
	float length = sqrtf(dx * dx + dy * dy);
	if (length == 0.0f) return;

	vx = dx / length;
	vy = dy / length;
};

void TEARS::Update(float DeltaTime) {
	float step = speed * DeltaTime;

	x += vx * step;
	y += vy * step;

	traveledDistance += step;
	if (traveledDistance >= maxDistance) {
		isActive = false;
	}
	SetTearRect();
};

void TEARS::Draw(HDC nhDC, HDC nhMemDC) {
	SetTearRect();
	HBITMAP oldBitmap = (HBITMAP)SelectObject(nhMemDC, TearsBitMap[0]); // 0번 비트맵 사용
	TransparentBlt(nhDC, TearRect.left, TearRect.top, (TearRect.right - TearRect.left), (TearRect.bottom - TearRect.top), nhMemDC, 0, 0, 17, 17, RGB(255, 200, 200)); // 눈물 그리기
	SelectObject(nhMemDC, oldBitmap); // 이전 비트맵으로 되돌리기
}

void TEARS::DrawBoom(HDC nhDC, HDC nhMemDC) {
	SetTearRect();
	for (int i = 0; i < 15; i++) {
		HBITMAP oldBitmap = (HBITMAP)SelectObject(nhMemDC, TearsBoomBitMap[i]); // 0번 비트맵 사용
		TransparentBlt(nhDC, TearRect.left, TearRect.top, (TearRect.right - TearRect.left), (TearRect.bottom - TearRect.top), nhMemDC, 0, 0, 64, 1, RGB(255, 200, 200)); // 눈물 그리기
		SelectObject(nhMemDC, oldBitmap); // 이전 비트맵으로 되돌리기
	}
};

bool TEARS::IsOutOfRange() { // 거리 초과 함수
	return !isActive;
};





