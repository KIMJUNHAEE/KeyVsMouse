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
		TearsBitMap[i] = (HBITMAP)LoadImage(NULL, Tb_filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (TearsBitMap[i] == NULL) {
			MessageBox(NULL, _T("비트맵 로딩 실패!"), _T("오류"), MB_OK);
		}
	}

	x = Px; // 눈물의 시작 x좌표
	y = Py; // 눈물의 시작 y좌표	
	width = 10;
	height = 10;
	TearRect.left = x - (width/2);
	TearRect.top = y - (height/2);
	TearRect.right = x + (width/2) + size;
	TearRect.bottom = y + (height/2) + size;
	intimer = 0.0f;
}; 


TEARS::~TEARS() { // 소멸자


}; 

void TEARS::SetTearRect() { // 눈물 RECT 설정 함수
	TearRect.left = x; 
	TearRect.top = y;
	TearRect.right = TearRect.left + width + size;
	TearRect.bottom = TearRect.top + height + size;

};

void TEARS::Shoot(int Tx, int Ty) { // 눈물 발사 함수
	float dx = Tx - x;
	float dy = Ty - y;
	float length = sqrt(dx * dx + dy * dy);



};



