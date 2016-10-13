#define GLUT_DISABLE_ATEXIT_HACK

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>

float range = 1.0;
float aspRatio = 1.0;
float dX = 0.0;
float rt = 0, grt=0;

void drawAxis(){
	glBegin(GL_LINES);

	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	
	glEnd();
}

void myDisplay() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2, 2, 2, 0, 0, 0, 0, 1, 0);
	
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glLineWidth(5);
	drawAxis();
	glLineWidth(1);

	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotatef(rt, 0, 1, 0);
	glutWireSphere(0.6, 20, 20); // 스페어 (반지름, 경도, 위도)
	glPopMatrix();

	rt += 1;
	grt += 2;
	if (rt >= 360){
		rt = 0;
	}
	if (grt >= 360){
		grt = 0;
	}
	

	// 수성
	glPushMatrix();
	glColor3f(0, 0, 1);
	glRotatef(rt, 0, 1, 0);
	glTranslatef(1.2, 0, 0);
	glRotatef(rt, 1, 0, 0);
	glutWireSphere(0.2, 10, 10); // 스페어 (반지름, 경도, 위도)

	glRotatef(-rt, 1, 0, 0);
	glColor3f(1, 1, 1);
	glRotatef(rt, 0, 1, 0);
	glTranslatef(0.5, 0, 0);
	glRotatef(rt, 1, 0, 0);
	glutWireSphere(0.1, 10, 10); // 스페어 (반지름, 경도, 위도)
	glPopMatrix();

	// 금성
	glPushMatrix();
	glColor3f(1, 1, 0);
	glRotatef(grt, 0, 1, 0);
	glTranslatef(2, 0, 0);
	glRotatef(grt*2, 1, 0, 0);
	glutWireSphere(0.4, 10, 10); // 스페어 (반지름, 경도, 위도)

	glRotatef(-grt, 1, 0, 0);
	glColor3f(1, 1, 1);
	glRotatef(grt, 0, 1, 0);
	glTranslatef(0.5, 0, 0);
	glRotatef(grt, 0, 1, 0);
	glRotatef(grt, 0, 0, 1);
	glutWireSphere(0.1, 10, 10); // 스페어 (반지름, 경도, 위도)
	glPopMatrix();

	glutSwapBuffers();
}

void SetCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -2, 2);
	gluPerspective(60, aspRatio, 0.1, 1000);
}

void reshape(int w, int h){
	aspRatio = float(w)/h;
	SetCamera();
	glViewport(0, 0, w, h);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("12510096 조광민");
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}