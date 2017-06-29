#include "Hover.h"
#include "./GLUT/freeglut.h"
#pragma comment(lib, "freeglut.lib")

Hover::Hover() : 
	loc(vec3d(0, 0, 0)), vel(vec3d(0, 0, 0)), acc(vec3d(0, 0, 0)), 
	mass(1.0), I(1.0), angle(3.14/1.0), aVel(0), aAcc(0)
{
	engine[0] = engine[1] = engine[2] = engine[3] = false;
	force[0] = vec3d(0, 1, 0);
	force[1] = vec3d(0, 1, 0);
	force[2] = vec3d(1, 0, 0);
	force[3] = vec3d(-1, 0, 0);
	r[0] = vec3d(-1, -1, 0);
	r[1] = vec3d(1, -1, 0);
	r[2] = vec3d(-1, 1, 0);
	r[3] = vec3d(1, 1, 0);
}

// 엔진 점화
void Hover::switchEngine(int idx){
	engine[idx] = engine[idx] ? false : true;
}

vec3d Hover::localToGlobal(vec3d l){ // 외적
	float c = cos(angle);
	float s = sin(angle);

	vec3d res(0, 0, 0);

	// (c  -s)
	// (s   c)
	res.x = c*l.x - s*l.y;
	res.y = s*l.x + c*l.y;

	return res;
}

void Hover::simulaste(float dt){
	acc.set(0, 0, 0);
	aAcc = 0;

	vec3d torque(0, 0, 0);
	for (int i = 0; i < NENGINES; i++){
		vec3d f = localToGlobal(force[i]);
		//vec3d globalR = localToGlobal(r[i]); // 변위 벡터
		if (engine[i]) {
			// 선 운동
			acc = acc + f / mass; // 각각의 엔진이 켜져있으면 엔진의 힘이 가해짐

			// 회전 운동
			//torque = cross(globalR, f); // torque는 z값만 나옴
			torque = cross(r[i], force[i]); // globalR, f를 넣는 것과 같음
			torque.z; // 회전에서의 힘
			aAcc = aAcc + torque.z / I;
		}
	}

	// 선운동
	vel = vel + acc * dt;
	loc = loc + vel * dt;

	// 회전운동
	aVel = aVel + aAcc * dt;
	angle = angle + aVel * dt;
}

void Hover::visualize(){
	float degree = angle * 180.0 / 3.14;

	glPushMatrix();

	glTranslatef(loc[0], loc[1], loc[2]);
	glRotatef(degree, 0, 0, 1);

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex2f(-1, 1);
	glVertex2f(-1, -1);
	glVertex2f(1, -1);
	glVertex2f(1, 1);
	glEnd();

	// 점화통1 생성(콘)
	for (int i = 0; i < NENGINES; i++){
		if (engine[i]){
			glPushMatrix();
			glColor3f(1, 0, 0);
			glTranslatef(r[i].x, r[i].y, r[i].z);
			glutWireSphere(0.1, 5, 5);
			glPopMatrix();
		}
	}

	glPopMatrix();
}