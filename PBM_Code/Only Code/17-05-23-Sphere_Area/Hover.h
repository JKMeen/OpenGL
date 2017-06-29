#ifndef _hover_ymkang
#define _hover_ymkang

#include "vec3d.h"

#define NENGINES 4

class Hover{
	vec3d color;   // ��
	vec3d loc;     // ��ġ
	vec3d vel;     // �ӵ�
	vec3d acc;     // ���ӵ�
	float mass;    // ����

	// 2�������� ��Į��� ǥ���Ǳ� ������ vec3d�� �ƴ� float��
	float angle;   // ����
	float aVel;    // �� �ӵ�
	float aAcc;    // �� ���ӵ�
	float I; // ȸ�� ����(Inertia)

	bool engine[NENGINES]; // ���� �� ��
	vec3d force[NENGINES]; // ���� �Ŀ�
	vec3d r[NENGINES]; // ������ ������(?) ��ġ

	vec3d localToGlobal(vec3d l); // ����

public:
	Hover();
	vec3d getLoc(){
		return loc;
	}
	void switchEngine(int idx);
	void simulaste(float dt);
	void visualize();
};

#endif