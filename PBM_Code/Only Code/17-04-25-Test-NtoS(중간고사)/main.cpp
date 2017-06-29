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

void mode(sphere* sphere[], double dt);

double rand(double minV, double maxV) {
	double interval = maxV - minV;
	return minV + interval * ((rand() % 10001) / 10000.0);
}

#define NSPHERES 100

class CMyWindow : public CKangGL {
public:
	sphere *sphere[NSPHERES];

	CMyWindow() : CKangGL() {
		for (int i = 0; i<NSPHERES; i++) sphere[i] = addSphere();
		addPlane(50, 50, 5);
		setCamera(100, 100, 100, 0, 0, 0, 0, 1, 0);
	}
	~CMyWindow() {
		removeSpheres();
	};

	virtual void init(void) {
		for (int i = 0; i < NSPHERES; i++) {
			if (i%2 == 0)
				sphere[i]->setColor(vec3d(1.0, 0.0, 0.0));
			else 
				sphere[i]->setColor(vec3d(0.0, 0.0, 1.0));
			//sphere[i]->setColor(vec3d(rand(0.0, 0.5), rand(0.0, 1.0), rand(0.0, 1.0)));
			sphere[i]->setLocation(vec3d(rand(-50, 50), 0, rand(-50, 50)));
			sphere[i]->setVelocity(vec3d(0, 0, 0));
			sphere[i]->setAcc(vec3d(0, 0, 0));
			sphere[i]->setRadius(rand(1.0, 2.0));
			sphere[i]->setMass(sphere[i]->getRadius()*sphere[i]->getRadius()*sphere[i]->getRadius()*10);
			//sphere[i]->setAngle(rand(10.0, 50.0));
		}
		/*
		sphere[0]->setColor(vec3d(1, 0, 0));
		sphere[0]->setLocation(vec3d(0, 0, 0));
		sphere[0]->setVelocity(vec3d(0, 0, 0));
		sphere[0]->setAcc(vec3d(0, 0, 0));
		sphere[0]->setRadius(3.0);
		sphere[0]->setMass(1000.0);
		sphere[0]->setAngle(60.0);
		
		sphere[NSPHERES]->setColor(vec3d(1, 1, 1));
		sphere[NSPHERES]->setLocation(vec3d(0, 0, 0));
		sphere[NSPHERES]->setVelocity(vec3d(0, 0, 0));
		sphere[NSPHERES]->setAcc(vec3d(0, 0, 0));
		sphere[NSPHERES]->setRadius(200);
		sphere[NSPHERES]->setAngle(60.0);*/
	};

	virtual void clean(void) {

	}

	virtual void doSimulation(double dt, double currentTime) { // time in seconds
		mode(sphere, dt);
	}
};

