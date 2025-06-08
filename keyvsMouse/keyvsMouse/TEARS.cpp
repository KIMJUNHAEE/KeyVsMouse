#include "TEARS.h"
#include <stdio.h>
#include <math.h>
#include <cstdio> 
#include <tchar.h>

HBITMAP TearsBitMap[3]; // ���� ��Ʈ��
HDC TearBitDc = NULL; // ���� ��Ʈ�� DC
HBITMAP oldBitmap = NULL;

void TEARS::LoadTearsBitMap() {
	TCHAR filePath[256];
	for (int i = 0; i < 3; i++) {
		_stprintf_s(filePath, _T("P1_graphics/tears_%d.bmp"), i + 1); // ����: "resources/player0.bmp", "resources/player1.bmp" ��
		TearsBitMap[i] = (HBITMAP)LoadImage(NULL, filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (TearsBitMap[i] == NULL) {
			MessageBox(NULL, _T("��Ʈ�� �ε� ����!"), _T("����"), MB_OK);
		}
	}
	TearBitDc = CreateCompatibleDC(NULL); // ���� ��Ʈ�� DC ����
	oldBitmap = (HBITMAP)SelectObject(TearBitDc, TearsBitMap[0]); // 0�� ��Ʈ�� ���

}


TEARS::TEARS(int Px, int Py) { // ������
	x = Px; // ������ ���� x��ǥ
	y = Py; // ������ ���� y��ǥ	
	size = 10;
	width = 16;
	height = 16;
	TearRect.left = x - (width/2);
	TearRect.top = y - (height/2);
	TearRect.right = x + (width/2) + size;
	TearRect.bottom = y + (height/2) + size;
	speed = 1000.0f;          // ���� �ӵ� (�ȼ�/�� ����)
	maxDistance = 600.0f;    // �ִ� �̵� �Ÿ�
	traveledDistance = 0.0f;
	isActive = true;         // �� true�� �ʱ�ȭ!
	vx = 0.0f;
	vy = 0.0f;
}; 


TEARS::~TEARS() { // �Ҹ���
}; 

void TEARS::SetTearRect() { // ���� RECT ���� �Լ�
	TearRect.left = x - (width / 2) - size;
	TearRect.top = y - (height / 2) - size;
	TearRect.right = x + (width / 2) + size;
	TearRect.bottom = y + (height / 2) + size;

};

void TEARS::Shoot(int Tx, int Ty) { // ���� �߻� �Լ�
	
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

void TEARS::Draw(HDC nhDC) {
	SetTearRect();
	TransparentBlt(nhDC, TearRect.left, TearRect.top, (TearRect.right - TearRect.left), (TearRect.bottom - TearRect.top), TearBitDc, 0, 0, 17, 17, RGB(255, 200, 200)); // ���� �׸���
	//SelectObject(nhMemDC, oldBitmap); // ���� ��Ʈ������ �ǵ�����
}

bool TEARS::IsOutOfRange() { // �Ÿ� �ʰ� �Լ�
	return !isActive;
};





