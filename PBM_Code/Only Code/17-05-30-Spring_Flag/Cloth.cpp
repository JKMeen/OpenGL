#include "Cloth.h"
#include "./GLUT/freeglut.h"
#include <math.h>
#include <stdio.h>
#pragma comment(lib, "freeglut.lib")

double rand(double minV, double maxV) {
	double interval = maxV - minV;
	return minV + interval * ((rand() % 10001) / 10000.0);
}

CCloth::CCloth(int nRow, int nCol, float width, float height, float _mass, float _k) :
w(nCol), h(nRow)
{
	nPart = w * h;				// 파티클 개수
	loc = new vec3d[nPart];		// 파티클 위치
	vel = new vec3d[nPart];		// 파티클 속도
	force = new vec3d[nPart];	// 파티클 힘
	mass = new float[nPart];	// 파티클 징량

	float xStep = width / (w - 1);		// x의 구간 길이 // 사이구간이 w-1이기 때문
	float yStep = height / (h - 1);		// y의 구간 길이

	for (int i = 0; i < nPart; i++) {
		float x = (i % w)*xStep;		// 구간에 맞춰 점을 설정
		float y = (i / w)*yStep;		// 구간에 맞춰 점을 설정
		//acc[i].set(0, 0, 0);			// 각 점의 가속도 설정
		loc[i].set(x, 50, y);			// 각 점의 위치 설정
		vel[i].set(0, 0, 0);			// 각 점의 속도 설정
		force[i].set(0, 0, 0);			// 각 점의 힘 설정

		mass[i] = _mass / nPart;		// 각 점의 질량 설정
	}

	// springs....
	nHSpring = (w - 1)*h;						// 가로 스프링의 개수
	nVSpring = (h - 1)*w;						// 세로 스프링의 개수
	nDSpring = (w - 1)*(h - 1) * 2;				// 대각 스프링의 개수
	nSpring = nHSpring + nVSpring + nDSpring;	// 전체 스프링의 개수

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
		spring[i].t = 0;
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
		spring[idx].t = 0;
	}

	// diagonal springs
	int l0 = sqrt(xStep*xStep + yStep*yStep);
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

		spring[idx].t = 0;
		spring[idx + 1].t = 0;
	}

}

void CCloth::simulate(float dt) {
	for (int i = 0; i < nPart; i++){	// 점의 개수만큼
		force[i].set(0, 0, 0);

		// gravity (중력)
		// wind
		force[i] = mass[i] * vec3d(30, rand(-10, 10), rand(-10, 10)); // 질량 * 속도
	}


	float dampingCoeff = 0.01; // 댐프 저항

	// spring force (스프링 힘)
	for (int i = 0; i < nSpring; i++){
		if (spring[i].t <= 1000){
			// p1과 p2를 연결하는 스프링
			int p1 = spring[i].i;
			int p2 = spring[i].j;

			// f1 = -k * d * (p2 - p1)/|p2-p1| 
			// 스프링 강도 * 늘어난 길이 * 방향
			vec3d dir = loc[p2] - loc[p1]; // p1에서 p2의 방향
			float d = dir.len() - spring[i].l0; // 점의 거리 - 스프링의 길이

			vec3d f1 = spring[i].k * d * dir.getNormalized();
			force[p1] = force[p1] + f1;
			force[p2] = force[p2] - f1;	// p1과 반대 방향으로 힘이 주어짐
			if (d > 0.6)
				spring[i].t++;


			// drag force (댐프 저항)
			vec3d v1 = vel[p1];		// p1 스프링의 속도
			vec3d v2 = vel[p2];		// p2 스프링의 속도
			vec3d vRel = v1 - v2;	// 상대 속도
			vec3d F_damp = -vRel * dampingCoeff; // 항력 = -상대속도 * 댐프 저항력

			force[p1] = force[p1] + F_damp;
			force[p2] = force[p2] - F_damp;
		}
	}
	for (int i = 0; i < nPart; i++){
		if (i % 20 == 0)
			force[i].set(0, 0, 0);
	}

	// intefration (적분)
	for (int i = 0; i < nPart; i++){
		vel[i] = vel[i] + (force[i] / mass[i]) * dt; // 속도 + 힘/질량 * dt
		loc[i] = loc[i] + vel[i] * dt;
	}
}

void CCloth::visualize() {
	glColor3f(1, 0, 0);
	glPointSize(3);
	glBegin(GL_POINTS);
	for (int i = 0; i < nPart; i++) {
		glVertex3f(loc[i].x, loc[i].y, loc[i].z);
	}
	glEnd();
	glPointSize(0);

	glBegin(GL_LINES);
	for (int i = 0; i < nSpring; i++) {
		if (spring[i].t <= 1000){
			int idx1 = spring[i].i;
			int idx2 = spring[i].j;
			glVertex3f(loc[idx1].x, loc[idx1].y, loc[idx1].z);
			glVertex3f(loc[idx2].x, loc[idx2].y, loc[idx2].z);
		}
	}
	glEnd();
	glColor3f(0, 0, 1);
}