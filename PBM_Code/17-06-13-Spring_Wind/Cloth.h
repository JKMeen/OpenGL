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


public:
	CCloth(int nRow, int nCol, float width, float height, float _mass, float _k);

	void simulate(float dt);
	void visualize();
};