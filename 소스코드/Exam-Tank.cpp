#define GLUT_DISABLE_ATEXIT_HACK

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>
#include <conio.h> // getch(); �Լ��� ���

GLfloat eyey = 3, eyex = 0, eyez = 0, tr = 0.01; // ���� �̵� ����
GLfloat pox = 0, poy = 0, poz = 0; // ��ž ȸ�� �Լ�
GLfloat movex = 0, movey = 0, movez = 0; // ���� ȸ��, �̵� �Լ�
GLfloat tirerotate = 0; // ���� ȸ��
GLdouble delay = 1;
GLint fovy = 0; // �۽���Ƽ�� �� �þ� ����
GLfloat potan = 1, pomove = 0;

// �����
void drawCircle(float radius, float size){
	glBegin(GL_POLYGON);

	int nPoints = 20;
	float angle = 0.0;
	float step = (3.14159*2.0) / nPoints;
	// �ݺ��� ������ ���� ���� ���� ��ǥ�� ����� �ڿ� �����ϴ� ���
	// ���⼭�� ���� �̷�� �������� ���
	while (angle <3.14159*2.0) {
		glVertex3f(radius*cos(angle), size, radius*sin(angle));
		glVertex3f(radius*cos(angle), -size, radius*sin(angle));
		glVertex3f(radius*cos(angle + step), -size, radius*sin(angle + step));
		glVertex3f(radius*cos(angle), size, radius*sin(angle));
		angle += step;
	}
	glEnd();

}

// ����(�����)
void drawtire(float radius, float size, float msize, int Points){
	glBegin(GL_POLYGON);

	int nPoints = Points;
	float angle = 0.0;
	float step = (3.14159*2.0) / nPoints;
	// �ݺ��� ������ ���� ���� ���� ��ǥ�� ����� �ڿ� �����ϴ� ���
	// ���⼭�� ���� �̷�� �������� ���
	while (angle <3.14159*2.0) {
		glVertex3f(size, radius*cos(angle), radius*sin(angle));
		glVertex3f(msize, radius*cos(angle), radius*sin(angle));
		glVertex3f(msize, radius*cos(angle + step), radius*sin(angle + step));
		glVertex3f(size, radius*cos(angle), radius*sin(angle));
		angle += step;
	}
	glEnd();
}

// ����
void drawtop(float radius, float size, float msize){
	glBegin(GL_POLYGON);

	int nPoints = 20;
	float angle = 0.0;
	float zangle = 0.0;
	float step = (3.14159*2.0) / nPoints;
	while (zangle <3.14159*2.0) {
		glVertex3f(size, radius*sin(zangle), radius*cos(zangle));
		while (angle < 3.14159*2.0) {
			glVertex3f(size, radius*cos(angle), radius*sin(angle));
		}
		angle += step;
	}
	glEnd();
}

