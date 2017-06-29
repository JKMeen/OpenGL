#include "./GLUT/freeglut.h"
#include <math.h>
#include <stdio.h>
#pragma comment(lib, "freeglut.lib")

#include "KangGL.h"
#include "vec3d.h"

/*double rand(double minV, double maxV) {
	double interval = maxV - minV;
	return minV + interval * ((rand() % 10001) / 10000.0);
}*/

class CMyWindow : public CKangGL {
public:
	CMyWindow() : CKangGL() {
		CCloth* myCloth = new CCloth(20, 20, 30, 30, 10, 20);
		addCloth(myCloth);
		addPlane(100, 100, 5);
		setCamera(20, 100, 1, 20, 0, 0, 0, 1, 0);
	}
	~CMyWindow() {

	};

	virtual void init(void) {

	};

	virtual void clean(void) {

	}

	virtual void doSimulation(double dt, double currentTime) { // time in seconds

		if (dt > 0.05) dt = 0.05;

		int iter = 5;

		dt = dt / iter;
		for (int i = 0; i<iter; i++) 
			cloth->simulate(dt);

	}


};



int main(int argc, char **argv) {

	CMyWindow* mywin = new CMyWindow();
	GLSetupWith(mywin, &argc, argv, "Cloth Simulation");
}