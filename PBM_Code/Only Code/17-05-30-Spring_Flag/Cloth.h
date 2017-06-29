#pragma once
#include "vec3d.h"

class CSpring {
public:
	int i;		// 입자들의 열 번호
	int j;		// 입자들의 행 번호
	float l0;	// 스프링 본래의 길이
	float k;	// 스프링 강도			// 스프링이 줄어들면 강도는 2배가 됨
	int t;		// 스프링이 존재하는지
};

class CCloth {
	int w;		// 옷감 가로 점 개수
	int h;		// 옷감 세로 점 개수

	int nPart;		// 점의 개수				// number of particles = w*h
	int nSpring;	// 스프링의 개수			// H+V+D springs
	int nHSpring;	// 수평 스프링 h * (w-1)
	int nVSpring;	// 수직 스프링 w * (h-1)
	int nDSpring;	// 대각 스프링 (h-1) * (w-1) * 2

public:
	CSpring *spring;// 스프링 생성
	vec3d *loc;		// 입자의 위치	// w * h locations
	vec3d *vel;		// 입자의 속도	// w * h velocities
	//vec3d *acc;	// 가속도
	vec3d *force;	// 입자의 힘	// w * h forces
	float *mass;	// 입자의 질량	// w * h masses

	// 옷감 생성자
	CCloth(int nRow, int nCol, float width, float height, float _mass, float _k);

	void simulate(float dt);
	void visualize();
};