void drawRactangle(float xscale, float yscale, float zscale){
	glBegin(GL_QUADS);

	// �պκ�
	glVertex3f(-xscale, -yscale, zscale);
	glVertex3f(xscale, -yscale, zscale);
	glVertex3f(xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, zscale);

	// �޺κ�
	glVertex3f(-xscale, yscale, -zscale);
	glVertex3f(xscale, yscale, -zscale);
	glVertex3f(xscale, -yscale, -zscale);
	glVertex3f(-xscale, -yscale, -zscale);

	// ���κ�
	glVertex3f(xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, -zscale);
	glVertex3f(xscale, yscale, -zscale);

	// �Ʒ� �κ�
	glVertex3f(-xscale, -yscale, zscale);
	glVertex3f(xscale, -yscale, zscale);
	glVertex3f(xscale, -yscale, -zscale);
	glVertex3f(-xscale, -yscale, -zscale);

	// ����
	glVertex3f(-xscale, -yscale, zscale);
	glVertex3f(-xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, -zscale);
	glVertex3f(-xscale, -yscale, -zscale);

	// ������
	glVertex3f(xscale, -yscale, zscale);
	glVertex3f(xscale, yscale, zscale);
	glVertex3f(xscale, yscale, -zscale);
	glVertex3f(xscale, -yscale, -zscale);
	glEnd();

	/// �� ����
	glBegin(GL_LINE_STRIP);
	glColor3f(1, 0, 0);
	// �պκ�
	glVertex3f(-xscale, -yscale, zscale);
	glVertex3f(xscale, -yscale, zscale);
	glVertex3f(xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, zscale);

	// �޺κ�
	glVertex3f(-xscale, yscale, -zscale);
	glVertex3f(xscale, yscale, -zscale);
	glVertex3f(xscale, -yscale, -zscale);
	glVertex3f(-xscale, -yscale, -zscale);

	// ���κ�
	glVertex3f(xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, -zscale);
	glVertex3f(xscale, yscale, -zscale);

	// �Ʒ� �κ�
	glVertex3f(-xscale, -yscale, zscale);
	glVertex3f(xscale, -yscale, zscale);
	glVertex3f(xscale, -yscale, -zscale);
	glVertex3f(-xscale, -yscale, -zscale);

	// ����
	glVertex3f(-xscale, -yscale, zscale);
	glVertex3f(-xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, -zscale);
	glVertex3f(-xscale, -yscale, -zscale);

	// ������
	glVertex3f(xscale, -yscale, zscale);
	glVertex3f(xscale, yscale, zscale);
	glVertex3f(xscale, yscale, -zscale);
	glVertex3f(xscale, -yscale, -zscale);
	glEnd();
}

void drawPlane(void) { // �ٴ� Ÿ�� ����
	glColor4f(1, 1, 1, 0.1);
	glBegin(GL_LINES);
	for (int i = 0; i <= 100; i++) {
		glVertex3f(-100, 0, i - 10);
		glVertex3f(100, 0, i - 10);
	}
	for (int i = 0; i <= 100; i++) {
		glVertex3f(i - 10, 0, -100);
		glVertex3f(i - 10, 0, 100);
	}
	glEnd();
}

// Ű �Է�
void  keyboard(unsigned char key, int x, int y)
{
	int   mod;
	switch (key) {
	// ���� �̵�
	case 't':
		eyey += 0.3;
		break;
	case 'g':
		eyey -= 0.3;
		break;
	case 'f':
		eyex += 0.05;
		break;
	case 'h':
		eyex -= 0.05;
		break;
	// ��ž
	case 'w':
		poy += 3;
		if (poy >= 45) poy = 45;
		break;
	case 's':
		poy -= 3;
		if (poy <= 0) poy = 0;
		break;
	case 'a':
		pox += 3;
		break;
	case 'd':
		pox -= 3;
		break;
	case 'c':
		if (potan == 1){
			potan = -1;
		}
		break;
	case 'z':
		delay *= -1;
		if (delay == -1){
			fovy = 0;
		}
		else if (delay == 1){
			fovy = 0;
		}
		break;
	}
	glutPostRedisplay();
}

