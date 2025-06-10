#pragma once
#include <Windows.h>

class TEARS

{
private:
	int size; // ũ��
	float vy = 0.0f; // �������
	

public:
	int x, y; // ��ǥ
	int width; // �ʺ�
	int height; // ����
	RECT TearRect; // ���� ��ġ �� ũ�� rect
	float vx = 0.0f; // �������
	float startX, startY;
	float speed = 300.0f;   // ���� �ӵ� (�ȼ�/��)
	float traveledDistance = 0.0f; // �̵� �Ÿ� ����
	float maxDistance = 500.0f;    // ���� �Ÿ� ���� �� ����
	bool isActive = true;   // ����ִ� ���� ����

	TEARS(int Px, int Py, float n); // ������
	~TEARS(); // �Ҹ���

	static void LoadTearsBitMap(); // ���� ��Ʈ�� �ε� �Լ�
	void SetTearRect(); // ���� RECT ���� �Լ�
	void Shoot(int Tx, int Ty);  // ���� �߻� �Լ�
	void Update(float DeltaTime); // ���� ������Ʈ �Լ�
	void Draw(HDC nhDC); // ���� �׸��� �Լ�
	bool IsOutOfRange();    // �Ÿ� üũ �Լ�
	void SetRange(float nrange);

};

