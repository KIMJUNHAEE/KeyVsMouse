#include "TEARS.h"
#include <stdio.h>
#include <math.h>

void TEARS::SetTearRect() { // ���� RECT ���� �Լ�



	TearRect.right = TearRect.left + width + size;
	TearRect.bottom = TearRect.top + height + size;

};

void TEARS::Shoot(int Px, int Py, int Tx, int Ty, HDC nhDC, HDC nMemDC) { // ���� �߻� �Լ�
	
	float dx = Tx - Px;
	float dy = Ty - Py;

	float length = sqrt(dx * dx + dy * dy);


}; 

