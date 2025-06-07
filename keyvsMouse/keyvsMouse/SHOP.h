#pragma once
#include <atlImage.h>
#include "IMAGE.h"

class SHOP
{
private:
	int ShopNum[3]; // 상점 번호
	int coin; // 코인 보유
	int x[4]; // 상점 번호별 x좌표
	int y[4]; // 상점 번호별 y좌표
	int Xsize;
	int Ysize;
	int type[5]; // 몬스터 시드값

	RECT rect[4]; // 상점 그리기용 좌표 배열
public:
	SHOP(); // 생성자

	~SHOP(); // 소멸자

	void SetCoin(int ncoin); // 코인 설정
	void SetType(int n, int ntype); // 상점 별 몬스터 시드값 설정

	void DrawShop(HDC hDC, int x, int y);
};