void mode(sphere* sphere[], double dt){
	float G = 10.0;
	static float angle = 0;
	angle += 0.1;
	for (int i = 0; i < NSPHERES; i++){
		for (int j = i + 1; j < NSPHERES; j++){
			//if (sphere[i]->blackhole != true){
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
				float Ri = ri / R;
				float Rj = rj / R;

				xij.normalize();

				// collision (R(반지름) 이하로 접근 못하게 만들어줌)
				if (len < R) {
					len = R;
					float d = R - len;
					sphere[i]->move(-(mj*d*R / M)*xij);
					sphere[j]->move(+(mj*d*R / M)*xij);

					// is sphere i trying to approach?
					vec3d vi = sphere[i]->getVelocity();
					vec3d vj = sphere[j]->getVelocity();
					vec3d v_rel = vi - vj; // 상대 속도
						// 이 양만큼 뚫고 들어가려 함
					// approaching : 스칼라 값
					float approaching = dot(v_rel, xij); // dot : 내적 / cross : 외적
					if (approaching > 0){
						vec3d appVel = approaching*xij;
						sphere[i]->setVelocity(vi - appVel*1.1);
						sphere[j]->setVelocity(vj + appVel*1.1);
					}
				}

				// f1 = G * m1*m2 / r² * (단위벡터)X12 // 스칼라 값
				if (sphere[i]->getColor().x != sphere[j]->getColor().x){
					vec3d f = (G*mi*mj / (len*len))*xij;
					sphere[i]->addAcc(f / (+mi));
					sphere[j]->addAcc(f / (-mj)); // -f*-/mj
				}
				else {
					vec3d f = (G*mi*mj / (len*len))*xij;
					sphere[i]->addAcc(f / (-mi));
					sphere[j]->addAcc(f / (+mj)); // -f*-/mj
				}
			}
		//}
	}
	// 공끼리 충돌 감지를 해주면 총알 처럼 날라가지 않는다.

	/*
	// BlackHole
	float BlackG = 10.0;
	for (int i = 1; i < NSPHERES; i++){
		//if (sphere[i]->blackhole == false){
		vec3d xi = sphere[i]->getLocation();
		vec3d x0 = sphere[0]->getLocation();
		vec3d xi0 = x0 - xi; // xi에서 블랙홀로 가는 벡터

		float mi = sphere[i]->mass;
		float m0 = sphere[0]->mass;
		float M = mi + m0; // total m

		// len : 거리를 잴 때 사용 / lenSquare : 거리 제곱
		float len = xi0.len();

		// 반지름
		float ri = sphere[i]->getRadius();
		float r0 = sphere[0]->getRadius();
		float R = ri + r0;

		xi0.normalize();

		// collision (R(반지름) 이하로 접근 못하게 만들어줌)
		if (len < R) {
			len = R;
			float d = R - len;
			
			sphere[i]->move(+(m0*d / M)*xi0);
			sphere[0]->move(-(m0*d / M)*xi0);
			sphere[i]->setLocation(vec3d(0, -3, 0));
			
			// is sphere i trying to approach?
			vec3d vi = sphere[i]->getVelocity();
			vec3d v0 = sphere[0]->getVelocity();
			vec3d v_rel = vi - v0; // 상대 속도

			// 이 양만큼 뚫고 들어가려 함
			// approaching : 스칼라 값
			float approaching = dot(v_rel, xi0); // dot : 내적 / cross : 외적
			if (approaching > 0){
				vec3d appVel = approaching*xi0;
				sphere[i]->setVelocity(vi - appVel);
				//sphere[0]->setVelocity(v0 + appVel);
			}
			sphere[i]->blackhole = true;
			sphere[i]->setLocation(sphere[0]->getLocation());
		}

		// f1 = G * m1*m2 / r² * (단위벡터)X12 // 스칼라 값
		vec3d f = (BlackG*mi*m0 / (len*len))*xi0;

		sphere[i]->addAcc(f / mi);
		sphere[0]->addAcc(-f / m0);//f / (-m0)); // -f/mj
	}
	// 공끼리 충돌 감지를 해주면 총알 처럼 날라가지 않는다.

	
	// 범위 지정
	for (int i = 0; i < NSPHERES; i++){
		float mi = sphere[i]->mass;
		float mNSPHERES = sphere[NSPHERES]->mass;
		float M = mi + mNSPHERES; // total m

		//if (sphere[i]->blackhole == false){
		vec3d xi = sphere[i]->getLocation();
		vec3d xNSPHERES = sphere[NSPHERES]->getLocation();
		vec3d xiNSPHERES = xNSPHERES - xi; // xi에서 블랙홀로 가는 벡터

		// len : 거리를 잴 때 사용 / lenSquare : 거리 제곱
		float len = xiNSPHERES.len();

		// 반지름
		float ri = sphere[i]->getRadius();
		float rNSPHERES = sphere[NSPHERES]->getRadius();
		float R = ri + rNSPHERES;

		xiNSPHERES.normalize();

		// collision (R(반지름) 이하로 접근 못하게 만들어줌)
		if (len >= rNSPHERES) {
			//sphere[i]->getLocation().y *= -0.5; // bounce : 탄성
			if (sphere[i]->getVelocity().y <= 0.0){
				sphere[i]->setVelocity(vec3d(0, sphere[i]->getVelocity().y*-0.5, 0));
			}

			if (sphere[i]->getVelocity().x <= 0.0){
				sphere[i]->setVelocity(vec3d(sphere[i]->getVelocity().x*-0.5, 0, 0));
			}

			if (sphere[i]->getVelocity().z <= 0.0){
				sphere[i]->setVelocity(vec3d(0, 0, sphere[i]->getVelocity().z*-0.5));
				//sphere[i]->getVelocity().z *= -0.5;
			}
		}
	}*/


	// simulate
	for (int i = 0; i < NSPHERES; i++){
		sphere[i]->simulate(dt); // 시뮬레이션
		sphere[i]->initAcc(); // 가속 초기화해야함
	}
}

int main(int argc, char **argv) {
	CMyWindow* mywin = new CMyWindow();
	GLSetupWith(mywin, &argc, argv, "my simple window");
}