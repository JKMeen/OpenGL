#ifndef SPHERE_YMKANG
#define SPHERE_YMKANG

#include "./GLUT/freeglut.h"
#include "vec3d.h"

class sphere {
public:
	float radius; // ������
	float mass; // ����
	vec3d loc; // ��ġ
	vec3d vel; // �ӵ�
	vec3d acc; // ���ӵ�
	vec3d pVel; // ��� �ӵ�
	vec3d pAcc; // ��� ���ӵ�

public:
	sphere() : // ������
		mass(1), radius(1), 
		loc(vec3d(0, 0, 0)), vel(vec3d(0, 0, 0)), acc(vec3d(0, 0, 0)) {}

	sphere(const vec3d& _loc, float _radius) : // �Ķ���͸� �� ���
		loc(_loc), radius(_radius), mass(_radius*_radius*_radius),
		vel(vec3d(0, 0, 0)), acc(vec3d(0, 0, 0)) {}

	void setRadius(float _radius);
	float getRadius(void);

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

	// simulation
	void simulate(float dt);

	void visualize(void);
};
#endif