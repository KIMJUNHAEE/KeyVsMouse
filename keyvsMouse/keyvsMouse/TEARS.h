#pragma once
#include <Windows.h>

class TEARS

{
private:
	int size; // 크기
	float vy = 0.0f; // 방향백터
	

public:
	int x, y; // 좌표
	int width; // 너비
	int height; // 높이
	RECT TearRect; // 눈물 위치 및 크기 rect
	float vx = 0.0f; // 방향백터
	float startX, startY;
	float speed = 300.0f;   // 눈물 속도 (픽셀/초)
	float traveledDistance = 0.0f; // 이동 거리 누적
	float maxDistance = 500.0f;    // 일정 거리 도달 시 제거
	bool isActive = true;   // 살아있는 눈물 여부

	TEARS(int Px, int Py, float n); // 생성자
	~TEARS(); // 소멸자

	static void LoadTearsBitMap(); // 눈물 비트맵 로드 함수
	void SetTearRect(); // 눈물 RECT 설정 함수
	void Shoot(int Tx, int Ty);  // 눈물 발사 함수
	void Update(float DeltaTime); // 눈물 업데이트 함수
	void Draw(HDC nhDC); // 눈물 그리기 함수
	bool IsOutOfRange();    // 거리 체크 함수
	void SetRange(float nrange);

};

