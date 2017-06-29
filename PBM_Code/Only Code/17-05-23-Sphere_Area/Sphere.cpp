#include "sphere.h"

// 반지름 및 질량
void sphere::setRadius(float _radius) {
	radius = _radius;
	mass = radius*radius*radius;
}

void sphere::setMass(float _mass){
	mass = _mass;
}

float sphere::getRadius(void) {
	return radius;
}

// 색상
void sphere::setColor(vec3d _color){
	color = _color;
}

vec3d sphere::getColor(void){
	return color;
}

// 자전
void sphere::setAngle(float _angle){
	angle = _angle;
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

// 자전 함수
void sphere::rotate(const float& _angle){
	//glRotatef(angle+_angle, 0, 1, 0);
}

// simulation
void sphere::simulate(float dt){
	vel = vel + acc*dt;
	loc = loc + vel*dt;
}

void sphere::visualize(void) {
	glPushMatrix();
	glLineWidth(0.1);
	glTranslatef(loc.x, loc.y, loc.z);
	glColor3f(color.x, color.y, color.z);
	glutWireSphere(radius, 10, 10);
	//glutSolidSphere(radius, 20, 20);
	glPopMatrix();
}