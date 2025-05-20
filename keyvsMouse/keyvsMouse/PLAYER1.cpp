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


};// 생성자



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
	HeadRect.left = x - 15 - size;
	HeadRect.top = y - 20 - size;
	HeadRect.right = x + 15 + size;
	HeadRect.bottom = y + size;
}; // 플레이어 머리 그리기용 좌표 // 30X20

void PLAYER1::SetBodyRect() {
	BodyRect.left = x - 15 - size;
	BodyRect.top = y + size;
	BodyRect.right = x + 15 + size;
	BodyRect.bottom = y + 10 + size;
}; // 플레이어 몸통 그리기용 좌표 // 30X10

void PLAYER1::SetCamera() {
	Came.left = x - 500;
	Came.right = x + 500;
	Came.top = y - 500;
	Came.bottom = y + 500;
}; // 카메라 업데이트

// 이동함수
void PLAYER1::MoveLeft(int nx, int ny, int nMspeed, int nview) {
	if (HeadRect.left - Mspeed >= 0) {
		x -= Mspeed;
		
		PLAYER1::SetCamera();

	}

}; // 좌로 이동 함수

void PLAYER1::MoveRight(int nx, int ny, int nMspeed, int nview) {
	if (HeadRect.right + Mspeed <= 1000) {
		x += Mspeed;
	}

}; // 우로 이동 함수

void PLAYER1::MoveUp(int nx, int ny, int nMspeed, int nview) {
	if (HeadRect.top - Mspeed >= 0) {
		y -= Mspeed;
	}

}; // 위로 이동 함수

void PLAYER1::MoveDowm(int nx, int ny, int nMspeed, int nview) {
	if (BodyRect.bottom + Mspeed <= 1000) {
		y += Mspeed;
	}

}; // 아래로 이동 함수

// 부가요소 함수
void PLAYER1::Update(float deltaTime) {

}; // 위치 업데이트

void PLAYER1::Draw(HDC nhDC) {




}; // 그리기