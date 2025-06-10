#pragma once
#include <atlImage.h>
#include "IMAGE.h"

class SHOP
{
private:
	int ShopNum[3]; // ���� ��ȣ
	int x[4]; // ���� ��ȣ�� x��ǥ
	int y[4]; // ���� ��ȣ�� y��ǥ
	int Xsize;
	int Ysize;
	int type[5]; // ���� �õ尪
	float InTimer;

	RECT rect[4]; // ���� �׸���� ��ǥ �迭
public:
	SHOP(); // ������

	~SHOP(); // �Ҹ���

	int coin; // ���� ����

	void SetCoin(int ncoin); // ���� ����
	void SetType(int n, int ntype); // ���� �� ���� �õ尪 ����

	void DrawShop(HDC hDC, int x, int y);

	void Update(float DeltaTime);
};

