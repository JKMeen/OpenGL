#define GLUT_DISABLE_ATEXIT_HACK

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>
#include <conio.h> // getch(); �Լ��� ���

double rotation = 0;

void drawTriangle() { // �ﰢ�� �׸��� (���ü - ���ϳ� ����)
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
	 // ī�޶��� ���� ���� �ּ� �Ÿ��� �ִ� �Ÿ��� ���� ��ü�� �ְ� ����
	glMatrixMode(GL_MODELVIEW); // 
	glLoadIdentity();
	
	glLineWidth(1);
	*/
	glPushMatrix(); // Begin~End�� �޸� push~pop�� �� �ܶ����� �����Ų��.
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
	glutCreateWindow("������ �������� ����");

	glEnable(GL_DEPTH_TEST);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutMainLoop();

	return 0;
}