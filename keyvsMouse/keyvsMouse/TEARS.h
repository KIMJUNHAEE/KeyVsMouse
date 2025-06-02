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
	
public:
	TEARS(); // ������
	~TEARS(); // �Ҹ���

	void SetTearRect(); // ���� RECT ���� �Լ�
	void Shoot(int Px, int Py, int Tx, int Ty, HDC nhDC, HDC nMemDC);  // ���� �߻� �Լ�

};

