#include "RoundTear.h"
#include <stdio.h>
#include <math.h>
#include <cstdio> 
#include <tchar.h>

RoundTear::RoundTear(int Px, int Py) {
	rad = 60;
	int x = Px + rad;
	int y = Py + rad;
	angle = 0.0f;
	speed = 8;

	TCHAR filePath[256];
	_stprintf_s(filePath, _T("P1_graphics/tears_1.bmp")); // ����: "resources/player0.bmp", "resources/player1.bmp" ��
	RtTearBitMap = (HBITMAP)LoadImage(NULL, filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (RtTearBitMap == NULL) {
		MessageBox(NULL, _T("��Ʈ�� �ε� ����!"), _T("����"), MB_OK);
	}
	
};

RoundTear::~RoundTear() { // ���� �Ҹ���
	if (RtTearBitMap) {
		DeleteObject(RtTearBitMap);
		RtTearBitMap = NULL;
	}
};

void RoundTear::SetRtTearRect() { // ���� RECT ���� �Լ�
	RtRect.left = x - 4;
	RtRect.top = y - 4;
	RtRect.right = x + 4;
	RtRect.bottom = y + 4;	
}; 

void RoundTear::Update(int Px, int Py, float DeltaTime) { // ���� ������Ʈ �Լ�
	float radSpeed = speed * DeltaTime;
	angle += radSpeed * rotationDir;
	x = static_cast<int>(Px + rad * cos(angle));
	y = static_cast<int>(Py + rad * sin(angle));
	SetRtTearRect();
}; 

void RoundTear::Draw(HDC nhDC, HDC nhMemDC) { // ���� �׸��� �Լ�
	SetRtTearRect();
	HBITMAP oldBitmap = (HBITMAP)SelectObject(nhMemDC, RtTearBitMap);
	TransparentBlt(nhDC, RtRect.left, RtRect.top, (RtRect.right - RtRect.left), (RtRect.bottom - RtRect.top), nhMemDC, 18, 0, 8, 8, RGB(255, 200, 200));
	SelectObject(nhMemDC, oldBitmap);
}; 

