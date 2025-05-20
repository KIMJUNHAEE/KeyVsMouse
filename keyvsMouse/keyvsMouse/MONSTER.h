#pragma once
#include <windows.h>
#include <stdlib.h>

enum DIRECTION {
	left = 0, right = 1, up = 2, down = 3
};

class MONSTER
{
private:
	int x, y; // 좌표
	int hp; // 체력
	int power; // 공격력
	int Mspeed; // 이동속도
	int Aspeed; // 공격속도
	int range; // 공격 사거리
	int size; // 몬스터 크기
	int DropItem; // 드랍되는 아이템 시드값
	int view; // 시선
	int DeltaTime; // 내부 타이머

	RECT rect; // 그리기용 좌표

public:
	MONSTER(int nhp, int npower, int nx, int ny, int nMspeed, int nAspeed, int nrange, int nsize, int nDropItem); // 생성자
	
	~MONSTER(); // 소멸자

	// 값 변경 함수
	void SetSpot(int nx, int ny); // 좌표 설정
	void SetHp(int nhp); // 체력 설정
	void SetPower(int npower); // 공격력 설정
	void SetMspeed(int nMspeed); // 이동속도 설정
	void SetAspeed(int nAspeed); // 공격속도 설정
	void SetSize(int nsize); // 몬스터 크기 설정
	void SetDropItem(int nDropItem); // 드랍되는 아이템 시드값 설정
	void SetView(int nview); // 몬스터 시선 설정
	void SetRect(RECT nrect); // 그리기용 좌표

	// 이동함수
	void MoveToPlayer(POINT player1); // 플레이어 위치 이동 함수
	void MoveToMachine(POINT buliding); // 기물 위치 근처 이동 함수

	// 행동함수
	void Hit(int power); // 피격 함수
	void Death(); // 죽음 함수

	// 부가요소 함수
	void Update(); // 위치 업데이트
	void Draw(HDC hDC); // 그리기
};

