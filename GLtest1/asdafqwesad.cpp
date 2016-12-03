#define GLUT_DISABLE_ATEXIT_HACK

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>
#include <conio.h> // getch(); 함수를 사용

float eyey = 1, eyex = 10, eyez = 10, tr = 0.01; // 전역 변수
double delay = -1; // 삼각형 크기 조절을 위한 변수

void drawTriangle(float size) { // 삼각형 그리기 (사면체 - 면하나 제외)
	glBegin(GL_POLYGON);

	glColor3f(0.5, 0, 1);
	glVertex3f(1 * size, 1 * size, 1 * size);
	glColor3f(0, 0, 1);
	glVertex3f(1 * size, 1 * size, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 1 * size, 1 * size);
	glColor3f(0, 0, 1);
	glVertex3f(1 * size, 2 * size, 1 * size);
	glColor3f(0, 0, 1);
	glVertex3f(1 * size, 1 * size, 0);

	glEnd();
}

void drawPlane(void) { // 바닥 타일 생성
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	for (int i = 0; i <= 20; i++) {
		glVertex3f(-10, 0, i - 10);
		glVertex3f(10, 0, i - 10);
	}
	for (int i = 0; i <= 20; i++) {
		glVertex3f(i - 10, 0, -10);
		glVertex3f(i - 10, 0, 10);
	}
	glEnd();
}

// 키 입력
void  keyboard(unsigned char key, int x, int y)
{
	int   mod;

	switch (key) {
	case 'z':
		delay *= -1;
		break;
	}
	glutPostRedisplay();
}

void  special(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		eyey += 0.3;
		break;
	case GLUT_KEY_DOWN:
		eyey -= 0.3;
		break;
	case GLUT_KEY_LEFT:
		eyex += 0.05;
		break;
	case GLUT_KEY_RIGHT:
		eyex -= 0.05;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void myDisplay() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 0.1, 100);
	// 카메라의 상을 맻는 최소 거리와 최대 거리를 정해 입체감 있게 만듬
	glMatrixMode(GL_MODELVIEW); // 
	glLoadIdentity();

	gluLookAt(3.0*cos(eyex), eyey, 3.0*sin(eyex), 0, 1.5, 0, 0, 1, 0); //카메라 회전
	drawPlane();
	glLineWidth(1);

	glPushMatrix(); // Begin~End와 달리 push~pop은 한 단락으로 적용시킨다.
	glRotatef(tr * 2, 0, tr * 2, 0);
	if (delay == 1){
		drawTriangle(0.5);
	}
	else {
		drawTriangle(1);
	}
	glPopMatrix();

	for (int i = 0; i < 30; i++){
		tr += 0.05;
	}

	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("12510096 조광민");

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutMainLoop();

	return 0;
}
