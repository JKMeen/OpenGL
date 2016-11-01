#define GLUT_DISABLE_ATEXIT_HACK

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>
#include <conio.h> // getch(); �Լ��� ���

float eyey = 2, eyex = 0, eyez = 0, tr = 0.01; // ���� ����
double delay = -1;

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
// �����
void drawCircle(float radius, float size){
	glBegin(GL_POLYGON);

	int nPoints=20;
	float angle = 0.0; 
	float step=(3.14159*2.0)/nPoints;
	// �ݺ��� ������ ���� ���� ���� ��ǥ�� ����� �ڿ� �����ϴ� ���
	// ���⼭�� ���� �̷�� �������� ���
	while (angle <3.14159*2.0) {
		glVertex3f(radius*cos(angle), size ,radius*sin(angle));
		glVertex3f(radius*cos(angle), -size ,radius*sin(angle));
		glVertex3f(radius*cos(angle+step), -size ,radius*sin(angle+step));
		glVertex3f(radius*cos(angle), size ,radius*sin(angle));
		angle += step;
	}
	glEnd();

}

// ����
void drawtire(float radius, float size, float msize){
	glBegin(GL_POLYGON);

	int nPoints=20;
	float angle = 0.0; 
	float step=(3.14159*2.0)/nPoints;
	// �ݺ��� ������ ���� ���� ���� ��ǥ�� ����� �ڿ� �����ϴ� ���
	// ���⼭�� ���� �̷�� �������� ���
	while (angle <3.14159*2.0) {
		glVertex3f(size, radius*cos(angle), radius*sin(angle));
		glVertex3f(msize, radius*cos(angle), radius*sin(angle));
		glVertex3f(msize, radius*cos(angle+step), radius*sin(angle+step));
		glVertex3f(size, radius*cos(angle), radius*sin(angle));
		angle += step;
	}
	glEnd();
}

// ����
void drawtop(float radius, float size, float msize){
	glBegin(GL_POLYGON);

	int nPoints=20;
	float angle = 0.0;
	float zangle = 0.0;
	float step=(3.14159*2.0)/nPoints;
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
	glVertex3f(-xscale,-yscale,zscale);
	glVertex3f(xscale,-yscale,zscale);
	glVertex3f(xscale,yscale,zscale);
	glVertex3f(-xscale,yscale,zscale);

	// �޺κ�
	glVertex3f(-xscale,yscale,-zscale);
	glVertex3f(xscale,yscale,-zscale);
	glVertex3f(xscale,-yscale,-zscale);
	glVertex3f(-xscale,-yscale,-zscale);

	// ���κ�
	glVertex3f(xscale,yscale,zscale);
	glVertex3f(-xscale,yscale,zscale);
	glVertex3f(-xscale,yscale,-zscale);
	glVertex3f(xscale,yscale,-zscale);

	// �Ʒ� �κ�
	glVertex3f(-xscale,-yscale,zscale);
	glVertex3f(xscale,-yscale,zscale);
	glVertex3f(xscale,-yscale,-zscale);
	glVertex3f(-xscale,-yscale,-zscale);

	// ����
	glVertex3f(-xscale,-yscale,zscale);
	glVertex3f(-xscale,yscale,zscale);
	glVertex3f(-xscale,yscale,-zscale);
	glVertex3f(-xscale,-yscale,-zscale);

	// ������
	glVertex3f(xscale,-yscale,zscale);
	glVertex3f(xscale,yscale,zscale);
	glVertex3f(xscale,yscale,-zscale);
	glVertex3f(xscale,-yscale,-zscale);
	glEnd();

	/// �� ����
	glBegin(GL_LINE_STRIP);
	glColor3f(1,0,0);
	// �պκ�
	glVertex3f(-xscale,-yscale,zscale);
	glVertex3f(xscale,-yscale,zscale);
	glVertex3f(xscale,yscale,zscale);
	glVertex3f(-xscale,yscale,zscale);

	// �޺κ�
	glVertex3f(-xscale,yscale,-zscale);
	glVertex3f(xscale,yscale,-zscale);
	glVertex3f(xscale,-yscale,-zscale);
	glVertex3f(-xscale,-yscale,-zscale);

	// ���κ�
	glVertex3f(xscale,yscale,zscale);
	glVertex3f(-xscale,yscale,zscale);
	glVertex3f(-xscale,yscale,-zscale);
	glVertex3f(xscale,yscale,-zscale);

	// �Ʒ� �κ�
	glVertex3f(-xscale,-yscale,zscale);
	glVertex3f(xscale,-yscale,zscale);
	glVertex3f(xscale,-yscale,-zscale);
	glVertex3f(-xscale,-yscale,-zscale);

	// ����
	glVertex3f(-xscale,-yscale,zscale);
	glVertex3f(-xscale,yscale,zscale);
	glVertex3f(-xscale,yscale,-zscale);
	glVertex3f(-xscale,-yscale,-zscale);

	// ������
	glVertex3f(xscale,-yscale,zscale);
	glVertex3f(xscale,yscale,zscale);
	glVertex3f(xscale,yscale,-zscale);
	glVertex3f(xscale,-yscale,-zscale);
	glEnd();
}

