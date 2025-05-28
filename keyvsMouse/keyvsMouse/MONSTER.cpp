#include "MONSTER.h"

enum DIRECTION {
	left = 0, right = 1, up = 2, down = 3
};

MONSTER::MONSTER() // ����Ʈ ���� ������
{
	type = 0;
	x = 0, y = 0;
	hp = 100, power = 10, Mspeed = 10, Aspeed = 1.0f, range = 50;
	size = 10, DropItem = 0;
	view = down;
	//DeltaTime = 0.0f;
	rect = { 0,0,0,0 };
}

MONSTER::MONSTER(int ntype, int nx, int ny) // ���� ������ (�õ�, ��ǥ)
{
	type = ntype;
	x = nx, y = ny;
	view = down;
	//DeltaTime = 0;

	switch (type) {
	case 1:
		hp = 200, power = 10, Mspeed = 10, Aspeed = 1.0f, range = 50;
		size = 20, DropItem = 1;
		break;
	default:
		hp = 100, power = 10, Mspeed = 10, Aspeed = 1.0f, range = 50;
		size = 10, DropItem = 0;
		break;
	}

	rect.left = x - size;
	rect.top = y - size;
	rect.right = x + size;
	rect.bottom = y + size;
}

MONSTER::~MONSTER() // ���� �Ҹ���
{

}

void MONSTER::SetSpot(int nx, int ny) // ��ǥ ����
{
	x = nx;
	y = ny;
}

void MONSTER::SetHp(int nhp) // ü�� ����
{
	hp = nhp;
}

void MONSTER::SetPower(int npower) // ���ݷ� ����
{
	power = npower;
}

void MONSTER::SetMspeed(int nMspeed) // �̵��ӵ� ����
{
	Mspeed = nMspeed;
}

void MONSTER::SetAspeed(int nAspeed) // ���ݼӵ� ����
{
	Aspeed = nAspeed;
}

void MONSTER::SetSize(int nsize) // ũ�� ����
{
	size = nsize;
}

void MONSTER::SetDropItem(int nDropItem) // ��� ������ �õ尪 ����
{
	DropItem = nDropItem;
}

void MONSTER::SetView(int nview) // ���� ����
{
	view = nview;
}

void MONSTER::SetRect(int x1, int y1, int x2, int y2) // �׸��� �� �浹ó�� ��ǥ ���� (int)
{
	rect.left = x1 - size;
	rect.top = y1 - size;
	rect.right = x1 + size;
	rect.bottom = y1 + size;
}

void MONSTER::SetRect(RECT nrect) // �׸��� �� �浹ó�� ��ǥ ���� (rect)
{
	rect.left = nrect.left;
	rect.top = nrect.top;
	rect.right = nrect.right;
	rect.bottom = nrect.bottom;
}

void MONSTER::MoveToPlayer(POINT player1, float DeltaTime) // �÷��̾��� ��ǥ�� �޾� �̵��ϴ� �Լ�
{
	int dx, dy;
	float distance;
	float step;
	float MoveX, MoveY;

	dx = player1.x - x;
	dy = player1.y - y;
	distance = sqrt(dx * dx + dy * dy); // �÷��̾���� �Ÿ�

	// �÷��̾ ����� �ָ� ���� �� �̵�
	if (distance >= 5.0f) { // 5�Ÿ� �̻��϶�
		step = Mspeed * DeltaTime;
		MoveX = (dx / distance) * step;
		MoveY = (dy / distance) * step;
		x += MoveX;
		y += MoveY;
	}
}

void MONSTER::MoveToMachine(POINT buliding) // �⹰�� ��ǥ�� �޾� �̵��ϴ� �Լ�
{
}

void MONSTER::Hit(int power) // �ǰ� �Լ�
{
	hp -= power;
}

void MONSTER::Death() // ��� �Լ�
{
}

void MONSTER::Update() // ����Ÿ�̸� �Լ�
{
}

void MONSTER::Draw(HDC hDC) // �׸��� �Լ�
{
	Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
}
