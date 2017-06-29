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

#define NSPHERES 50

double bounce = 0.5; // 탄성
double friction = 0.1; // 마찰력
double density = 2.0; // 부력
double dragCoeff = 1.5; // 항력 (액체 속을 움직이는 물체가 유체에서 받는 항력)

bool bExploded = false;
double ExplosionHeight = 3.0;

double rand(double minV, double maxV) {
	double interval = maxV - minV;
	return minV + interval * ((rand() % 10001) / 10000.0);
}

class CMyWindow : public CKangGL {
public:
	sphere *sphere[NSPHERES];

	CMyWindow() : CKangGL() {
		for (int i = 0; i < NSPHERES; i++)
			sphere[i] = addSphere();
		addPlane(5, 5, 0.2);
		//setCamera(5, 5, 10, 0, 0, 0, 0, 1, 0);
		setCamera(0, 0, 30, 0, 0, 0, 0, 1, 0);
	}
	~CMyWindow() {
		removePoints();
	};

	virtual void init(void) {
		for (int i = 0; i < NSPHERES; i++){
			sphere[i]->setLocation(vec3d(0, 10, 0));
			sphere[i]->setVelocity(vec3d(rand(-5, 5), rand(0, -6), rand(-5, 5)));
			sphere[i]->setAcc(vec3d(0, -10, 0)); // 시작 위치
			sphere[i]->setRadius(rand(0.1, 1));
		}
	};

	virtual void clean(void) {

	}

	virtual void doSimulation(double dt, double currentTime) { // time in seconds
		for (int i = 0; i < NSPHERES; i++) {
		collisionHandling(i);
		// buoyant and drag force
		vec3d buoy(0, 0, 0);
		vec3d drag(0, 0, 0);

		if (sphere[i]->getLocation().y < 0){
		buoy = -density * vec3d(0, -10, 0); // 중력 가속도
		drag = -dragCoeff * sphere[i]->getVelocity(); //
		}

		// simulation
		sphere[i]->setAcc(vec3d(0, -10, 0) + buoy + drag / 1); // 1은 질량
		sphere[i]->simulate(dt);
		}
	}

	void collisionHandling(int i){
		float bottom = -5.0;
		float e = 0.75;
		float penetration = sphere[i]->getRadius() - sphere[i]->getLocation().y + bottom;
		if (penetration > 0) // 바닥충돌
			sphere[i]->move(vec3d(0, (1 + e)*penetration, 0));
	}
};



int main(int argc, char **argv) {
	CMyWindow* mywin = new CMyWindow();
	GLSetupWith(mywin, &argc, argv, "my simple window");
}