#include "MONSTER.h"

enum DIRECTION {
	left = 0, right = 1, up = 2, down = 3
};

MONSTER::MONSTER() // ����Ʈ ���� ������
{
	x = 0, y = 0;
	type = 0;
	Xsize = 0, Ysize = 0;
	hp = 0, power = 0, Mspeed = 0, Aspeed = 0.0f, range = 0;
	DropItem = 0;

	view = down;
	InTimer = 0.0f;

	rect = { 0,0,0,0 };

	Animation = 0;
}

MONSTER::~MONSTER() // ���� �Ҹ���
{

}

void MONSTER::SetSpot(int nx, int ny) // ��ǥ ����
{
	x = nx; y = ny;
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

void MONSTER::SetSize(int n1size, int n2size) // ũ�� ����
{
	Xsize = n1size; Ysize = n2size;
}

void MONSTER::SetDropItem(int nDropItem) // ��� ������ �õ尪 ����
{
	DropItem = nDropItem;
}

void MONSTER::SetView(int nview) // ���� ����
{
	view = nview;
}

void MONSTER::SetRect()
{
	rect.left = x;
	rect.top = y;
	rect.right = x + Xsize;
	rect.bottom = y + Ysize;
}

int MONSTER::GetX()
{
	return (x + Xsize) / 2;
}
int MONSTER::GetY()
{
	return (y + Ysize) / 2;
}

void MONSTER::SetMonster(int ntype)
{
	switch (ntype)
	{
	case 1:
		type = 1;
		Xsize = 19, Ysize = 15;
		hp = 200, power = 10, Mspeed = 50, Aspeed = 1.0f, range = 0;
		DropItem = 1;
		Animation = 1;
		break;
	case 2:
		type = 2;
		Xsize = 32, Ysize = 32;
		hp = 400, power = 30, Mspeed = 30, Aspeed = 1.0f, range = 0;
		DropItem = 1;
		Animation = 1;
		break;
	case 3:
		type = 3;
		Xsize = 64; Ysize = 128;
		hp = 1000, power = 50, Mspeed = 1500, Aspeed = 1.0f, range = 0;
		DropItem = 1;
		Animation = 1;
		break;
	default:
		break;
	}
}

void MONSTER::MoveToPlayer(POINT player1, RECT head, RECT body, float DeltaTime) // �÷��̾��� ��ǥ�� �޾� �̵��ϴ� �Լ�
{
	if (hp > 0) {
		RECT lprcDest;
		if (IntersectRect(&lprcDest, &rect, &head) || IntersectRect(&lprcDest, &rect, &body)) {
			if (type == 1) { // �ĸ�
				Death();
			}
			else if (type == 2) { // ��״�?
				if (Animation == 3 || Animation == 4) {
					Animation = 5;
					InTimer = 0.0f;
				}
			}
			else if (type == 3 && Animation == 1) {
				x = head.left;
				y = head.top - Ysize;
			}
			return;
		}
		if (type == 3 && Animation != 1) {
			return;
		}

		float dx, dy;
		float distance;
		float step;
		float MoveX, MoveY;

		dx = player1.x - x;
		dy = player1.y - y;
		distance = sqrt(dx * dx + dy * dy); // �÷��̾���� �Ÿ�

		if (type == 2) {
			if (Animation == 1) {
				if (distance < 200.0f) {
					Animation++;
					InTimer = 0.0f;
				}
			}
			else if (Animation == 2) {
				if (InTimer <= 1000.0f && distance > 200.0f) {
					InTimer = 1000.0f;
				}
			}
			else if (Animation == 3 || Animation == 4) {
				if (distance > 200.0f) {
					Animation = 2;
					InTimer = 1000.0f;
				}
			}
			else if (Animation >= 5 && Animation <= 7) {
				if (InTimer <= 3.0f) {
					return;
				}
				else {
					Animation = 2;
					InTimer = 0.0f;
				}
			}
		}
		if (distance > 0.0001f) {
			step = Mspeed * DeltaTime;
			MoveX = (dx / distance) * step;
			MoveY = (dy / distance) * step;
			x += MoveX;
			y += MoveY;
		}
		SetRect();
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
	hp = 0;
	if (type == 1) {
		Animation = 3;
		x = x + (Xsize / 2);
		y = y + (Ysize / 2);
		Xsize = 59, Ysize = 47;
		x = x - (Xsize / 2);
		y = y - (Ysize / 2);
	}
}

bool MONSTER::Update(float DeltaTime) // ����Ÿ�̸� �Լ�
{
	InTimer += DeltaTime;

	if (Animation == 0 && hp == 0) {
		return true;
	}

	if (type == 1) { // �ĸ�
		if (Animation == 2 && hp <= 0) {
			Death();
		}
	}
	else if (type == 3) { // ����
		if (Animation == 1) {
			Ysize = 64;
		}
		if (Animation == 2 || Animation == 6) {
			Ysize = 64;
		}
		else if (Animation == 3 || Animation == 5) {
			Ysize = 128;
		}
		else if (Animation == 4) {
			Ysize = 174;
		}
	}

	return false;
}

void MONSTER::Draw(HDC hDC) // �׸��� �Լ�
{
	if (Animation == 0) {
		return;
	}
	if (type == 1) {
		if (hp > 0) {
			// Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom); �����
			if (Animation == 1) {
				IMGfly[1].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
				Animation++;
			}
			else if (Animation == 2) {
				IMGfly[2].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
				Animation--;
			}
		}
		else {
			IMGfly[Animation++].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
			if (Animation > 13) {
				Animation = 0;
			}
		}
	}
	else if (type == 2) {
		if (hp > 0) {
			if (Animation == 1) {
				IMGparabite[Animation].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
			}
			else if (Animation == 2) {
				IMGparabite[Animation].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
				if (InTimer >= 0.5f && InTimer < 1000.0f) {
					Animation++;
				}
			else if (InTimer >= 1000.5f) {
					Animation--;
				}
			}
			else if (Animation == 3) {
				IMGparabite[Animation++].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
			}
			else if (Animation == 4) {
				IMGparabite[Animation--].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
			}
			else {
				IMGparabite[Animation++].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
				if (Animation > 7) {
					Animation = 5;
				}
			}
		}
	}
	else if (type == 3) {
		if (hp > 0) {
			if (InTimer >= 0.5f) {
				if (Animation >= 1 && Animation < 7) {
					Animation++;
					InTimer = 0.0f;
				}
				if (Animation == 7) {
					Animation = 1;
					InTimer = 0.0f;
				}
			}
			int cnt = Animation;
			if (Animation == 5) {
				cnt = 3;
			}
			else if (Animation == 6) {
				cnt = 2;
			}
			if (Animation != 1) {
				IMGmom[cnt].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
			}
		}
	}
}
