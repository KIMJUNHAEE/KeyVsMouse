#pragma once
#include <atlImage.h>
#include "IMAGE.h"

class SHOP
{
private:
	int Xsize;
	int Ysize;
	float InTimer;
public:
	SHOP(); // ������

	~SHOP(); // �Ҹ���

	int coin; // ���� ����

	void DrawShop(HDC hDC, int x, int y);

	void Update(float DeltaTime);
};

