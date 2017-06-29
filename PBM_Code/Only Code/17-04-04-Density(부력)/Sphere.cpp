#include "sphere.h"

// 반지름 및 질량
void sphere::setRadius(float _radius) {
	radius = _radius;
	mass = radius*radius*radius;
}

float sphere::getRadius(void) {
	return radius;
}


// 위치
void sphere::setLocation(const vec3d& vec) {
	loc = vec;
}
vec3d sphere::getLocation(void) {
	return loc;
	//return vec3d(loc.x, loc.y, loc.z);
}

// 속도
void sphere::setVelocity(const vec3d& vec){
	vel = vec;
}
vec3d sphere::getVelocity(void){
	return vel;
}

// 가속도
void sphere::setAcc(const vec3d& vec){
	acc = vec;
}
vec3d sphere::getAcc(void){
	return acc;
}

// 추가 가속도
void sphere::addAcc(const vec3d& vec){ // 백업은 addAcc에서 설정하고 가속도를 추가
	acc = acc + vec;
}
void sphere::initAcc(void){ // 백업을 풀어줌
	acc.set(0, 0, 0);
}

// 이동 함수
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