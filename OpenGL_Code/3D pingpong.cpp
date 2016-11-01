#define GLUT_DISABLE_ATEXIT_HACK

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>
#include <conio.h> // getch(); �Լ��� ���

//GLfloat ax, ay, az;
GLdouble angle = 0.0; // ȸ�� ��
GLfloat cx, cy, cz; // Ŭ�� ��ǥ
GLfloat ca; // Ŭ�� �ޱ�
// ���콺 �̵��� ����

GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
GLfloat pos[] = { 3.0, 4.0, 5.0, 1.0 };
GLdouble ex = 0.0, ey = 0.0, ez = 10.0;
GLdouble tx = 0.0, ty = 0.0, tz = 0.0;
GLdouble ax = 0.0, ay = 1.0, az; // ȸ�� ��

double sx, sy;
#define SCALE 360.0

/////////////////////////////////////
float mvx= 0, mvz = 0;
float ballx = 0, bally = 0, ballz = 0;
float xc = 1, yc = 1, zc = 1;
float viewx = 0, viewy = 0, viewz = 0;

void drawRactangle(float xscale, float yscale, float zscale){
	/// �� ����
	
	glColor3f(1, 0, 0);
	// �պκ�
	glBegin(GL_LINE_LOOP);
	glVertex3f(-xscale, -yscale, zscale);
	glVertex3f(xscale, -yscale, zscale);
	glVertex3f(xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, zscale);
	glEnd();
	// �޺κ�
	glBegin(GL_LINE_LOOP);
	glVertex3f(-xscale, yscale, -zscale);
	glVertex3f(xscale, yscale, -zscale);
	glVertex3f(xscale, -yscale, -zscale);
	glVertex3f(-xscale, -yscale, -zscale);
	glEnd();
	// ���κ�
	glBegin(GL_LINE_LOOP);
	glVertex3f(xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, -zscale);
	glVertex3f(xscale, yscale, -zscale);
	glEnd();
	// �Ʒ� �κ�
	glBegin(GL_LINE_LOOP);
	glVertex3f(-xscale, -yscale, zscale);
	glVertex3f(xscale, -yscale, zscale);
	glVertex3f(xscale, -yscale, -zscale);
	glVertex3f(-xscale, -yscale, -zscale);
	glEnd();
	// ����
	glBegin(GL_LINE_LOOP);
	glVertex3f(-xscale, -yscale, zscale);
	glVertex3f(-xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, -zscale);
	glVertex3f(-xscale, -yscale, -zscale);
	glEnd();
	// ������
	glBegin(GL_LINE_LOOP);
	glVertex3f(xscale, -yscale, zscale);
	glVertex3f(xscale, yscale, zscale);
	glVertex3f(xscale, yscale, -zscale);
	glVertex3f(xscale, -yscale, -zscale);

	glEnd();
}

void drawBall(){
	glBegin(GL_LINE_STRIP);

	/*
	int nPoints = 20;
	float angle = 0.0;
	float step = (3.14159*2.0) / nPoints;
	glColor3f(1, 1, 0);
	while (angle <3.14159*2.0) {
		glVertex3f(0.05*cos(angle), 0.05*sin(angle), 0);
		angle += step;
	}*/

	glutWireSphere(0.3, 20, 20);
	glEnd();
}

void drawPlayer(float xscale, float yscale, float zscale){
	/*glBegin(GL_QUADS);
	
	glColor3f(0, 0, 1);
	glVertex3f(0.1, 0.01, 0);
	glVertex3f(-0.1, 0.01, 0);
	glVertex3f(-0.1, -0.01, 0);
	glVertex3f(0.1, -0.01, 0);

	glEnd();*/
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
}

// ���콺 �Է�
/*
void mouse(int x, int y){

}*/

void resize(int w, int h){
	// ���콺 ������ ��ġ �������� ������� ��ġ�� ȯ�� ��
	sx = 1.0 / (double)w;
	sy = 1.0 / (double)h;
}

