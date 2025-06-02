#pragma once
#include <Windows.h>

class TEARS

{
private:
	int x, y; // 좌표
	int size; // 크기
	int speed; // 속도
	int width; // 너비
	int height; // 높이

	RECT TearRect; // 눈물 위치 및 크기 rect
	HBITMAP TearsBitMap[3]; // 눈물 비트맵
	HBITMAP TearsBoomBitMap[15]; // 눈물 폭팔 비트맵

public:
	TEARS(int Px, int Py); // 생성자
	~TEARS(); // 소멸자
	float intimer = 0.0f; // 눈물 발사 시간

	void SetTearRect(); // 눈물 RECT 설정 함수
	void Shoot(int Tx, int Ty);  // 눈물 발사 함수
	void Draw(HDC hDC, HDC hMemDC); // 눈물 그리기 함수

};

