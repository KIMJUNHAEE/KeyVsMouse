#include "PLAYER1.h"
#include <cstdio> 
#include <tchar.h>

PLAYER1::PLAYER1(int nhp, int nx, int ny, int nMspeed, float nAspeed, int nrange, int nsize, int nAct, int nview) { // ������
	hp = nhp;
	x = nx;
	y = ny;
	Mspeed = nMspeed;
	Aspeed = nAspeed;
	range = nrange;
	size = nsize;
	Act = nAct;
	view = nview;
	Damage = 200; // �⺻ ���ݷ�
	for (int i = 0; i < 6; i++) {
		// �� �̹��� ���� ��θ� �־�� �մϴ�
		TCHAR filePath[256];
		_stprintf_s(filePath, _T("P1_graphics/P1_%d.bmp"), (i + 1)); // ����: "resources/player0.bmp", "resources/player1.bmp" ��
		P1BitMap[i] = (HBITMAP)LoadImage(NULL, filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (P1BitMap[i] == NULL) {
			MessageBox(NULL, _T("��Ʈ�� �ε� ����!"), _T("����"), MB_OK);
		}
	}
};

PLAYER1::~PLAYER1() { // �Ҹ���
	for (int i = 0; i < 7; i++) {
		if (P1BitMap[i]) {
			DeleteObject(P1BitMap[i]);  // GDI ���ҽ� ����
			P1BitMap[i] = nullptr;      // ������ ��ȿȭ (����)
		}
	}
};

// �� ���� �Լ�
void PLAYER1::SetSpot(int nx, int ny) { // ��ǥ ����
	x = nx;
	y = ny;
};

void PLAYER1::SetMspeed(int nMspeed) { // �̵��ӵ� ����
	Mspeed = nMspeed;

};

void PLAYER1::SetAspeed(int nAspeed) { // ���ݼӵ� ����
	Aspeed = nAspeed;

};
void PLAYER1::SetRange(int nrange) { // ���� ��Ÿ� ����
	range = nrange;

};

void PLAYER1::SetSize(int nsize) { // �÷��̾� ũ�� ����
	size = nsize;

};

void PLAYER1::SetAct(int nAct) { // ��Ƽ�� ������ �õ尪 ����
	Act = nAct;

};

void PLAYER1::SetPct(int nPct) { // �нú� ������ �õ尪 �迭 ����
	for (int i = 0; i < 80; i++) {
		if (Pct[i] == -1) {
			Pct[i] = nPct;
			break;
		}
	}

};

void PLAYER1::SetHeadRect() { // �÷��̾� �Ӹ� �׸���� ��ǥ

	HeadRect.left = x;
	HeadRect.top = y;
	HeadRect.right = x + (31 * size);
	HeadRect.bottom = y + (26 * size);

};

void PLAYER1::SetBodyRect() { // �÷��̾� ���� �׸���� ��ǥ

	BodyRect.left = HeadRect.left + (5 * size);
	BodyRect.top = HeadRect.top + (21 * size);
	BodyRect.right = HeadRect.right - (5 * size);
	BodyRect.bottom = HeadRect.bottom + (9 * size);

};

void PLAYER1::SetTarget() { // �÷��̾� Ÿ�� ��ǥ ����
	Tx = (HeadRect.right + HeadRect.left) / 2; // Ÿ�� X��ǥ
	Ty = (HeadRect.top + BodyRect.bottom) / 2; // Ÿ�� Y��ǥ
};

void PLAYER1::SetCamera() { // ī�޶� ������Ʈ
	Came.left = x - 500;
	Came.right = x + 500;
	Came.top = y - 500;
	Came.bottom = y + 500;
};

// �̵��Լ�
void PLAYER1::MoveLeft() { // �·� �̵� �Լ�
	if (HeadRect.left - Mspeed >= 0) {
		x -= Mspeed;
		SetHeadRect();
		SetBodyRect();
		SetCamera();
	}
};

void PLAYER1::MoveRight() { // ��� �̵� �Լ�
	if (HeadRect.right + Mspeed <= 1000) {
		x += Mspeed;
		SetHeadRect();
		SetBodyRect();
		SetCamera();
	}
};

void PLAYER1::MoveUp() { // ���� �̵� �Լ�
	if (HeadRect.top - Mspeed >= 0) {
		y -= Mspeed;
		SetHeadRect();
		SetBodyRect();
		SetCamera();
	}
};

void PLAYER1::MoveDown() { // �Ʒ��� �̵� �Լ�
	if (BodyRect.bottom + Mspeed <= 1000) {
		y += Mspeed;
		SetHeadRect();
		SetBodyRect();
		SetCamera();
	}
};

void PLAYER1::MoveUpLeft() { // �»�� �밢�� �̵� �Լ�
	if ((HeadRect.left - Mspeed >= 0) && (HeadRect.top - Mspeed >= 0)) {
		x -= Mspeed;
		y -= Mspeed;
		SetHeadRect();
		SetBodyRect();
		SetCamera();
	}
}; 

void PLAYER1::MoveUpRight() { // ���� �밢�� �̵� �Լ�
	if ((HeadRect.right + Mspeed <= 1000) && (HeadRect.top - Mspeed >= 0)) {
		x += Mspeed;
		y -= Mspeed;
		SetHeadRect();
		SetBodyRect();
		SetCamera();
	}

};

void PLAYER1::MoveDownLeft() { // ���ϴ� �밢�� �̵� �Լ�
	if ((HeadRect.left - Mspeed >= 0) && (BodyRect.bottom + Mspeed <= 1000)) {
		x -= Mspeed;
		y += Mspeed;
		SetHeadRect();
		SetBodyRect();
		SetCamera();
	}
}; 

void PLAYER1::MoveDownRight() {// ���ϴ� �밢�� �̵� �Լ�
	if ((HeadRect.right + Mspeed <= 1000) && (BodyRect.bottom + Mspeed <= 1000)) {
		x += Mspeed;
		y += Mspeed;
		SetHeadRect();
		SetBodyRect();
		SetCamera();
	}
}; 



// �ΰ���� �Լ�
void PLAYER1::Update(float deltaTime) { // ���� Ÿ�̸� ������Ʈ �Լ�
	InTimer += deltaTime;
	if (InTimer >= 3.0f) {
		InTimer = 0.0f;

	}

};

void PLAYER1::Draw(HDC nhDC, HDC nMemDC) { // ��� dc, �޸� dc ����, �������� �׸���
	SetHeadRect();
	SetBodyRect();
	view = down; // �ü� ����
	HBITMAP oldBitmap = (HBITMAP)SelectObject(nMemDC, P1BitMap[0]);
	
	//���� �޸� -> ��µ�÷�
	TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 5, 44, 21, 14, RGB(255, 200, 200));


	//�Ӹ� �޸� -> ��µ�÷�
	TransparentBlt(nhDC, HeadRect.left, HeadRect.top, (HeadRect.right - HeadRect.left), (HeadRect.bottom - HeadRect.top), nMemDC, 0, 0, 31, 26, RGB(255, 200, 200));

}; // �׸���

