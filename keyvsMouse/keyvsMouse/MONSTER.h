#pragma once
#include <windows.h>

enum DIRECTION {
	left = 0, right = 1, up = 2, down = 3
};


class MONSTER
{
private:
	int hp;
	int x, y; // 좌표
	int Mspeed; // 이동속도
	int Aspeed; // 공격속도
	int range; // 공격 사거리
	int size; // 몬스터 크기
	int DropItem; // 드랍되는 아이템 시드값
	int view; // 시선
	int DeltaTime; // 내부 타이머

	RECT rect; // 그리기용 좌표

public:
	MONSTER(int x, int y, int Mspeed, int Aspeed, int range, int size, int Act, int view, RECT rect); // 생성자
	~MONSTER(); // 소멸자

	// 값 변경 함수
	void SetSpot(int x, int y) {}; // 좌표 설정
	void SetMspeed(int Mspeed) {}; // 이동속도 설정
	void SetAspeed(int Aspeed) {}; // 공격속도 설정
	void SetSize(int size) {}; // 몬스터 크기 설정
	void SetAct(int Act) {}; // 드랍되는 아이템 시드값 설정
	void SetView(int view) {}; // 몬스터 시선 설정
	void SetRect(RECT rect) {}; // 그리기용 좌표

	// 이동함수
	void MoveToPlayer(int x, int y, int Mspeed, int view, POINT player1) {}; // 플레이어 위치 이동 함수
	void MoveToMachine(int x, int y, int Mspeed, int view, POINT buliding) {}; // 기물 위치 근처 이동 함수

	// 행동함수
	void Hit() {}; // 피격 함수
	void Death(int x, int y, int DropItem) {}; // 죽음 함수

	// 부가요소 함수
	void Update(float deltaTime) {}; // 위치 업데이트
	void Draw(HDC hDC) {}; // 그리기

};

