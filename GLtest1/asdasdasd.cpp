#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

void drawAxes() {
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0); // x
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0); // y
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1); // z
	glEnd();
}

void drawPlane(void) {
	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_LINES);
	for (int i = 0; i<40; i++) {
		glVertex3f(-20, 0, i - 20);
		glVertex3f(20, 0, i - 20);
	}
	for (int i = 0; i<40; i++) {
		glVertex3f(i - 20, 0, -20);
		glVertex3f(i - 20, 0, 20);
	}
	glEnd();

	glColor3f(0, 0, 0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex3f(-20, 0, 0);
	glVertex3f(20, 0, 0);
	glVertex3f(0, 0, -20);
	glVertex3f(0, 0, 20);
	glEnd();

}

void drawBox(float w, float h) {
	glPushMatrix();
	glScalef(w, h, w);
	glutWireCube(1);
	glPopMatrix();
}


void myDisplay() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 0.1, 100); //-2.0, 2.0, -2.0, 2.0, -1.0, 1.0);

	static float angle = 0.0;
	angle += 0.01;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3.0*cos(angle), 2.5, 3.0*sin(angle), 0, 1.5, 0, 0, 1, 0);

	glLineWidth(1);
	drawPlane();

	glLineWidth(3);
	drawAxes();
	glTranslatef(0, 0.5, 0);
	drawBox(0.25, 1);

	glTranslatef(0, 0.5, 0);
	glRotatef(45, 0, 0, 1);
	glTranslatef(0, 0.5, 0);
	drawAxes();
	drawBox(0.25, 1);

	static float tAngle;
	tAngle += 0.1;
	float hAngle = sin(tAngle);
	hAngle *= hAngle;

	// hand 1
	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	glRotatef(20.0*hAngle, 0, 0, 1);
	glTranslatef(0, 0.25, 0);
	drawAxes();
	drawBox(0.1, 0.5);
	glPopMatrix();

	// hand 2
	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	glRotatef(-20.0*hAngle, 0, 0, 1);
	glTranslatef(0, 0.25, 0);
	drawAxes();
	drawBox(0.1, 0.5);
	glPopMatrix();




	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Transform");

	glEnable(GL_DEPTH_TEST);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutMainLoop();

	return 0;
}