#pragma once
#include <windows.h>

enum DIRECTION {
	left = 0, right = 1, up = 2, down = 3
};

class PLAYER1
{
private:
	int hp; // 플레이어 체력
	int x, y; // 머리, 몸통 사이 중심 좌표
	int Mspeed; // 이동속도
	int Aspeed; // 공격속도
	int range; // 공격 사거리
	int size; // 플레이어 크기
	int Act; // 액티브 아이템 시드값
	int Pct[80]; // 패시브 아이템 시드 배열
	int view; // 시선
	int DeltaTime; // 내부 타이머

	RECT HeadRect; // 플레이어 머리 그리기용 좌표 
	RECT BodyRect; // 플레이어 몸통 그리기용 좌표 
	RECT Came; // 카메라 영역 (1000,1000)

	HBITMAP BitMap[5]; 

public:
	PLAYER1(int nhp, int nx, int ny, int nMspeed, int nAspeed, int nrange, int nsize, int nAct, int nview, RECT nrect); // 생성자
	~PLAYER1(); // 소멸자

	// 값 변경 함수
	void SetSpot(int nx, int ny); // 좌표 설정
	void SetMspeed(int nMspeed); // 이동속도 설정
	void SetAspeed(int nAspeed); // 공격속도 설정
	void SetRange(int nrange); // 공격 사거리 설정
	void SetSize(int nsize); // 플레이어 크기 설정
	void SetAct(int nAct); // 액티브 아이템 시드값 설정
	void SetPct(int nPct); // 패시브 아이템 시드값 배열 설정
	void SetView(int nview); // 플레이어 시선 설정
	void SetHeadRect(); // 플레이어 머리 그리기용 좌표
	void SetBodyRect(); // 플레이어 몸통 그리기용 좌표
	void SetCamera(); // 카메라 업데이트

	// 이동함수
	void MoveLeft(int nx, int ny, int nMspeed, int nview); // 좌로 이동 함수
	void MoveRight(int nx, int ny, int nMspeed, int nview); // 우로 이동 함수
	void MoveUp(int nx, int ny, int nMspeed, int nview); // 위로 이동 함수
	void MoveDowm(int nx, int ny, int nMspeed, int nview); // 아래로 이동 함수

	// 부가요소 함수
	void Update(float deltaTime); // 위치 업데이트
	void Draw(HDC nhDC); // 그리기

};

