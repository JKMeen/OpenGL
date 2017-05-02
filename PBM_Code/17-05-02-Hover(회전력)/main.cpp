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

double rand(double minV, double maxV) {
	double interval = maxV - minV;
	return minV + interval * ((rand() % 10001) / 10000.0);
}

class CMyWindow : public CKangGL {
public:
	Hover *pHover;
	CMyWindow() : CKangGL() {
		addPlane(100, 100, 1);
		pHover = addHover();
		setCamera(pHover->getLoc().x, pHover->getLoc().y, 20, 0, 0, 0, 0, 1, 0);
	}
	~CMyWindow() {
		removeAll();
	};

	virtual void init(void) {
		
	};

	virtual void clean(void) {

	}
	// °¢µµ : 90 - rad2deg(atan2(pHover->getLoc()[0], pHover->getLoc()[1]))
	virtual void doSimulation(double dt, double currentTime) { // time in seconds
		pHover->simulaste(dt);
		setCamera(pHover->getLoc()[0], pHover->getLoc()[1], 50, pHover->getLoc()[0], pHover->getLoc()[1], 0, 0, 1, 0);
	}
};

int main(int argc, char **argv) {
	CMyWindow* mywin = new CMyWindow();
	GLSetupWith(mywin, &argc, argv, "my simple window");
}