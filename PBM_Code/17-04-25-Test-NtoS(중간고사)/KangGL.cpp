#include "KangGL.h"
#include <stdlib.h>
#include <stdio.h>

bool bTrace = false;

// Constructor
CKangGL::CKangGL() : bStarted(false), bPaused(false), plane(NULL), nPoints(0), nSpheres(0) {
	mEx = 1;
	mEy = 1;
	mEz = 1;
	mTx = 0;
	mTy = 0;
	mTz = 0;
	mUx = 0;
	mUy = 1;
	mUz = 0;

	this->initTime();
}


CKangGL::~CKangGL() { }

CPoint *CKangGL::addPoint(void) {
	CPoint *p = new CPoint;
	pointList[nPoints++] = p;
	return p;
}

sphere *CKangGL::addSphere(void) {
	sphere *p = new sphere;
	sphereList[nSpheres++] = p;
	return p;
}

void CKangGL::removePoints(void) {
	for (int i = 0; i < nPoints; i++) {
		delete pointList[i];
	}
	nPoints = 0;
}

void CKangGL::removeSpheres(void) {
	for (int i = 0; i < nSpheres; i++) {
		delete sphereList[i];
	}
	nSpheres = 0;
}

void CKangGL::removeAll(void) {
	removePoints();
	removeSpheres();
}

void CKangGL::addPlane(double w, float h, float interval) {
	if (plane) delete plane;
	plane = new CPlane();
	plane->setPlane(w, h, interval);
}

void CKangGL::idle(void) {
	double dt, et;
	checkTime(dt, et); // in microseconds

	actions(dt / 1000000.0, et / 1000000.0); // in seconds

}

void CKangGL::display(void) {
	if (plane) plane->visualize();
	for (int i = 0; i < nPoints; i++) {
		pointList[i]->visualize();
	}
	for (int i = 0; i < nSpheres; i++) {
		sphereList[i]->visualize();
	}



}

void CKangGL::actions(double dt, double currentTime) {
	if (bStarted && !bPaused) {
		doSimulation(dt, currentTime);
	}
}



// Control Event Handlers

void CKangGL::start() {
	if (bStarted) return;

	bStarted = true; bPaused = false;
	this->init();
}

void CKangGL::stop() {
	if (!bStarted) return;

	bStarted = false; bPaused = false;
	this->clean();
}

void CKangGL::pause() {
	bPaused = true;
}

void CKangGL::resume() {
	bPaused = false;
}


//////////////////////////////////// timer
void CKangGL::initTime(void) {
#ifdef WIN32
	QueryPerformanceFrequency(&frequency);
	startCount.QuadPart = 0;
	checkCount.QuadPart = 0;
	endCount.QuadPart = 0;
#else
	startCount.tv_sec = startCount.tv_usec = 0;
	checkCount.tv_sec = checkCount.tv_usec = 0;
	endCount.tv_sec = endCount.tv_usec = 0;
#endif
}

void CKangGL::getCurrentTime(_timeCountType* timeData) {
#ifdef WIN32
	QueryPerformanceCounter(timeData);
#else
	gettimeofday(timeData, NULL);
#endif
}

double CKangGL::diffTimeInMicroSec(_timeCountType  timePre, _timeCountType timeNext) {
#ifdef WIN32
	double startTimeInMicroSec = timePre.QuadPart * (1000000.0 / frequency.QuadPart);
	double endTimeInMicroSec = timeNext.QuadPart * (1000000.0 / frequency.QuadPart);
	return endTimeInMicroSec - startTimeInMicroSec;
#else
	double startTimeInMicroSec = (timePre.tv_sec * 1000000.0) + timePre.tv_usec;
	double endTimeInMicroSec = (timeNext.tv_sec * 1000000.0) + timeNext.tv_usec;
	return endTimeInMicroSec - startTimeInMicroSec;
#endif
}

void CKangGL::addMicroSeconds(_timeCountType* orgTime, double timeToBeAddedInMicroSec){
	long addSec = (long)timeToBeAddedInMicroSec / 1000000;
	long addMicro = (long)timeToBeAddedInMicroSec - addSec * 1000000;
#ifdef WIN32
	orgTime->QuadPart += timeToBeAddedInMicroSec * frequency.QuadPart / 1000000;
#else
	orgTime->tv_sec += addSec;
	orgTime->tv_usec += addMicro;
#endif
}

void CKangGL::checkTime(double &dt, double &et) {
	// dt
	tempCount = checkCount;
	getCurrentTime(&checkCount);

	if (!bStarted || bPaused) dt = 0.0;
	else {
		dt = diffTimeInMicroSec(tempCount, checkCount);
	}

	// et
	if (!bStarted) {
		getCurrentTime(&endCount);
		startCount = endCount;
	}
	else {
		getCurrentTime(&endCount);
	}
	et = diffTimeInMicroSec(startCount, endCount);
}



void CKangGL::setCamera(float x, float y, float z, float tx, float ty, float tz, float ux, float uy, float uz) {
	mEx = x;
	mEy = y;
	mEz = z;
	mTx = tx;
	mTy = ty;
	mTz = tz;
	mUx = ux;
	mUy = uy;
	mUz = uz;
}


CKangGL *win = NULL;

void idle() {
	win->idle();
	glutPostRedisplay();
}

void display() {
	GLbitfield mask = bTrace ? GL_DEPTH_BUFFER_BIT : (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(mask);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(win->mEx, win->mEy, win->mEz, win->mTx, win->mTy, win->mTz, win->mUx, win->mUy, win->mUz);

	win->display();
	glutSwapBuffers();
}

void reshapeFunction(int w, int h) {
	if (h == 0) h = 1;
	float ratio = 1.0* w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(60, ratio, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y) {
	switch (c) {
	case 's': win->start(); break;
	case ' ': win->stop(); break;
	case 'p': win->pause(); break;
	case 'r': win->resume(); break;
	case 't': bTrace = bTrace ? false : true; break;
	case 'l': win->mEx++;  break;
	case 'k': win->mEx--;  break;
	}
}

void GLinit(void) {
	glEnable(GL_DEPTH_TEST);
}
void GLSetupWith(CKangGL *window, int *pArgc, char **argv, const char *title) {
	win = window;
	glutInit(pArgc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow(title);
	GLinit();
	win->init();
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshapeFunction);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutMainLoop();
}