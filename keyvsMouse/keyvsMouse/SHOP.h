#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

class SHOP
{
private:
	int ShopNum[5]; // ���� ��ȣ
	int level; // ���� ����
	int exp; // ���� ����ġ
	int coin; // ���� ����
	int x[5]; // ���� ��ȣ�� x��ǥ
	int y[5]; // ���� ��ȣ�� y��ǥ
	int type[5]; // ���� �õ尪

	RECT rect[5]; // ���� �׸���� ��ǥ �迭
public:
	SHOP(); // ������

	~SHOP(); // �Ҹ���

	void SetLevel(int nlevel); // ���� ����
	void SetExp(int nexp); // ����ġ ����
	void SetCoin(int ncoin); // ���� ����
	void SetType(int n, int ntype); // ���� �� ���� �õ尪 ����
};

