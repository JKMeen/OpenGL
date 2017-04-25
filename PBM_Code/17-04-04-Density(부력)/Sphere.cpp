#include "sphere.h"

// ������ �� ����
void sphere::setRadius(float _radius) {
	radius = _radius;
	mass = radius*radius*radius;
}

float sphere::getRadius(void) {
	return radius;
}


// ��ġ
void sphere::setLocation(const vec3d& vec) {
	loc = vec;
}
vec3d sphere::getLocation(void) {
	return loc;
	//return vec3d(loc.x, loc.y, loc.z);
}

// �ӵ�
void sphere::setVelocity(const vec3d& vec){
	vel = vec;
}
vec3d sphere::getVelocity(void){
	return vel;
}

// ���ӵ�
void sphere::setAcc(const vec3d& vec){
	acc = vec;
}
vec3d sphere::getAcc(void){
	return acc;
}

// �߰� ���ӵ�
void sphere::addAcc(const vec3d& vec){ // ����� addAcc���� �����ϰ� ���ӵ��� �߰�
	acc = acc + vec;
}
void sphere::initAcc(void){ // ����� Ǯ����
	acc.set(0, 0, 0);
}

// �̵� �Լ�
void sphere::move(const vec3d& displacement){
	loc = loc + displacement;
}

// simulation
void sphere::simulate(float dt){
	vel = vel + acc*dt;
	loc = loc + vel*dt;
}


void sphere::visualize(void) {
	glPushMatrix();
	glTranslatef(loc.x, loc.y, loc.z);
	glutWireSphere(radius, 20, 20);
	glPopMatrix();
}