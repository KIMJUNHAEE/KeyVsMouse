#pragma once
#include <Windows.h>

class TEARS

{
private:
	int x, y; // ��ǥ
	int size; // ũ��
	int speed; // �ӵ�
	int width; // �ʺ�
	int height; // ����

	RECT TearRect; // ���� ��ġ �� ũ�� rect
	HBITMAP TearsBitMap[3]; // ���� ��Ʈ��
	HBITMAP TearsBoomBitMap[15]; // ���� ���� ��Ʈ��

public:
	TEARS(int Px, int Py); // ������
	~TEARS(); // �Ҹ���
	float intimer = 0.0f; // ���� �߻� �ð�

	void SetTearRect(); // ���� RECT ���� �Լ�
	void Shoot(int Tx, int Ty);  // ���� �߻� �Լ�
	void Draw(HDC hDC, HDC hMemDC); // ���� �׸��� �Լ�

};

