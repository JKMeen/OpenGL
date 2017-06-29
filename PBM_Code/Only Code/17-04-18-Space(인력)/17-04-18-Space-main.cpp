#define GLUT_DISABLE_ATEXIT_HACK

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include "./GLUT/freeglut.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "freeglut.lib")

#include "KangGL.h"
#include "vec3d.h"
#include "sphere.h"

double rand(double minV, double maxV) {
	double interval = maxV - minV;
	return minV + interval * ((rand() % 10001) / 10000.0);
}

#define NSPHERES 200

class CMyWindow : public CKangGL {
public:
	sphere *sphere[NSPHERES];

	CMyWindow() : CKangGL() {
		for (int i = 0; i<NSPHERES; i++) sphere[i] = addSphere();
		addPlane(50, 50, 5);
		setCamera(200, 200, 200, 0, 0, 0, 0, 1, 0);
	}
	~CMyWindow() {
		removeSpheres();
	};

	virtual void init(void) {
		for (int i = 0; i < NSPHERES; i++) {
			sphere[i]->setLocation(vec3d(rand(-100, 100), 0, rand(-100, 100)));
			sphere[i]->setVelocity(vec3d(0, 0, 0));
			sphere[i]->setAcc(vec3d(0, 0, 0));
			sphere[i]->setRadius(rand(1.0, 3.0));
		}
	};

	virtual void clean(void) {

	}

	virtual void doSimulation(double dt, double currentTime) { // time in seconds

		float G = 10.0;
		for (int i = 0; i < NSPHERES; i++){
			for (int j = i+1; j < NSPHERES; j++){
				vec3d xi = sphere[i]->getLocation();
				vec3d xj = sphere[j]->getLocation();
				vec3d xij = xj - xi; // xi에서 xj로 가는 벡터

				float mi = sphere[i]->mass;
				float mj = sphere[i]->mass;
				float M = mi + mj; // total m

				// len : 거리를 잴 때 사용 / lenSquare : 거리 제곱
				float len = xij.len(); 

				// 반지름
				float ri = sphere[i]->getRadius();
				float rj = sphere[j]->getRadius();
				float R = ri + rj;

				xij.normalize();

				// collision (R(반지름) 이하로 접근 못하게 만들어줌)
				if (len < R) {
					len = R;
					float d = R - len;
					sphere[i]->move(-(mj*d / M)*xij);
					sphere[j]->move(+(mj*d / M)*xij);

					// is sphere i trying to approach?
					vec3d vi = sphere[i]->getVelocity();
					vec3d vj = sphere[j]->getVelocity();
					vec3d v_rel = vi - vj; // 상대 속도

					// 이 양만큼 뚫고 들어가려 함
					// approaching : 스칼라 값
					float approaching = dot(v_rel, xij); // dot : 내적 / cross : 외적
					if (approaching > 0){
						vec3d appVel = approaching*xij;
						sphere[i]->setVelocity(vi - appVel);
						sphere[j]->setVelocity(vj + appVel);
					}
				}

				// f1 = G * m1*m2 / r² * (단위벡터)X12 // 스칼라 값
				vec3d f = (G*mi*mj / (len*len))*xij;
					
				sphere[i]->addAcc(f / mi);
				sphere[j]->addAcc(f / (-mj)); // -f/mj
			}
		}
		// 공끼리 충돌 감지를 해주면 총알 처럼 날라가지 않는다.

		// simulate
		for (int i = 0; i < NSPHERES; i++){
			sphere[i]->simulate(dt); // 시뮬레이션
			sphere[i]->initAcc(); // 가속 초기화해야함
		}
	}
};



int main(int argc, char **argv) {

	CMyWindow* mywin = new CMyWindow();
	GLSetupWith(mywin, &argc, argv, "my simple window");
}