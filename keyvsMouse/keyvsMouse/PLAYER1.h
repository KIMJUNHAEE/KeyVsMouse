#pragma once
#include <windows.h>

enum DIRECTION {
	left = 0, right = 1, up = 2, down = 3
};

class PLAYER1
{
private:
	int hp; // �÷��̾� ü��
	int x, y; // �Ӹ�, ���� ���� �߽� ��ǥ
	int Mspeed; // �̵��ӵ�
	int Aspeed; // ���ݼӵ�
	int range; // ���� ��Ÿ�
	int size; // �÷��̾� ũ��
	int Act; // ��Ƽ�� ������ �õ尪
	int Pct[80]; // �нú� ������ �õ� �迭
	int view; // �ü�
	int DeltaTime; // ���� Ÿ�̸�

	RECT HeadRect; // �÷��̾� �Ӹ� �׸���� ��ǥ 
	RECT BodyRect; // �÷��̾� ���� �׸���� ��ǥ 
	RECT Came; // ī�޶� ���� (1000,1000)

	HBITMAP BitMap[5]; 

public:
	PLAYER1(int nhp, int nx, int ny, int nMspeed, int nAspeed, int nrange, int nsize, int nAct, int nview, RECT nrect); // ������
	~PLAYER1(); // �Ҹ���

	// �� ���� �Լ�
	void SetSpot(int nx, int ny); // ��ǥ ����
	void SetMspeed(int nMspeed); // �̵��ӵ� ����
	void SetAspeed(int nAspeed); // ���ݼӵ� ����
	void SetRange(int nrange); // ���� ��Ÿ� ����
	void SetSize(int nsize); // �÷��̾� ũ�� ����
	void SetAct(int nAct); // ��Ƽ�� ������ �õ尪 ����
	void SetPct(int nPct); // �нú� ������ �õ尪 �迭 ����
	void SetView(int nview); // �÷��̾� �ü� ����
	void SetHeadRect(); // �÷��̾� �Ӹ� �׸���� ��ǥ
	void SetBodyRect(); // �÷��̾� ���� �׸���� ��ǥ
	void SetCamera(); // ī�޶� ������Ʈ

	// �̵��Լ�
	void MoveLeft(int nx, int ny, int nMspeed, int nview); // �·� �̵� �Լ�
	void MoveRight(int nx, int ny, int nMspeed, int nview); // ��� �̵� �Լ�
	void MoveUp(int nx, int ny, int nMspeed, int nview); // ���� �̵� �Լ�
	void MoveDowm(int nx, int ny, int nMspeed, int nview); // �Ʒ��� �̵� �Լ�

	// �ΰ���� �Լ�
	void Update(float deltaTime); // ��ġ ������Ʈ
	void Draw(HDC nhDC); // �׸���

};

