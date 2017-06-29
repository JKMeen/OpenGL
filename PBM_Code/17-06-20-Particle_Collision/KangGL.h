#ifndef _TONGMYONG_YMKANG_SIMPLE_GL_2017_
#define _TONGMYONG_YMKANG_SIMPLE_GL_2017_


#include "./GLUT/freeglut.h"
#include <math.h>
#include "cloth.h"
#include "Sphere.h"

#ifdef WIN32   // Windows system specific
#include <windows.h>
#else          // Unix based system specific
#include <sys/time.h>
#endif

#ifdef WIN32
typedef LARGE_INTEGER _timeCountType;
#else
typedef timeval _timeCountType;
#endif

#pragma comment(lib, "freeglut.lib")



class CPlane {
	double w;
	double h;
	double interval;
public:
	void setPlane(double w, double h, double interval) {
		this->w = w;
		this->h = h;
		this->interval = interval;
	}

	void visualize(void) {
		double currentLoc = 0.0;

		glColor3f(0.45, 0.45, 0.45);
		glBegin(GL_LINES);
		while (currentLoc < w) {
			glVertex3f(currentLoc, 0.0, -h);
			glVertex3f(currentLoc, 0.0, h);
			glVertex3f(-currentLoc, 0.0, -h);
			glVertex3f(-currentLoc, 0.0, h);
			currentLoc += interval;
		}
		currentLoc = 0.0;
		while (currentLoc < h) {
			glVertex3f(w, 0.0, currentLoc);
			glVertex3f(-w, 0.0, currentLoc);
			glVertex3f(w, 0.0, -currentLoc);
			glVertex3f(-w, 0.0, -currentLoc);
			currentLoc += interval;
		}
		glEnd();
	}
};



////////////////////////////////
//
// Simple GL Interface
//
// Young-Min Kang
// Tongmyong University

class CKangGL {
	bool bStarted;
	bool bPaused;

public:
	CPlane *plane;
	CCloth *cloth;
	sphere *sphereList[256];
	int nSpheres;

#ifdef WIN32
	_timeCountType frequency; // ticks per seconds (required only on Windows)
#endif
	_timeCountType startCount;

	_timeCountType endCount;
	_timeCountType checkCount;
	_timeCountType tempCount;
	_timeCountType pauseStart;
	_timeCountType pauseEnd;

public:

	double mEx, mEy, mEz; // eye
	double mTx, mTy, mTz; // camera target
	double mUx, mUy, mUz; // camera up vector

	// Constructor and destructor
	CKangGL();
	virtual ~CKangGL();

	// initialization
	virtual void init(void) = 0;
	// clean
	virtual void clean(void) = 0;


	// idle function
	void idle(void);

	// display function
	void display(void);

	virtual void actions(double dt, double currentTime);


	virtual void doSimulation(double dt, double currentTime) = 0;

	// Control Event Handlers
	void start();
	void stop();
	void pause();
	void resume();


	sphere *addSphere(void);
	void removeSpheres(void);
	void addPlane(double w, float h, float interval);
	void addCloth(CCloth *clothObj);
	void setCamera(float x, float y, float z, float tx, float ty, float tz, float ux, float uy, float uz);

private:


	// timer
	void	initTime(void);
	void    getCurrentTime(_timeCountType* timeData);
	double  diffTimeInMicroSec(_timeCountType  timePre, _timeCountType timeNext);
	void    addMicroSeconds(_timeCountType* orgTime, double timeToBeAddedInMicroSec);
	bool	bRunning(void) { return bStarted; }
	void	checkTime(double &dt, double &eT);
};




void GLSetupWith(CKangGL *window, int *pargc, char **argv, const char *title);

#endif