void  special(int key, int x, int y)
{
	switch (key) {
	// �̵�
	case GLUT_KEY_UP:
		movez -= 1;
		tirerotate -= 30; // Ÿ�̾� ȸ��
		break;
	case GLUT_KEY_DOWN:
		movez += 1;
		tirerotate += 30; // Ÿ�̾� ȸ��
		break;
	// ���� ȸ��
	case GLUT_KEY_LEFT:
		movex += 3;
		break;
	case GLUT_KEY_RIGHT:
		movex -= 3;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void drawWall(){
	for (int i = -5.0; i<15; i += 10){
		for (int j = -5.0; j<15; j += 10){
			glPushMatrix();
			glColor4f(1, 1, 1, 1);
			//glRotatef(45, 0, 0, 1); // �����̼� ����, x, y, z�� ����
			glTranslatef(i, 0.5, j);
			// -5  -2.5  0  2.5  5
			drawRactangle(0.5, 0.5, 0.5);
			glPopMatrix();

			glPushMatrix();
			glColor4f(0, 1, 0, 1);
			glTranslatef(i, 1.5, j);
			// -5  -2.5  0  2.5  5
			drawCircle(0.4, 1.5);
			glPopMatrix();
		}
	}
}

void myDisplay() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, -10, 10);
	gluPerspective(fovy, 1, 0.1, 3000);
	// �þ߰�, ��Ⱦ��, �������ܸ�, �Ĺ����ܸ�
	// ī�޶��� ���� ���� �ּ� �Ÿ��� �ִ� �Ÿ��� ���� ��ü�� �ְ� ����
	glMatrixMode(GL_MODELVIEW); // 
	glLoadIdentity();

	if (delay == -1){
		gluLookAt(1, 0, 0, 0, 0, 0, 0, 1, 0); //ī�޶� ȸ��
	}
	else {
		gluLookAt(2.0*cos(eyex), eyey, 2.0*sin(eyex), 0, 1.5, 0, 0, 1, 0); //ī�޶� ȸ��
	}

	glPushMatrix();
	// �̵� �� ȸ�� �Լ�
	//glRotatef(movex, 0, 1, 0);
	glTranslatef(0, 0, -movez);
	drawPlane();
	glLineWidth(1);
	glPopMatrix();

	// ��ũ ����
	glPushMatrix();

		glColor3f(1, 1, 1);
		glTranslatef(0, 0.8, 0.5);
		drawRactangle(2, 0.6, 3.5);

		// ��ũ ��ž
		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(0, 1, 0.5);
		glRotated(pox, 0, 1, 0);
		drawRactangle(1.5, 0.5, 2);

		// ��ũ ����
		glPushMatrix();
		glColor3f(1, 0, 1);
		glTranslatef(0, 0, -1);
		glRotatef(90, 0, 1, 0);
		glRotatef(poy, 0, 0, 1);
		drawtire(0.3, 5, -0.5, 10);

		// ��ź
		glPushMatrix();
		glColor3f(1, 1, 0);
		//glRotated(pox, 0, 1, 0);
		//glTranslatef(0, 0, -1);
		//glTranslatef(0, 1.8, 0);
		//glRotatef(90, 0, 1, 0);
		//glRotatef(poy, 0, 0, 1);
		if (potan == 1){
			pomove = 0;
			glTranslatef(0, 0, 0);
		}
		else if (potan == -1){
			pomove += 0.4;
			glTranslatef(pomove, 0, 0);
			if (pomove >= 10){
				potan = 1;
			}
		}
		drawtire(0.2, 1, -0.5, 10);
		glPopMatrix();

		glPopMatrix(); // ��ũ ����

		glPopMatrix(); // ��ũ ��ž

		// ����1-0 (����)
		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(2.5, 0, -2); // ��ġ ����
		glRotatef(tirerotate, 1, 0, 0); // Ÿ�̾� ȸ��
		drawtire(1, 0.4, -0.5, 5);
		glPopMatrix(); // ����1-0
		/*
		// ����1-1
		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(2.5, 0, 0.5);
		glRotatef(tirerotate, 1, 0, 0);
		drawtire(1, 0.4, -0.5, 5);
		glPopMatrix(); // ����1-1
		*/
		// ����1-2
		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(2.5, 0, 2.5);
		glRotatef(tirerotate, 1, 0, 0);
		drawtire(1, 0.4, -0.5, 5);
		glPopMatrix(); // ����1-2

		// ����2-0 (����)
		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(-2.5, 0, -2);
		glRotatef(tirerotate, 1, 0, 0);
		drawtire(1, -0.4, 0.5, 5);
		glPopMatrix(); // ����2-0
		/*
		// ����2-1
		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(-2.5, 0, 0.5);
		glRotatef(tirerotate, 1, 0, 0);
		drawtire(1, -0.4, 0.5, 5);
		glPopMatrix(); // ����2-1
		*/
		// ����2-2
		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(-2.5, 0, 2.5);
		glRotatef(tirerotate, 1, 0, 0);
		drawtire(1, -0.4, 0.5, 5);
		glPopMatrix(); // ����2-2

	glPopMatrix(); // ��ũ ����

		
	
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("12510096 ������ �������� ����");

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutMainLoop();

	return 0;
}