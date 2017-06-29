#include "cloth.h"
#include "./GLUT/freeglut.h"
#include <math.h>
#include <stdio.h>
#pragma comment(lib, "freeglut.lib")

CCloth::CCloth(int nRow, int nCol, float width, float height, float _mass, float _k) :
w(nCol), h(nRow)
{
	nPart = w * h;
	loc = new vec3d[nPart];
	vel = new vec3d[nPart];
	force = new vec3d[nPart];
	normal = new vec3d[nPart];

	mass = new float[nPart];

	float xStep = width / (w - 1);
	float yStep = height / (h - 1);
	for (int i = 0; i < nPart; i++) {
		float x = (i % w)*xStep;
		float y = (i / w)*yStep;
		loc[i].set(x, 5, y);
		vel[i].set(0, 0, 0);
		force[i].set(0, 0, 0);
		normal[i].set(0, 1, 0);
		mass[i] = _mass / nPart;
	}

	// springs....
	nHSpring = (w - 1)*h;
	nVSpring = (h - 1)*w;
	nDSpring = (w - 1)*(h - 1) * 2;
	nSpring = nHSpring + nVSpring + nDSpring;

	spring = new CSpring[nSpring];

	// horizontal springs
	for (int i = 0; i < nHSpring; i++) {
		// which row
		int col = i % (w - 1);
		int row = i / (w - 1);
		spring[i].i = row*w + col;
		spring[i].j = spring[i].i + 1;
		spring[i].l0 = xStep;
		spring[i].k = _k / xStep;
	}
	// vertical springs
	for (int i = 0; i < nVSpring; i++) {
		// which row
		int col = i % w;
		int row = i / w;
		int idx = i + nHSpring;
		spring[idx].i = row*w + col;
		spring[idx].j = (row + 1)*w + col;
		spring[idx].l0 = yStep;
		spring[idx].k = _k / yStep;
	}

	// diagonal springs
	float l0 = sqrt(xStep*xStep + yStep*yStep);
	for (int i = 0; i < nDSpring / 2; i++) {
		// which row
		int col = i % (w - 1);
		int row = i / (w - 1);
		int idx = i * 2 + nHSpring + nVSpring;
		spring[idx].i = row*w + col;
		spring[idx].j = (row + 1)*w + col + 1;
		spring[idx + 1].i = (row + 1)*w + col;
		spring[idx + 1].j = row*w + col + 1;
		spring[idx].l0 = l0;
		spring[idx].k = _k / l0;
		spring[idx + 1].l0 = l0;
		spring[idx + 1].k = _k / l0;
	}

}

void CCloth::simulate(float dt) {

	// init force and set gravity
	for (int i = 0; i < nPart; i++) {
		force[i].set(0, 0, 0);
		// gravity
		//force[i] = mass[i] * vec3d(0, -10.0, 0);
	}

	// spring force
	for (int i = 0; i < nSpring; i++) {
		int p1 = spring[i].i;
		int p2 = spring[i].j;
		// f1 = k * d * (p2-p1)/|p2-p1|
		// f1 = spring constant * stretched length * direction
		vec3d dir = loc[p2] - loc[p1];
		float d = dir.len() - spring[i].l0;

		vec3d f1 = spring[i].k * d * dir.getNormalized();
		force[p1] = force[p1] + f1;
		force[p2] = force[p2] - f1;
	}

	// damping for each spring
	float dampingCoeff = 0.01;
	for (int i = 0; i < nSpring; i++) {
		int p1 = spring[i].i;
		int p2 = spring[i].j;
		vec3d v1 = vel[p1];
		vec3d v2 = vel[p2];
		vec3d vRel = v1 - v2;
		vec3d dir = loc[p2] - loc[p1];
		dir.normalize();

		vec3d F_damp = -dampingCoeff * dot(vRel, dir)*dir;
		force[p1] = force[p1] + F_damp;
		force[p2] = force[p2] - F_damp;
	}


	// wind drag and lift
	static float angle = 0.0f;
	//angle += 0.001;
	vec3d wind = vec3d(cos(angle) * 50, 0, sin(angle) * 50);
	float dragCoeff = 0.00001;
	float liftCoeff = 0.0001;
	for (int i = 0; i < nPart; i++) {
		vec3d relWind = wind - vel[i];
		vec3d windDir = relWind.getNormalized();
		float DOT = dot(relWind, normal[i]);				// dot : º¤ÅÍ ³»Àû
		vec3d dragForce = dragCoeff * fabs(DOT) * windDir;

		float sign = DOT > 0 ? 1.0 : -1.0;
		float liftMagnitude = sign * cross(relWind, normal[i]).len();
		vec3d liftForce = liftCoeff * liftMagnitude * normal[i];

		force[i] = force[i] + dragForce + liftForce;
	}

	force[0].set(0, 0, 0);
	//force[w * (h - 1)].set(0, 0, 0);

	// integration 
	for (int i = 0; i < nPart; i++) {
		vel[i] = vel[i] + (force[i] / mass[i])*dt;
		loc[i] = loc[i] + vel[i] * dt;
	}
}

