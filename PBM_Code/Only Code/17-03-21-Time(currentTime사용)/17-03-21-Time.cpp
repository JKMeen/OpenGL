#define GLUT_DISABLE_ATEXIT_HACK

#include <Windows.h>
#include <stdio.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <math.h>
#include <string>

#include "./GLUT/freeglut.h"

#pragma comment(lib, "freeglut.lib")

#include "KangGL.h"

struct vec3d {
	double x;
	double y;
	double z;
};

class CMyWindow : public CKangGL {
public:
	CPoint *point;
	CPoint *timepoint;
	vec3d initX; vec3d initV;
	vec3d loc;
	vec3d vel;

	CMyWindow() : CKangGL() {
		point = addPoint();
		timepoint = addPoint();
		addPlane(5, 5, 0.2);
		setCamera(0, 0, 30, 0, 0, 0, 0, 1, 0);
	}

	~CMyWindow() {
		removePoints();
	};

	virtual void init(void) {
		initX.x = initX.y = initX.z = 0.0;
		initV.x = 5.0; initV.y = 10.0; initV.z = 5.0;
		loc = initX;
		vel = initV;
		point->setLocation(loc.x, loc.y, loc.z);
	};

	virtual void clean(void) {

	}

	virtual void doSimulation(double dt, double currentTime) { // time in seconds
		// simulation
		double t = currentTime;

		double angle = 6.28 * t / 60.0;
		timepoint->setLocation(5.0*cos(angle), 5.0*sin(angle), 0);

		loc.x = initX.x + initV.x * t;
		loc.y = initX.y + initV.y * t - 5.0 * t*t;
		loc.z = initX.z + initV.z * t;
		//point->setLocation(loc.x, loc.y, loc.z);
	}
};



int main(int argc, char **argv) {

	CMyWindow* mywin = new CMyWindow();
	GLSetupWith(mywin, &argc, argv, "my simple window");
}