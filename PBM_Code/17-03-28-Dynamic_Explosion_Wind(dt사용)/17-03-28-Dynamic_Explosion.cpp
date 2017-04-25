#define GLUT_DISABLE_ATEXIT_HACK

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include "./GLUT/freeglut.h"
#include <math.h>
#include <stdio.h>
#pragma comment(lib, "freeglut.lib")

#include "KangGL.h"


struct vec3d {
	double x;
	double y;
	double z;

public:
	vec3d() : x(0), y(0), z(0) {}
	vec3d(double x, double y, double z) { this->x = x; this->y = y; this->z = z; }
	void set(double x, double y, double z) { this->x = x; this->y = y; this->z = z; }
};

inline vec3d operator*(double t, const vec3d& v) {
	return vec3d(t*v.x, t*v.y, t*v.z);
}
inline vec3d operator*(const vec3d& v, double t) {
	return vec3d(t*v.x, t*v.y, t*v.z);
}
inline vec3d operator+(const vec3d& v1, const vec3d& v2) {
	return vec3d(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
inline vec3d operator-(const vec3d& v1, const vec3d& v2) {
	return vec3d(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}


class CMyWindow : public CKangGL {
public:
	CPoint *point;
	vec3d initX; vec3d initV;
	vec3d loc;
	vec3d vel;

	////////// new code ///////////////
	CPoint *pointD;
	vec3d locD;
	vec3d velD;
	///////////////////////////////////


	CMyWindow() : CKangGL() {
		point = addPoint();
		pointD = addPoint();
		addPlane(50, 50, 0.2);
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

		////// new code
		locD.set(0, 0, 0);
		velD.set(5, 10, 5);
		pointD->setLocation(locD.x, locD.y, locD.z);
		///////
	};

	virtual void clean(void) {

	}

	virtual void doSimulation(double dt, double currentTime) { // time in seconds
		// simulation
		double t = currentTime;
		loc.x = initX.x + initV.x * t;
		loc.y = initX.y + initV.y * t - 5.0 * t*t;
		loc.z = initX.z + initV.z * t;
		point->setLocation(loc.x, loc.y, loc.z);

		/////////////// new code for pointD
		vec3d acc(0, -10, 0);
		velD = velD + acc * dt;
		locD = locD + velD * dt;
		pointD->setLocation(locD.x, locD.y, locD.z);
		/////////////
	}
};



int main(int argc, char **argv) {

	CMyWindow* mywin = new CMyWindow();
	GLSetupWith(mywin, &argc, argv, "my simple window");
}