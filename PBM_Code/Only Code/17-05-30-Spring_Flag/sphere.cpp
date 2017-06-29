#include "sphere.h"

void sphere::setRadius(float _radius) {
	
	radius = _radius;
	mass = radius*radius*radius;
}

float sphere::getRadius(void) {
	
	return radius;
}

void sphere::setLocation(const vec3d& vec) {
	center = vec;
}

vec3d sphere::getLocation(void) {
	return vec3d(center.x, center.y, center.z);
}

void sphere::moveLocation(const vec3d& displacement) {
	center = center + displacement;
}

void sphere::visualize(void) {
	glPushMatrix();
	glTranslatef(center.x, center.y, center.z);
	glutSolidSphere(radius, 20, 20);
	glPopMatrix();
}


void sphere::setVelocity(const vec3d& vec) {
	velocity = vec;
}
vec3d sphere::getVelocity(void) {
	return velocity;
}

void sphere::setAcc(vec3d acc) {
	pAcc = acceleration;
	acceleration = acc;
}

void sphere::initAcc() {
	accBackup = false;
	acceleration.set(0, 0, 0);
}
void sphere::addAcc(vec3d acc) {
	if (!accBackup) {
		pAcc = acceleration;
		accBackup = true;		
	}
	acceleration = acceleration + acc;
}

void sphere::simulate(float dt) {
	pVel = velocity;
	velocity = velocity + 0.5 * dt * (pAcc + acceleration);
	center = center + 0.5 * dt * (velocity + pVel);
	accBackup = false;
}