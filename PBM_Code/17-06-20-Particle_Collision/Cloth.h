#pragma once
#include "vec3d.h"

class CSpring {
public:
	int i;
	int j;
	float l0;
	float k;
};

class CCloth {

public:
	int w;
	int h;

	int nPart; // number of particles = w*h
	int nSpring; // H+V+D springs
	int nHSpring;
	int nVSpring;
	int nDSpring;

	CSpring *spring;
	vec3d *loc; // w * h locations
	vec3d *vel; // w * h velocities
	vec3d *force; // w * h forces
	vec3d *normal;
	float *mass; // w * h masses
	vec3d *color;


public:
	CCloth() {}	// 상속을 위해 default 생성자
	CCloth(int nRow, int nCol, float width, float height, float _mass, float _k);

	void simulate(float dt);
	virtual void visualize();	// 오버라이딩을 위해 virtual
};


class CConfetti : public CCloth {

public:
	CConfetti(int nRow, int nCol, float width, float height, float _mass, float _k);

	virtual void visualize();
};