void PLAYER1::DMDraw(HDC nhDC, HDC nMemDC, int nCount) { // �Ʒ��� ������ �׸���
	SetHeadRect();
	SetBodyRect();
	view = down; // �ü� ����
	HBITMAP oldBitmap = (HBITMAP)SelectObject(nMemDC, P1BitMap[0]); // �Ʒ��� ������ ��Ʈ�� ����
	
	if (nCount == 0) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 197, 12, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 1) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 229, 12, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 2) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 5, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 3) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 37, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 4) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 70, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 5) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 101, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 6) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 133, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 7) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 165, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 8) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 197, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 9) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 228, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	TransparentBlt(nhDC, HeadRect.left, HeadRect.top, (HeadRect.right - HeadRect.left), (HeadRect.bottom - HeadRect.top), nMemDC, 0, 0, 31, 26, RGB(255, 200, 200)); // �Ӹ� �׸���

	SelectObject(nMemDC, oldBitmap); // ���� ��Ʈ������ �ǵ�����

};

void PLAYER1::UMDraw(HDC nhDC, HDC nMemDC, int nCount) { // ���� ������ �׸���
	SetHeadRect();
	SetBodyRect();
	view = up; // �ü� ����
	HBITMAP oldBitmap = (HBITMAP)SelectObject(nMemDC, P1BitMap[0]); // �Ʒ��� ������ ��Ʈ�� ����
	

	if (nCount == 9) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 197, 12, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 8) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 229, 12, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 7) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 5, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 6) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 37, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 5) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 70, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 4) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 101, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 3) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 133, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 2) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 165, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 1) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 197, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 0) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 228, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	TransparentBlt(nhDC, HeadRect.left, HeadRect.top, (HeadRect.right - HeadRect.left), (HeadRect.bottom - HeadRect.top), nMemDC, 128, 0, 31, 26, RGB(255, 200, 200)); // �Ӹ� �׸���

	SelectObject(nMemDC, oldBitmap); // ���� ��Ʈ������ �ǵ�����

};

