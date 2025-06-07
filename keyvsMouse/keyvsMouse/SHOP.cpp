#include "SHOP.h"

SHOP::SHOP()
{
	coin = 0;

	Xsize = 800;
	Ysize = 200;

	rect[0].left = x[0];
	rect[0].top = y[0];
	rect[0].right = 800;
	rect[0].bottom = 1000;
}

SHOP::~SHOP()
{
}

void SHOP::SetCoin(int ncoin)
{
}

void SHOP::SetType(int n, int ntype)
{
}

void SHOP::DrawShop(HDC hDC, int x, int y)
{
	IMGshop.Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
}
