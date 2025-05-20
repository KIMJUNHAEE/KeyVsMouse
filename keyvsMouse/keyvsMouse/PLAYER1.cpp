#include "PLAYER1.h"

PLAYER1::PLAYER1(int nhp, int nx, int ny, int nMspeed, int nAspeed, int nrange, int nsize, int nAct, int nview, RECT nrect) {
	hp = nhp;
	x = nx;
	y = ny;
	Mspeed = nMspeed;
	Aspeed = nMspeed;
	range = nrange;
	size = nsize;
	Act = nAct;
	view = nview;


};// ������



// �� ���� �Լ�
void PLAYER1::SetSpot(int nx, int ny) {
	x = nx;
	y = ny;
}; // ��ǥ ����

void PLAYER1::SetMspeed(int nMspeed) {
	Mspeed = nMspeed;

}; // �̵��ӵ� ����

void PLAYER1::SetAspeed(int nAspeed) {
	Aspeed = nAspeed;

}; // ���ݼӵ� ����
void PLAYER1::SetRange(int nrange) {
	range = nrange;

}; // ���� ��Ÿ� ����

void PLAYER1::SetSize(int nsize) {
	size = nsize;

}; // �÷��̾� ũ�� ����

void PLAYER1::SetAct(int nAct) {
	Act = nAct;

}; // ��Ƽ�� ������ �õ尪 ����

void PLAYER1::SetPct(int nPct) {
	for (int i = 0;i < 80;i++) {
		if (Pct[i] == -1) {
			Pct[i] = nPct;
			break;
		}
	}

}; // �нú� ������ �õ尪 �迭 ����


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

}; // �÷��̾� �ü� ����

void PLAYER1::SetHeadRect() {
	HeadRect.left = x - 15 - size;
	HeadRect.top = y - 20 - size;
	HeadRect.right = x + 15 + size;
	HeadRect.bottom = y + size;
}; // �÷��̾� �Ӹ� �׸���� ��ǥ // 30X20

void PLAYER1::SetBodyRect() {
	BodyRect.left = x - 15 - size;
	BodyRect.top = y + size;
	BodyRect.right = x + 15 + size;
	BodyRect.bottom = y + 10 + size;
}; // �÷��̾� ���� �׸���� ��ǥ // 30X10

void PLAYER1::SetCamera() {
	Came.left = x - 500;
	Came.right = x + 500;
	Came.top = y - 500;
	Came.bottom = y + 500;
}; // ī�޶� ������Ʈ

// �̵��Լ�
void PLAYER1::MoveLeft(int nx, int ny, int nMspeed, int nview) {
	if (HeadRect.left - Mspeed >= 0) {
		x -= Mspeed;
		
		PLAYER1::SetCamera();

	}

}; // �·� �̵� �Լ�

void PLAYER1::MoveRight(int nx, int ny, int nMspeed, int nview) {
	if (HeadRect.right + Mspeed <= 1000) {
		x += Mspeed;
	}

}; // ��� �̵� �Լ�

void PLAYER1::MoveUp(int nx, int ny, int nMspeed, int nview) {
	if (HeadRect.top - Mspeed >= 0) {
		y -= Mspeed;
	}

}; // ���� �̵� �Լ�

void PLAYER1::MoveDowm(int nx, int ny, int nMspeed, int nview) {
	if (BodyRect.bottom + Mspeed <= 1000) {
		y += Mspeed;
	}

}; // �Ʒ��� �̵� �Լ�

// �ΰ���� �Լ�
void PLAYER1::Update(float deltaTime) {

}; // ��ġ ������Ʈ

void PLAYER1::Draw(HDC nhDC) {




}; // �׸���