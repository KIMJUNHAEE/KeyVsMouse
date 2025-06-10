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
	SHOP(); // 생성자

	~SHOP(); // 소멸자

	int coin; // 코인 보유

	void DrawShop(HDC hDC, int x, int y);

	void Update(float DeltaTime);
};

