#ifndef SPHERE_YMKANG
#define SPHERE_YMKANG

#include "./GLUT/freeglut.h"
#include "vec3d.h"

class sphere {
public:
	float radius; // ������
	float mass;   // ����
	bool blackhole; // ��Ȧ
	float angle;  // ȸ�� �ӵ�
	vec3d loc;    // ��ġ
	vec3d vel;    // �ӵ�
	vec3d acc;    // ���ӵ�
	vec3d pVel;   // ��� �ӵ�
	vec3d pAcc;   // ��� ���ӵ�
	vec3d color;  // ����

public:
	sphere() : // ������
		mass(1), radius(1), blackhole(false), angle(30),
		loc(vec3d(0, 0, 0)), vel(vec3d(0, 0, 0)), acc(vec3d(0, 0, 0)) {}

	sphere(const vec3d& _loc, float _radius) : // �Ķ���͸� �� ���
		loc(_loc), radius(_radius), mass(_radius*_radius*_radius), angle(30),
		blackhole(false), vel(vec3d(0, 0, 0)), acc(vec3d(0, 0, 0)) {}

	void setRadius(float _radius);
	float getRadius(void);

	void setColor(vec3d _color);
	vec3d getColor(void);

	void setAngle(float _angle);

	void setMass(float _mass);

	// ��ġ // vec�� �ٲ� �ʿ䰡 ���� ������ const(���)�� �޾Ƽ� ����
	void setLocation(const vec3d& vec);
	vec3d getLocation(void);

	// �ӵ�
	void setVelocity(const vec3d& vec);
	vec3d getVelocity(void);

	// ���ӵ�
	void setAcc(const vec3d& vec);
	vec3d getAcc(void);

	// �߰� ���ӵ�
	void addAcc(const vec3d& vec); // ����� addAcc���� �����ϰ� ���ӵ��� �߰�
	void initAcc(void); // ����� Ǯ����

	// ��ü �̵� �Լ�
	void move(const vec3d& displacement); // adisplacement ���̸� ������ �̵�

	// ��ü ���� �Լ�
	void rotate(const float& _angle);

	// simulation (����)
	void simulate(float dt);

	// ����� �׸�
	void visualize(void);
};
#endif