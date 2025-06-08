#include "SHOP.h"

SHOP::SHOP()
{
	coin = 0;

	Xsize = 800;
	Ysize = 200;
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
	IMGparabite[3].Draw(hDC, x+100, y, 200, 200, 0, 0, 32, 32);
}
