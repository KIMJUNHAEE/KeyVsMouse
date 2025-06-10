#pragma once
#include <Windows.h>

class RoundTear
{
private:
	

public:
	int x, y;
	int speed;
	int rad;
	float angle;
	int rotationDir = 0;
	RECT RtRect; 

	RoundTear(int Px, int Py); // 생성자
	~RoundTear(); // 소멸자

	void SetRtTearRect(); // 눈물 RECT 설정 함수
	void Update(int Px, int Py, float DeltaTime); // 눈물 업데이트 함수
	void Draw(HDC nhDC); // 눈물 그리기 함수
	
};

