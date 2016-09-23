#define GLUT_DISABLE_ATEXIT_HACK

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>
#include <conio.h> // getch(); 함수를 사용

double rotation = 0;

void drawTriangle() { // 삼각형 그리기 (사면체 - 면하나 제외)
	glBegin(GL_POLYGON);

	glColor3f(0.5, 0, 1);
	glVertex3f(-0.5, -0.5, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0.5, -0.5, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0.5,0);

	glEnd();
}

void myDisplay() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	/*
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 0.1, 100);
	 // 카메라의 상을 맻는 최소 거리와 최대 거리를 정해 입체감 있게 만듬
	glMatrixMode(GL_MODELVIEW); // 
	glLoadIdentity();
	
	glLineWidth(1);
	*/
	glPushMatrix(); // Begin~End와 달리 push~pop은 한 단락으로 적용시킨다.
	glRotatef(0, rotation, 0, 0);
	drawTriangle();
	glPopMatrix();
	
	for (int i = 0; i < 30; i++){
		rotation += 0.05;
	}

	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("양혜영 오픈지엘 과제");

	glEnable(GL_DEPTH_TEST);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutMainLoop();

	return 0;
}