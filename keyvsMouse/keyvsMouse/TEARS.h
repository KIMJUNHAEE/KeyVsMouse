#pragma once
#include <Windows.h>

class TEARS

{
private:
	int size; // ũ��
	int width; // �ʺ�
	int height; // ����
	RECT TearRect; // ���� ��ġ �� ũ�� rect
	float vx = 0.0f; // �������
	float vy = 0.0f; // �������

	
	HBITMAP TearsBitMap[3]; // ���� ��Ʈ��
	HBITMAP TearsBoomBitMap[15]; // ���� ���� ��Ʈ��

public:
	int x, y; // ��ǥ
	float startX, startY;
	float speed = 300.0f;   // ���� �ӵ� (�ȼ�/��)
	float traveledDistance = 0.0f; // �̵� �Ÿ� ����
	float maxDistance = 500.0f;    // ���� �Ÿ� ���� �� ����
	bool isActive = true;   // ����ִ� ���� ����
	

	TEARS(int Px, int Py); // ������
	~TEARS(); // �Ҹ���

	void SetTearRect(); // ���� RECT ���� �Լ�
	void Shoot(int Tx, int Ty);  // ���� �߻� �Լ�
	void Update(float DeltaTime); // ���� ������Ʈ �Լ�
	void Draw(HDC nhDC, HDC nhMemDC); // ���� �׸��� �Լ�
	void DrawBoom(HDC nhDC, HDC nhMemDC); // ���� ���� �׸��� �Լ�	
	bool IsOutOfRange();    // �Ÿ� üũ �Լ�

};

