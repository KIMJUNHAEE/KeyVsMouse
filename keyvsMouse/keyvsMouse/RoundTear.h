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

	RoundTear(int Px, int Py); // ������
	~RoundTear(); // �Ҹ���

	void SetRtTearRect(); // ���� RECT ���� �Լ�
	void Update(int Px, int Py, float DeltaTime); // ���� ������Ʈ �Լ�
	void Draw(HDC nhDC); // ���� �׸��� �Լ�
	
};