void CCloth::visualize() {

	for (int i = 0; i < nPart; i++) normal[i].set(0, 0, 0);

	for (int i = 0; i < w - 1; i++) {
		for (int j = 0; j < h - 1; j++) {
			int p0 = i + j*w;
			int p1 = i + (j + 1)*w;
			int p2 = 1 + i + (j + 1)*w;
			int p3 = 1 + i + j*w;
			vec3d v1 = loc[p1] - loc[p0];
			vec3d v2 = loc[p2] - loc[p0];
			vec3d v3 = loc[p3] - loc[p0];
			vec3d n = cross(v1, v2);
			normal[p0] = normal[p0] + n;
			normal[p1] = normal[p1] + n;
			normal[p2] = normal[p2] + n;
			n = cross(v2, v3);
			normal[p0] = normal[p0] + n;
			normal[p2] = normal[p2] + n;
			normal[p3] = normal[p3] + n;
		}
	}
	for (int i = 0; i < nPart; i++) normal[i].normalize();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	for (int i = 0; i < w - 1; i++) {
		for (int j = 0; j < h - 1; j++) {
			int p0 = i + j*w;
			int p1 = i + (j + 1)*w;
			int p2 = 1 + i + (j + 1)*w;
			int p3 = 1 + i + j*w;
			glNormal3f(normal[p0].x, normal[p0].y, normal[p0].z);
			glVertex3f(loc[p0].x, loc[p0].y, loc[p0].z);
			glNormal3f(normal[p1].x, normal[p1].y, normal[p1].z);
			glVertex3f(loc[p1].x, loc[p1].y, loc[p1].z);
			glNormal3f(normal[p2].x, normal[p2].y, normal[p2].z);
			glVertex3f(loc[p2].x, loc[p2].y, loc[p2].z);
			glNormal3f(normal[p3].x, normal[p3].y, normal[p3].z);
			glVertex3f(loc[p3].x, loc[p3].y, loc[p3].z);
		}
	}
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	for (int i = 0; i < w - 1; i++) {
		for (int j = 0; j < h - 1; j++) {
			int p0 = i + j*w;
			int p1 = i + (j + 1)*w;
			int p2 = 1 + i + (j + 1)*w;
			int p3 = 1 + i + j*w;
			glNormal3f(-normal[p3].x, -normal[p3].y, -normal[p3].z);
			glVertex3f(loc[p3].x, loc[p3].y, loc[p3].z);
			glNormal3f(-normal[p2].x, -normal[p2].y, -normal[p2].z);
			glVertex3f(loc[p2].x, loc[p2].y, loc[p2].z);
			glNormal3f(-normal[p1].x, -normal[p1].y, -normal[p1].z);
			glVertex3f(loc[p1].x, loc[p1].y, loc[p1].z);
			glNormal3f(-normal[p0].x, -normal[p0].y, -normal[p0].z);
			glVertex3f(loc[p0].x, loc[p0].y, loc[p0].z);
		}
	}
	glEnd();

}