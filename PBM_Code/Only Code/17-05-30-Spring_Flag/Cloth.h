#pragma once
#include "vec3d.h"

class CSpring {
public:
	int i;		// ���ڵ��� �� ��ȣ
	int j;		// ���ڵ��� �� ��ȣ
	float l0;	// ������ ������ ����
	float k;	// ������ ����			// �������� �پ��� ������ 2�谡 ��
	int t;		// �������� �����ϴ���
};

class CCloth {
	int w;		// �ʰ� ���� �� ����
	int h;		// �ʰ� ���� �� ����

	int nPart;		// ���� ����				// number of particles = w*h
	int nSpring;	// �������� ����			// H+V+D springs
	int nHSpring;	// ���� ������ h * (w-1)
	int nVSpring;	// ���� ������ w * (h-1)
	int nDSpring;	// �밢 ������ (h-1) * (w-1) * 2

public:
	CSpring *spring;// ������ ����
	vec3d *loc;		// ������ ��ġ	// w * h locations
	vec3d *vel;		// ������ �ӵ�	// w * h velocities
	//vec3d *acc;	// ���ӵ�
	vec3d *force;	// ������ ��	// w * h forces
	float *mass;	// ������ ����	// w * h masses

	// �ʰ� ������
	CCloth(int nRow, int nCol, float width, float height, float _mass, float _k);

	void simulate(float dt);
	void visualize();
};