void motion(int x, int y){
	double dx, dy, a;

	// ���콺 ������ ��ġ�� ���� ���� ��ġ������ ����
	dx = (x - cx) * sx;
	dy = (y - cy) * sy;

	// ���콺 ������ ��ġ�� ���� ���� ��ġ������ �Ÿ�
	a = sqrt(dx * dx + dy * dy);

	if (a != 0.0){
		// �Ÿ��� ������ ȯ���Ͽ� �巡�� ���۽��� ȸ�� ���� ����
		angle = fmod(ca + SCALE * a, 360.0);

		// ���콺 �������� �������� ȸ���� ���͸� ��û
		ax = dy / a;
		ay = dx / a;
		az = 0.0;

		// ������ �� ��ȭ
		glutPostRedisplay();
	}
}

void mouse(int button, int direction, int x, int y)
{
	switch (direction){
	case GLUT_DOWN :
		// ���콺 ��ư�� ���� ��ġ�� ���
		cx = x;
		cy = y;
		// ǥ���ϰ� �ִ� ��ü�� ȸ�� ���� ���
		ca = angle;
		break;
	default :
		break;
	}
}
// Ű �Է�
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
		mvx -= 0.05;
		if (mvx <= -0.5){
			mvx = -0.5;
		}
		break;
	case 'd':
		mvx += 0.05;
		if (mvx >= 0.5){
			mvx = 0.5;
		}
		break;
	case 'w':
		mvz -= 0.05;
		if (mvz <= -0.5){
			mvz = -0.5;
		}
		break;
	case 's':
		mvz += 0.05;
		if (mvz >= 0.5){
			mvz = 0.5;
		}
		break;
	}
	glutPostRedisplay();
}

void specialkey(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		viewx -= 0.1;
		break;
	case GLUT_KEY_RIGHT:
		viewx += 0.1;
		break;
	case GLUT_KEY_UP:
		viewy += 0.1;
		break;
	case GLUT_KEY_DOWN:
		viewy -= 0.1;
		break;
	}
	glutPostRedisplay();
}

void myDisplay() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);
	gluPerspective(30, 1, 0.1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(-3.0*cos(viewx), viewy, -3.0*sin(viewx), 0, 0, 0, 0, 1, 0);
	gluLookAt(ex, ey, ez, tx, ty, tz, 0.0, 1.0, 0.0);
	glRotated(angle, ax, ay, 0.0);

	glPushMatrix();
	glTranslatef(ballx, bally, ballz);
	glColor3f(0, 1, 0);
	glutWireSphere(0.1, 15, 15);
	//drawBall();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(mvx, -0.8, mvz);
	glColor3f(0, 0, 1);
	drawPlayer(0.3, 0.01, 0.3);
	glPopMatrix();

	// �� �浹 �̺�Ʈ
	if (ballx >= 0.8 || ballx <= -0.8){ xc *= -1; }
	if (bally >= 0.8){ yc = -1; }
	if (bally <= -1){ yc = 1; }//exit(0); }//yc = 1; }
	if (ballz >= 0.8 || ballz <= -0.8){ zc *= -1; }
	if (ballx > mvx-0.3 && ballx < mvx+0.3 && ballz > mvz-0.3 && ballz < mvz+0.3 && bally <= -0.6){ yc = 1; }

	ballx += 0.01 * xc;
	bally += 0.008 * yc;
	ballz += 0.003 * zc;

	drawRactangle(0.9, 0.9, 0.9);
	glPushMatrix();
	glColor3f(1,1,0);
	glPopMatrix();

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
	glutSpecialFunc(specialkey);
	
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutReshapeFunc(resize);

	glutMouseFunc(mouse); // ���콺 Ŭ�� �� �߻��Ǵ� �̺�Ʈ
	glutMotionFunc(motion); // ���콺 Ŭ�� �� �̵� �� �߻��Ǵ� �̺�Ʈ
	//glutPassiveMotionFunc(); // ���콺 Ŭ�� ���ϰ� �̵� �� �߻��Ǵ� �̺�Ʈ

	glutMainLoop();

	return 0;
}
