#ifndef _hover_ymkang
#define _hover_ymkang

#include "vec3d.h"

#define NENGINES 4

class Hover{
	vec3d color;   // 색
	vec3d loc;     // 위치
	vec3d vel;     // 속도
	vec3d acc;     // 가속도
	float mass;    // 질량

	// 2차원에서 스칼라로 표현되기 때문에 vec3d가 아닌 float형
	float angle;   // 각도
	float aVel;    // 각 속도
	float aAcc;    // 각 가속도
	float I; // 회전 질량(Inertia)

	bool engine[NENGINES]; // 엔진 두 개
	vec3d force[NENGINES]; // 엔진 파워
	vec3d r[NENGINES]; // 각각의 반지름(?) 위치

	vec3d localToGlobal(vec3d l); // 외적

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