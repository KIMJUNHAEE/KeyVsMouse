#include "PLAYER1.h"
#include <cstdio> 
#include <tchar.h>

static HDC P1BitDC = NULL; // �÷��̾� ��Ʈ�� DC
static HBITMAP P1BitMap[6]; // �÷��̾� ��Ʈ��
static HBITMAP oldBitmap = NULL; // ���� ��Ʈ�� �����

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

	P1BitDC = CreateCompatibleDC(NULL); // �޸� DC ����
	oldBitmap = (HBITMAP)SelectObject(P1BitDC, P1BitMap[0]);


};

PLAYER1::~PLAYER1() { // �Ҹ���
	for (int i = 0; i < 6; i++) {
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
	int camWidth = 1000;
	int camHeight = 1000;

	int newLeft = Tx - camWidth / 2;
	int newTop = Ty - 400;

	// ī�޶� �� ������ ������ �ʵ��� ����
	if (newLeft < 0) newLeft = 0;
	if (newTop < 0) newTop = 0;
	if (newLeft + camWidth > 4000) newLeft = 4000 - camWidth;
	if (newTop + 1100 > 4000) newTop = 4000 - 1100;

	// ���� ����
	Came.left = newLeft;
	Came.top = newTop;
	Came.right = newLeft + camWidth;
	Came.bottom = newTop + camHeight;
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
	if (HeadRect.right + Mspeed <= 4000) {
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
	if (BodyRect.bottom + Mspeed <= 4000) {
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
	if ((HeadRect.right + Mspeed <= 4000) && (HeadRect.top - Mspeed >= 0)) {
		x += Mspeed;
		y -= Mspeed;
		SetHeadRect();
		SetBodyRect();
		SetCamera();
	}

};

void PLAYER1::MoveDownLeft() { // ���ϴ� �밢�� �̵� �Լ�
	if ((HeadRect.left - Mspeed >= 0) && (BodyRect.bottom + Mspeed <= 4000)) {
		x -= Mspeed;
		y += Mspeed;
		SetHeadRect();
		SetBodyRect();
		SetCamera();
	}
}; 

void PLAYER1::MoveDownRight() {// ���ϴ� �밢�� �̵� �Լ�
	if ((HeadRect.right + Mspeed <= 4000) && (BodyRect.bottom + Mspeed <= 4000)) {
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

void PLAYER1::Draw(HDC nhDC) { // ��� dc, �޸� dc ����, �������� �׸���
	SetHeadRect();
	SetBodyRect();
	view = down; // �ü� ����

	//���� �޸� -> ��µ�÷�
	TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 5, 44, 21, 14, RGB(255, 200, 200));
	//�Ӹ� �޸� -> ��µ�÷�
	TransparentBlt(nhDC, HeadRect.left, HeadRect.top, (HeadRect.right - HeadRect.left), (HeadRect.bottom - HeadRect.top), P1BitDC, 0, 0, 31, 26, RGB(255, 200, 200));
	//SelectObject(nMemDC, oldBitmap);
}; // �׸���

void PLAYER1::DMDraw(HDC nhDC, int nCount) { // �Ʒ��� ������ �׸���
	SetHeadRect();
	SetBodyRect();
	view = down; // �ü� ����
	
	if (nCount == 0) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 197, 12, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 1) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 229, 12, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 2) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 5, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 3) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 37, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 4) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 70, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 5) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 101, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 6) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 133, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 7) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 165, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 8) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 197, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 9) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 228, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	TransparentBlt(nhDC, HeadRect.left, HeadRect.top, (HeadRect.right - HeadRect.left), (HeadRect.bottom - HeadRect.top), P1BitDC, 0, 0, 31, 26, RGB(255, 200, 200)); // �Ӹ� �׸���

	//SelectObject(nMemDC, oldBitmap); // ���� ��Ʈ������ �ǵ�����

};

void PLAYER1::UMDraw(HDC nhDC, int nCount) { // ���� ������ �׸���
	SetHeadRect();
	SetBodyRect();
	view = up; // �ü� ����	

	if (nCount == 9) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 197, 12, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 8) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 229, 12, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 7) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 5, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 6) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 37, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 5) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 70, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 4) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 101, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 3) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 133, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 2) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 165, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 1) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 197, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 0) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 228, 44, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	TransparentBlt(nhDC, HeadRect.left, HeadRect.top, (HeadRect.right - HeadRect.left), (HeadRect.bottom - HeadRect.top), P1BitDC, 128, 0, 31, 26, RGB(255, 200, 200)); // �Ӹ� �׸���

	//SelectObject(nMemDC, oldBitmap); // ���� ��Ʈ������ �ǵ�����

};

void PLAYER1::RMDraw(HDC nhDC, int nCount) { // ���������� ������ �׸���
	SetHeadRect();
	SetBodyRect();
	view = right; // �ü� ����
	
	if (nCount == 0) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 5, 76, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 1) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 37, 76, 21, 14, RGB(255, 200, 200)); // ���� �׸���	
	}
	else if (nCount == 2) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 70, 76, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 3) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 101, 76, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 4) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 133, 76, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 5) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 165, 76, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 6) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 197, 76, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 7) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 228, 76, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 8) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 5, 107, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 9) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 37, 107, 21, 14, RGB(255, 200, 200)); // ���� �׸���	
	}

	TransparentBlt(nhDC, HeadRect.left, HeadRect.top, (HeadRect.right - HeadRect.left), (HeadRect.bottom - HeadRect.top), P1BitDC, 64, 0, 31, 26, RGB(255, 200, 200)); // �Ӹ� �׸���

	//SelectObject(nMemDC, oldBitmap); // ���� ��Ʈ������ �ǵ�����

};

void PLAYER1::LMDraw(HDC nhDC, int nCount) { // �������� ������ �׸���
	SetHeadRect();
	SetBodyRect();
	view = left; // �ü� ����
	
	if (nCount == 0) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 70, 107, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 1) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 101, 107, 21, 14, RGB(255, 200, 200)); // ���� �׸���	
	}
	else if (nCount == 2) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 133, 107, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 3) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 165, 107, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 4) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 197, 107, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 5) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 228, 107, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 6) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 5, 127, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 7) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 37, 127, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 8) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 70, 127, 21, 14, RGB(255, 200, 200)); // ���� �׸���
	}
	else if (nCount == 9) {
		TransparentBlt(nhDC, BodyRect.left, BodyRect.top, (BodyRect.right - BodyRect.left), (BodyRect.bottom - BodyRect.top), P1BitDC, 101, 127, 21, 14, RGB(255, 200, 200)); // ���� �׸���	
	}

	TransparentBlt(nhDC, HeadRect.left, HeadRect.top, (HeadRect.right - HeadRect.left), (HeadRect.bottom - HeadRect.top), P1BitDC, 259, 0, 31, 26, RGB(255, 200, 200)); // �Ӹ� �׸���

	//SelectObject(nMemDC, oldBitmap); // ���� ��Ʈ������ �ǵ�����
};

int PLAYER1::ShootTime(float deltaTime) { // ���� Ÿ�̸� ������Ʈ �Լ�
	InTimer += deltaTime;
	if (InTimer >= Aspeed) {
		InTimer = 0.0f; // Ÿ�̸� �ʱ�ȭ
		return 1; // ����!
	}
	return 0; // ��������!
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