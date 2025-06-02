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
	
public:
	TEARS(); // 생성자
	~TEARS(); // 소멸자

	void SetTearRect(); // 눈물 RECT 설정 함수
	void Shoot(int Px, int Py, int Tx, int Ty, HDC nhDC, HDC nMemDC);  // 눈물 발사 함수

};

