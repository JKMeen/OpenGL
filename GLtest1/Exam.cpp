#define GLUT_DISABLE_ATEXIT_HACK

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>

float r=0;

void drawRectangle(float x, float y){
	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
	glVertex3f(-x, y, 0);
	glVertex3f(-x, -y, 0);
	glVertex3f(x, -y, 0);
	glVertex3f(x, y, 0);
	glEnd();
}
void drawRectangle2(){
	glBegin(GL_QUADS);
	glColor3f(1, 1, 0);
	glVertex3f(0.9, 0.4, 0);
	glVertex3f(0.7, 0.4, 0);
	glVertex3f(0.3, 0, 0);
	glVertex3f(0.5, 0, 0);
	glEnd();
}

void drawCircle(float r, float x, float y, float Cr, float Cg, float Cb){
	// ��
	glBegin(GL_POLYGON);
	int Points = 20; // �������� ���� ����
	float radius = r; // ������
	glColor3f(Cr, Cg, Cb);
	float angle = 0.0; // ����
	float step = (3.14159*2.0) / Points; // 360 / 20 = 18��
	while (angle < 3.14159*2.0) {
		glVertex3f(radius*cos(angle) + x , radius*sin(angle) + y, 0); // x, y��ŭ ��ġ �̵�
		angle += step; // ������ 18���� ����
	}
	glEnd();
}

void Display(){
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -2, 2); // â�� ������ �������ִ� ��
	gluPerspective(60, 1, 0.1, 100); // �չٴ� �þ߰����� ���� / ����, ����� �Ÿ�����, �� �Ÿ� ����
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 1, 1, 0, 0, 0, 0, 1, 0); // ī�޶��� ��ǥ, ī�޶󿡼� ��ü�� ��ġ, ī�޶� ����

	r += 2;
	/////////////////////////////////////
	glPushMatrix();
	glTranslatef(0.1, 0, 0); // �̵��ϴ� �� x��, y��, z��
	glColor3f(1, 0, 0);
	glutWireTeapot(0.1);
	////////////////////
	glPushMatrix();
	glRotatef(r, 0, 1, 0); // ȸ���ϴ� �� ����, x��, y�� z��
	glTranslatef(0.3, 0, 0); // �̵��ϴ� ��
	glColor3f(1, 1, 0);
	glutWireTeapot(0.1);
	glPopMatrix();
	///////////////////
	glPopMatrix();


	////////////////////////////////////
	/*drawCircle(0.2, 0.5, -0.5, 1, 0, 0);

	drawCircle(0.2, -0.5, -0.5, 0, 0, 1);

	drawRectangle2();
	
	glPushMatrix();
	glTranslatef(0.5, 0, 0); // �̵��ϴ� ��
	drawRectangle(0.5,0.3);
	glPopMatrix();
	*/
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("������");

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.0, 0.0, 1.0);

	glutDisplayFunc(Display);
	glutIdleFunc(Display);

	glutMainLoop();

	return 0;
}