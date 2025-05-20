#pragma once
#include <windows.h>

enum DIRECTION {
	left = 0, right = 1, up = 2, down = 3
};


class MONSTER
{
private:
	int hp;
	int x, y; // ��ǥ
	int Mspeed; // �̵��ӵ�
	int Aspeed; // ���ݼӵ�
	int range; // ���� ��Ÿ�
	int size; // ���� ũ��
	int DropItem; // ����Ǵ� ������ �õ尪
	int view; // �ü�
	int DeltaTime; // ���� Ÿ�̸�

	RECT rect; // �׸���� ��ǥ

public:
	MONSTER(int x, int y, int Mspeed, int Aspeed, int range, int size, int Act, int view, RECT rect); // ������
	~MONSTER(); // �Ҹ���

	// �� ���� �Լ�
	void SetSpot(int x, int y) {}; // ��ǥ ����
	void SetMspeed(int Mspeed) {}; // �̵��ӵ� ����
	void SetAspeed(int Aspeed) {}; // ���ݼӵ� ����
	void SetSize(int size) {}; // ���� ũ�� ����
	void SetAct(int Act) {}; // ����Ǵ� ������ �õ尪 ����
	void SetView(int view) {}; // ���� �ü� ����
	void SetRect(RECT rect) {}; // �׸���� ��ǥ

	// �̵��Լ�
	void MoveToPlayer(int x, int y, int Mspeed, int view, POINT player1) {}; // �÷��̾� ��ġ �̵� �Լ�
	void MoveToMachine(int x, int y, int Mspeed, int view, POINT buliding) {}; // �⹰ ��ġ ��ó �̵� �Լ�

	// �ൿ�Լ�
	void Hit() {}; // �ǰ� �Լ�
	void Death(int x, int y, int DropItem) {}; // ���� �Լ�

	// �ΰ���� �Լ�
	void Update(float deltaTime) {}; // ��ġ ������Ʈ
	void Draw(HDC hDC) {}; // �׸���

};

