#define GLUT_DISABLE_ATEXIT_HACK

#include "GL_header.h"
#include "Camera.h"
#include "Light.h"
#include "Draw.h"

#include <math.h>
#include <stdlib.h>

GLfloat movez = 7.5;

// 시점 변경
bool setcam = true;

// 라이트 변경
int bSpot = 0;

// 다이렉션 라이트
GLfloat lightPos[] = { 0, 1, 0, 1 };

// 스포트 라이트
GLfloat lightPos1[] = { 0, 1, 0, 1 };

// 포인트 라이트
GLfloat lightPos2[] = { 0, 1, 0, 1 };

void keyboard(unsigned char c, int x, int y) {
	switch (c) {
	case 27: exit(0);
	case 'a': movez += 0.1;  break;
	case 'd': movez -= 0.1;  break;
	case 'q': bSpot += 1; if (bSpot >= 4) bSpot = 0;
				SetSpot(bSpot, 30.0f); break;
	case 'e': setcam = setcam ? true : false; break;
	}
	glutPostRedisplay();
}

void reshape(int w, int h) {
	float asp = float(w) / h;
	setCameraLens(60, asp);
	glViewport(0, 0, w, h);
}

void drawTC(){
	// 책상
	glPushMatrix();
	SetMaterial(0.8, 0.1, 0.0, 0.8, 0.1, 0, 0.8, 0.1, 0);
	drawTable();
	glPopMatrix();

	// 의자
	glPushMatrix();
	glTranslatef(0, 0, -0.75);
	SetMaterial(0.8, 0.1, 0.0, 0.8, 0.1, 0, 0.8, 0.1, 0);
	drawChair();
	glPopMatrix();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	setCameraPosition(1.5, 3.0, movez);

	SetLightPosition(lightPos, lightPos1, lightPos2);

	static float angle = 0;
	angle += 0.05;

	glPushMatrix();
	if (bSpot == 0){ 
		// 다이렉션 라이트
		lightPos[0] = 0;
		lightPos[1] = 4;
		lightPos[2] = 0;

		SetLight(0.5, 0.5, 0.5, 0.5, 0.5, 0.5);

		glPushMatrix();
		glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
		glColor3f(0, 0, 1);
		glutWireSphere(0.5, 10, 10);
		glColor3f(0, 0, 0);
		glPopMatrix();
	}
	else if(bSpot == 1){ 
		// 스포트 라이트
		lightPos1[0] = 5.0 * cos(angle);
		lightPos1[1] = 4;
		lightPos1[2] = 0;

		SetLight1(0.5, 0.5, 0.5, 0.5, 0.5, 0.5);

		glPushMatrix();
		glColor3f(1, 1, 1);
		glPushMatrix();
		glBegin(GL_LINES);
		glVertex3f(lightPos1[0], lightPos1[1], 0);
		glVertex3f(0, 10, 0);
		glEnd();
		glPopMatrix();

		glTranslatef(lightPos1[0], lightPos1[1]-0.5, lightPos1[2]);
		glPushMatrix();
		glRotatef(270, 1, 0, 0);
		glutWireCone(0.5, 0.5, 10, 10);
		glPopMatrix();
		glPopMatrix();
		glColor3f(0, 0, 0);
		glPopMatrix();
	}
	else if (bSpot == 2){
		// 포인트 라이트
		lightPos2[0] = 5.0 * cos(angle);
		lightPos2[1] = 2;
		lightPos2[2] = 0;//5.0 * sin(angle);

		SetLight2(0.5, 0.5, 0.5, 0.5, 0.5, 0.5);

		glPushMatrix();
		glTranslatef(lightPos2[0], lightPos2[1], lightPos2[2]);
		glColor3f(1, 0, 0);
		glutWireSphere(0.5, 10, 10);
		glPopMatrix();
		glColor3f(0, 0, 0);
		glPopMatrix();
	}
	
	glPopMatrix();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	// 바닥
	glPushMatrix();
	SetMaterial(1, 1, 1, 1, 1, 1, 0, 0, 0);
	drawPlane();
	glPopMatrix();

	// 천장
	glPushMatrix();
	glTranslatef(0, 7.0, 0);
	SetMaterial(1, 1, 1, 1, 1, 1, 0, 0, 0);
	drawPlane();
	glPopMatrix();

	// 왼쪽 벽
	glPushMatrix();
	glTranslatef(-5.51, 3.51, 0);
	SetMaterial(1, 1, 1, 1, 1, 1, 0, 0, 0);
	drawWall();
	glPopMatrix();

	// 오른쪽 벽
	glPushMatrix();
	glTranslatef(5.51, 3.51, 0);
	SetMaterial(1, 1, 1, 1, 1, 1, 0, 0, 0);
	drawWall();
	glPopMatrix();

	// 뒷 벽
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(5.51, 3.51, 0);
	SetMaterial(1, 1, 1, 1, 1, 1, 0, 0, 0);
	drawWall();
	glPopMatrix();

	// 책걸상
	for (int i = -4; i <= 4; i+= 2){
		for (int j = -4; j <= 4; j+=2){
			glPushMatrix();
			glTranslatef(i, 0, j);
			drawTC();
			glPopMatrix();
		}
	}
	
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);

	glutSwapBuffers();
}

void init() {
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	//SetMaterial(1.0, 1.0, 0.0);
}

int main(int argc, char **argv) {
	// glut initialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Lighting Test");

	// initialization
	init();

	// callback registration
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(display);

	// enter mainloop
	glutMainLoop();
}