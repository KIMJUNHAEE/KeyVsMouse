#include "SHOP.h"

SHOP::SHOP()
{
	x[0] = 0; y[0] = 790;
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

void SHOP::DrawShop(HDC hDC)
{
	IMGshop.Draw(hDC, x[0], y[0], Xsize, Ysize, 0, 0, Xsize, Ysize);
}
