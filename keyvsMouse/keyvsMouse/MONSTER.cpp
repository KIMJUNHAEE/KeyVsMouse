#include "MONSTER.h"


MONSTER::MONSTER(int nhp, int npower, int nx, int ny, int nMspeed, int nAspeed, int nrange, int nsize, int nDropItem)
{
	hp = nhp;
	power = npower;
	x = nx, y = ny;
	Mspeed = nMspeed;
	Aspeed = nAspeed;
	range = nrange;
	size = nsize;
	DropItem = nDropItem;
	view = down;
	DeltaTime = 0;

	rect.left = x - size;
	rect.top = y - size;
	rect.right = x + size;
	rect.bottom = y + size;
}

MONSTER::~MONSTER()
{
}

void MONSTER::SetSpot(int nx, int ny)
{
	x = nx;
	y = ny;
}

void MONSTER::SetHp(int nhp)
{
	hp = nhp;
}

void MONSTER::SetPower(int npower)
{
	power = npower;
}

void MONSTER::SetMspeed(int nMspeed)
{
	Mspeed = nMspeed;
}

void MONSTER::SetAspeed(int nAspeed)
{
	Aspeed = nAspeed;
}

void MONSTER::SetSize(int nsize)
{
	size = nsize;
}

void MONSTER::SetDropItem(int nDropItem)
{
	DropItem = nDropItem;
}

void MONSTER::SetView(int nview)
{
	view = nview;
}

void MONSTER::SetRect(int x1, int y1, int x2, int y2)
{
	rect.left = x1 - size;
	rect.top = y1 - size;
	rect.right = x1 + size;
	rect.bottom = y1 + size;
}

void MONSTER::SetRect(RECT nrect)
{
	rect.left = nrect.left;
	rect.top = nrect.top;
	rect.right = nrect.right;
	rect.bottom = nrect.bottom;
}

void MONSTER::MoveToPlayer(POINT player1)
{

}

void MONSTER::MoveToMachine(POINT buliding)
{
}

void MONSTER::Hit(int power)
{
	hp -= power;
}

void MONSTER::Death()
{
}

void MONSTER::Update()
{
}

void MONSTER::Draw(HDC hDC)
{
	HPEN hPen, OldPen;
	HBRUSH hBrush, OldBrush;



}