void drawPlane(void) { // �ٴ� Ÿ�� ����
	glColor4f(1, 1, 1, 0.1);
	glBegin(GL_LINES);
	for (int i = 0; i<=20; i++) {
		glVertex3f(-10, 0, i - 10);
		glVertex3f(10, 0, i - 10);
	}
	for (int i = 0; i<=20; i++) {
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

void drawWall(){
	for (int i= -5.0; i<15; i+=10){
		for (int j= -5.0; j<15; j+=10){
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
	gluPerspective(0, 1, 0.1, 2000);
	// �þ߰�, ��Ⱦ��, �������ܸ�, �Ĺ����ܸ�
	 // ī�޶��� ���� ���� �ּ� �Ÿ��� �ִ� �Ÿ��� ���� ��ü�� �ְ� ����
	glMatrixMode(GL_MODELVIEW); // 
	glLoadIdentity();

	gluLookAt(-3.0*cos(eyex), eyey, -3.0*sin(eyex), 0, 1.5, 0, 0, 1, 0); //ī�޶� ȸ��

	glPushMatrix();
	drawPlane();
	glLineWidth(1);
	glPopMatrix();

	glPushMatrix(); // Begin~End�� �޸� push~pop�� �� �ܶ����� �����Ų��.

	//glRotatef(tr * 2, 0, tr * 2, 0);
	if (delay == 1){
		// �ڵ��� ����
		glPushMatrix();
		//drawWall();
		glColor3f(1,1,1);
		glTranslatef(0, 0.8, 0.5);
		drawRactangle(2, 0.6, 3.5);
		glColor3f(1,1,1);
		glTranslatef(0, 1.41, 0.5);
		drawRactangle(2, 0.8, 2);
		glPopMatrix();

		// ����
		glPushMatrix();
		glColor3f(1,0,0);
		glTranslatef(1.7, 0 , -1);
		drawtire(1, 0.4, -0.5);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1,0,0);
		glTranslatef(1.7, 0 , 2.3);
		drawtire(1, 0.4, -0.5);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1,0,0);
		glTranslatef(-1.7, 0 , -1);
		drawtire(1,-0.4, 0.5);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1,0,0);
		glTranslatef(-1.7, 0 , 2.3);
		drawtire(1, -0.4, 0.5);
		glPopMatrix();

		// ���� ��
		glPushMatrix();
		glColor3f(0, 0, 1);
		glTranslatef(0, 3, 1);
		glutSolidSphere(2, 10, 10);
		glPopMatrix();

	}else {
		drawTriangle(0.5);
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