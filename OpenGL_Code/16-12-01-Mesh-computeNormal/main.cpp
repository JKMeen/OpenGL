#include "Header.h"
#include "Camera.h"
#include "Light.h"
#include "mesh.h"
#include "Draw.h"


// mesh
CMesh mesh1, mesh2;

void keyboard(unsigned char c, int, int) {
	switch (c) {
	case 27: exit(0);
	}
}

void display() {
	// world
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	static float angle = 0;
	//gluLookAt(100.0*cos(angle), 50, 100.0*sin(angle), 0, 50, 0, 0, 1, 0);
	gluLookAt(100.0, 50, 100.0, 0, 50, 0, 0, 1, 0);
	angle += 0.001;
	SetLightPosition(angle);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glLineWidth(1);
	//draw axes
	drawAxes(1.0);

	glEnable(GL_LIGHTING);

	// draw mesh
	glColor3f(1, 0, 1);
	mesh1.show();

	glColor3f(0,1,0);
	mesh2.show();

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

	glDisable(GL_LIGHTING);

	glutSwapBuffers();
}


void init(void) {
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	// light enable
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	SetLighting();

	mesh1.read("femail.sms.txt");
	mesh2.read("sleevel.sms.txt");

}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Light");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	init();


	glutMainLoop();
	return 1;
}