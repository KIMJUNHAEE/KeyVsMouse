#pragma once
#include <windows.h>
#include <iostream>
#include <cmath>
#include <atlImage.h>

class MONSTER
{
private:
	int x, y; // ���� �»�� ��ǥ
	int type; // ���� �õ尪
	int Xsize; // ���� x ũ��
	int Ysize; // ���� y ũ��
	int hp; // ü��
	int power; // ���ݷ�
	int Mspeed; // �̵��ӵ�
	float Aspeed; // ���ݼӵ�
	int range; // ���� ��Ÿ�
	int DropItem; // ����Ǵ� ������ �õ尪
	int view; // �ü�
	float InTimer; // ���� Ÿ�̸�
	
	int Animation; // �ִϸ��̼� �׸� ��ȣ

	RECT rect; // �׸���� ��ǥ

public:


	MONSTER(); // ����Ʈ ������
	~MONSTER(); // �Ҹ���

	// �� ���� �Լ�
	void SetSpot(int nx, int ny); // ��ǥ ����
	void SetHp(int nhp); // ü�� ����
	void SetPower(int npower); // ���ݷ� ����
	void SetMspeed(int nMspeed); // �̵��ӵ� ����
	void SetAspeed(int nAspeed); // ���ݼӵ� ����
	void SetSize(int n1size, int n2size); // ���� ũ�� ����
	void SetDropItem(int nDropItem); // ����Ǵ� ������ �õ尪 ����
	void SetView(int nview); // ���� �ü� ����
	void SetRect(); // �׸����

	// ���� Ÿ�� ����
	void SetMonster(int type);

	// �̵��Լ�
	void MoveToPlayer(POINT player1, float DeltaTime); // �÷��̾� ��ġ �̵� �Լ�
	void MoveToMachine(POINT buliding); // �⹰ ��ġ ��ó �̵� �Լ�

	// �ൿ�Լ�
	void Hit(int power); // �ǰ� �Լ�
	void Death(); // ���� �Լ�

	// �ΰ���� �Լ�
	void Update(); // ��ġ ������Ʈ
	void Draw(HDC hDC); // �׸���


};

