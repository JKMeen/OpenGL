#ifndef SPHERE_YMKANG
#define SPHERE_YMKANG

#include "./GLUT/freeglut.h"
#include "vec3d.h"

class sphere {
public:
	float radius; // 반지름
	float mass;   // 질량
	bool blackhole; // 블랙홀
	float angle;  // 회전 속도
	vec3d loc;    // 위치
	vec3d vel;    // 속도
	vec3d acc;    // 가속도
	vec3d pVel;   // 평균 속도
	vec3d pAcc;   // 평균 가속도
	vec3d color;  // 색상

public:
	sphere() : // 생성자
		mass(1), radius(1), blackhole(false), angle(30),
		loc(vec3d(0, 0, 0)), vel(vec3d(0, 0, 0)), acc(vec3d(0, 0, 0)) {}

	sphere(const vec3d& _loc, float _radius) : // 파라미터를 준 경우
		loc(_loc), radius(_radius), mass(_radius*_radius*_radius), angle(30),
		blackhole(false), vel(vec3d(0, 0, 0)), acc(vec3d(0, 0, 0)) {}

	void setRadius(float _radius);
	float getRadius(void);

	void setColor(vec3d _color);
	vec3d getColor(void);

	void setAngle(float _angle);

	void setMass(float _mass);

	// 위치 // vec는 바뀔 필요가 없기 때문에 const(상수)로 받아서 설정
	void setLocation(const vec3d& vec);
	vec3d getLocation(void);

	// 속도
	void setVelocity(const vec3d& vec);
	vec3d getVelocity(void);

	// 가속도
	void setAcc(const vec3d& vec);
	vec3d getAcc(void);

	// 추가 가속도
	void addAcc(const vec3d& vec); // 백업은 addAcc에서 설정하고 가속도를 추가
	void initAcc(void); // 백업을 풀어줌

	// 구체 이동 함수
	void move(const vec3d& displacement); // adisplacement 차이를 가지고 이동

	// 구체 자전 함수
	void rotate(const float& _angle);

	// simulation (동작)
	void simulate(float dt);

	// 모양을 그림
	void visualize(void);
};
#endif