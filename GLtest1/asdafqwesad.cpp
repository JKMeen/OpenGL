#define GLUT_DISABLE_ATEXIT_HACK

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>
#include <conio.h> // getch(); �Լ��� ���

float eyey = 1, eyex = 10, eyez = 10, tr = 0.01; // ���� ����
double delay = -1; // �ﰢ�� ũ�� ������ ���� ����

void drawTriangle(float size) { // �ﰢ�� �׸��� (���ü - ���ϳ� ����)
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

void drawPlane(void) { // �ٴ� Ÿ�� ����
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

// Ű �Է�
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
	// ī�޶��� ���� ���� �ּ� �Ÿ��� �ִ� �Ÿ��� ���� ��ü�� �ְ� ����
	glMatrixMode(GL_MODELVIEW); // 
	glLoadIdentity();

	gluLookAt(3.0*cos(eyex), eyey, 3.0*sin(eyex), 0, 1.5, 0, 0, 1, 0); //ī�޶� ȸ��
	drawPlane();
	glLineWidth(1);

	glPushMatrix(); // Begin~End�� �޸� push~pop�� �� �ܶ����� �����Ų��.
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
	glutCreateWindow("12510096 ������");

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutMainLoop();

	return 0;
}