void PLAYER1::RMDraw(HDC nhDC, HDC nMemDC, int nCount) { // ���������� ������ �׸���
	SetHeadRect();
	SetBodyRect();
	view = right; // �ü� ����
	HBITMAP oldBitmap = (HBITMAP)SelectObject(nMemDC, P1BitMap[0]); // �Ʒ��� ������ ��Ʈ�� ����
	
	if (nCount == 0) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 5, 76, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 1) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 37, 76, 21, 14, RGB(255, 200, 200)); // ���� �׸���	
	}
	else if (nCount == 2) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 70, 76, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 3) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 101, 76, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 4) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 133, 76, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 5) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 165, 76, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 6) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 197, 76, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 7) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 228, 76, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 8) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 5, 107, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 9) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 37, 107, 21, 14, RGB(255, 200, 200)); // ���� �׸���	
	}

	TransparentBlt(nhDC, HeadRect.left, HeadRect.top, (HeadRect.right - HeadRect.left), (HeadRect.bottom - HeadRect.top), nMemDC, 64, 0, 31, 26, RGB(255, 200, 200)); // �Ӹ� �׸���

	SelectObject(nMemDC, oldBitmap); // ���� ��Ʈ������ �ǵ�����

};

void PLAYER1::LMDraw(HDC nhDC, HDC nMemDC, int nCount) { // �������� ������ �׸���
	SetHeadRect();
	SetBodyRect();
	view = left; // �ü� ����
	HBITMAP oldBitmap = (HBITMAP)SelectObject(nMemDC, P1BitMap[0]); // �Ʒ��� ������ ��Ʈ�� ����
	
	if (nCount == 0) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 70, 107, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 1) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 101, 107, 21, 14, RGB(255, 200, 200)); // ���� �׸���	
	}
	else if (nCount == 2) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 133, 107, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 3) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 165, 107, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 4) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 197, 107, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 5) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 228, 107, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 6) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 5, 127, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 7) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 37, 127, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 8) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 70, 127, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 9) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), nMemDC, 101, 127, 21, 14, RGB(255, 200, 200)); // ���� �׸���	
	}

	TransparentBlt(nhDC, HeadRect.left, HeadRect.top, (HeadRect.right - HeadRect.left), (HeadRect.bottom - HeadRect.top), nMemDC, 259, 0, 31, 26, RGB(255, 200, 200)); // �Ӹ� �׸���

	SelectObject(nMemDC, oldBitmap); // ���� ��Ʈ������ �ǵ�����
};


int PLAYER1::ShootTime(float deltaTime) { // ���� Ÿ�̸� ������Ʈ �Լ�
	InTimer += deltaTime;
	if (InTimer >= Aspeed) {
		InTimer = 0.0f; // Ÿ�̸� �ʱ�ȭ
		return 1; // ����!
	}
	return 0; // ��������!
};