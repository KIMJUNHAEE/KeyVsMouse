#pragma once
#include <windows.h>
#include "P1RESOURCE.h"

enum DIRECTION {
	left = 0, right = 1, up = 2, down = 3
};

class PLAYER1
{
private:	
	int x, y; // �÷��̾� �Ӹ� �»�� ��ǥ
	int Mspeed; // �̵��ӵ�
	float Aspeed; // ���ݼӵ�
	int range; // ���� ��Ÿ�
	int size; // �÷��̾� ũ��
	int Act; // ��Ƽ�� ������ �õ尪
	int Pct[80]; // �нú� ������ �õ� �迭
	int view; // �ü�
	float DieTimer = 0.0f;

public:
	PLAYER1(int nhp, int nx, int ny, int nMspeed, float nAspeed, int nrange, int nsize, int nAct, int nview); // ������
	~PLAYER1(); // �Ҹ���

	int hp; // �÷��̾� ü��
	int Tx, Ty; // �÷��̾� Ÿ�� ��ǥ
	int Damage; // �÷��̾� ���ݷ�
	RECT HeadRect; // �÷��̾� �Ӹ� �׸���� ��ǥ 
	RECT BodyRect; // �÷��̾� ���� �׸���� ��ǥ 
	RECT DieRect; // �÷��̾� ��� �׸���� ��ǥ
	RECT Came; // ī�޶� ���� (1000,1000)
	float InTimer = 0.0f; // ���� Ÿ�̸�
	HBITMAP P1BitMap[6]; // �÷��̾� ��Ʈ��

	// �� ���� �Լ�
	void SetSpot(int nx, int ny); // ��ǥ ����
	void SetMspeed(int nMspeed); // �̵��ӵ� ����
	void SetAspeed(int nAspeed); // ���ݼӵ� ����
	void SetRange(int nrange); // ���� ��Ÿ� ����
	void SetSize(int nsize); // �÷��̾� ũ�� ����
	void SetAct(int nAct); // ��Ƽ�� ������ �õ尪 ����
	void SetPct(int nPct); // �нú� ������ �õ尪 �迭 ����
	void SetView(int nview); // �÷��̾� �ü� ����
	void SetHeadRect(); // �÷��̾� �Ӹ� �׸���� ��ǥ ����
	void SetBodyRect(); // �÷��̾� ���� �׸���� ��ǥ ����
	void SetTarget(); // �÷��̾� Ÿ�� ��ǥ ����
	void SetCamera(); // ī�޶� ������Ʈ
	void SetBitMap(HBITMAP nhBitmap, int nindex); // �÷��̾� ��Ʈ�� ����(
	int SetDieRect(float deltaTime); // ��� Rect ����

	// �̵��Լ�
	void MoveLeft(); // �·� �̵� �Լ�
	void MoveRight(); // ��� �̵� �Լ�
	void MoveUp(); // ���� �̵� �Լ�
	void MoveDown(); // �Ʒ��� �̵� �Լ�
	void MoveUpLeft(); // �»�� �밢�� �̵� �Լ�
	void MoveUpRight(); // ���� �밢�� �̵� �Լ�
	void MoveDownLeft(); // ���ϴ� �밢�� �̵� �Լ�
	void MoveDownRight(); // ���ϴ� �밢�� �̵� �Լ�

	// �ΰ���� �Լ�
	void Update(float deltaTime); // ��ġ ������Ʈ
	void Draw(HDC nhDC, HDC nMemDC); // ���� ���� �׸���
	void DMDraw(HDC nhDC, HDC nMemDC, int nCount); // �Ʒ��� ������ �׸���
	void UMDraw(HDC nhDC, HDC nMemDC, int nCount); // ���� ������ �׸���
	void RMDraw(HDC nhDC, HDC nMemDC, int nCount); // ���������� ������ �׸���
	void LMDraw(HDC nhDC, HDC nMemDC, int nCount); // �������� ������ �׸���
	void ULMDraw(HDC nhDC, HDC nMemDC, int nCount); // �»�� �밢�� ������ �׸���
	int ShootTime(float deltaTime); // ���� Ÿ�̸� ������Ʈ


};

