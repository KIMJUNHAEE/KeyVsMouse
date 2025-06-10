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
	IMGparabite[3].Draw(hDC, x+110, y+10, 180, 180, 0, 0, 32, 32);
	IMGboomfly[1].Draw(hDC, x +310, y+10, 180, 180, 0, 0, 32, 32);
	IMGmom[22].Draw(hDC, x + 510, y + 10, 180, 180, 0, 0, 128, 174);
	TextOut(hDC, x + 110, y + 10, L"1coin", lstrlen(L"1coin"));
	TextOut(hDC, x + 310, y + 10, L"2coin", lstrlen(L"2coin"));
	TextOut(hDC, x + 510, y + 10, L"10coin", lstrlen(L"10coin"));
}

void SHOP::Update(float DeltaTime)
{
	InTimer += DeltaTime;

	if (InTimer >= 1.0f) {
		coin += 1;
		InTimer = 0.0f;
	}
}
