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
	Intersect = false;
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
		hp = 400, power = 20, Mspeed = 30, Aspeed = 1.0f, range = 0;
		DropItem = 1;
		Animation = 1;
		break;
	case 3:
		type = 3;
		Xsize = 120; Ysize = 49;
		hp = 1000, power = 20, Mspeed = 0, Aspeed = 1.0f, range = 0;
		DropItem = 1;
		Animation = 1;
		InTimer = -1.0f;
		break;
	case 4:
		type = 4;
		Xsize = 32; Ysize = 32;
		hp = 300, power = 20, Mspeed = 100, Aspeed = 1.0f, range = 0;
		DropItem = 1;
		Animation = 1;
		break;
	default:
		break;
	}
}

int MONSTER::MoveToPlayer(POINT player1, RECT head, RECT body, float DeltaTime) // �÷��̾��� ��ǥ�� �޾� �̵��ϴ� �Լ�
{
	if (hp > 0) {
		RECT lprcDest;
		if (IntersectRect(&lprcDest, &rect, &head) || IntersectRect(&lprcDest, &rect, &body)) {
			if (type == 1) { // �ĸ�
				Death();
				return power;
			}
			else if (type == 2) { // ��״�?
				if (Animation == 3 || Animation == 4) {
					Animation = 5;
					InTimer = 0.0f;
				}
			}
			if (Intersect) {
				return 0;
			}
			Intersect = true;
			return power;
		}
		else {
			Intersect = false;
		}

		if (type == 3) {
			if (Animation == 1) {
				x = (head.left + head.right) / 2 - 60;
				y = body.bottom - 20;
				return 0;
			}
			else if (Animation == 2) {
				x = ((head.left + head.right) / 2) - 64;
				y = head.top - 96;
			}
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
					return 0;
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
	return 0;
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
	else { // �ĸ��� �ƴҶ�
		Animation = 101;
		x = x + (Xsize / 2);
		y = y + (Ysize / 2);
		Xsize = 64, Ysize = 64;
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
		if ((Animation == 1 || Animation == 2) && hp <= 0) {
			Death();
		}
	}
	else { // �ĸ� ����
		if (Animation < 100 && hp <= 0) {
			Death();
		}
		if (type == 3) { // ����
			if (Animation == 1) {
				Xsize = 120;
				Ysize = 49;
			}
			if (InTimer >= 2.0f) {
				if (Animation == 2) {
					Xsize = 128;
					Ysize = 16;
				}
				else if (Animation > 2 && Animation < 22) {
					Ysize -= 8;
				}
				else if (Animation == 22) {
					Ysize = 166;
				}
			}
			else {
				if (Animation == 2) {
					Xsize = 128;
					Ysize = 24;
				}
				else if (Animation > 2 && Animation < 22) {
					Ysize += 8;
				}
				else if (Animation == 22) {
					Ysize = 174;
				}
			}
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
	else { // �ĸ��� �ƴҶ�
		if (Animation >= 100) {
			int cnt = Animation - 100;
			IMGdeath[cnt].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
			Animation++;
			if (Animation > 111) {
				Animation = 0;
			}
		}
		else {
			if (type == 2) {
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
					if (InTimer >= 2.0f) {
						if (Animation == 1) {
							InTimer = -1.0f;
						}
						if (Animation > 1 && Animation <= 22) {
							Animation--;
						}
					}
					else if (InTimer >= 0.0f && InTimer < 2.0f) {
						if (Animation >= 1 && Animation < 22) {
							Animation++;
							InTimer = 0.0f;
						}
					}
					IMGmom[Animation].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
				}
			}
			else if (type == 4) {
				if (hp > 0) {
					if (Animation == 1) {
						IMGboomfly[Animation++].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
					}
					else if (Animation == 2){
						IMGboomfly[Animation--].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
					}
				}
			}
		}
	}
}
