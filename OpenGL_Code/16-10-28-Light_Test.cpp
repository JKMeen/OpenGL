#define GLUT_DISABLE_ATEXIT_HACK

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>

bool bPers = true;

// parameters for camera lens
float aspRatio = 1.0;

//light parameters
GLfloat lit_diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; // ���� ����
GLfloat lit_position[] = { 5, 5, 0, 1 }; // ��(����)�� ��ġ

// material parameters
GLfloat mat_diffuse[] = { 1.0, 1.0, 0.5, 1.0 };

void SetLighting(void){
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); // ���׸����� float vector ���·� ���� (�ո��� ĥ�ϴµ� ������ �����̵ǰ�, DiffuseĮ�� ���� ��ǻ� �ٲ���)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lit_diffuse); // GL_LIGHT0�� ���̰�, GL_DIFFUSE�� ���̴µ�, lit_diffuse�� ����
}

void SetLightPosition(){
	glLightfv(GL_LIGHT0, GL_POSITION, lit_position); // ����Ʈ�� �������� �����
}

void SetCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	bPers ? gluPerspective(60, aspRatio, 0.1, 1000) : glOrtho(-10, 10, -10, 10, -100, 100);
}

void reshape(int w, int h) {
	aspRatio = float(w) / h;
	SetCamera();
	glViewport(0, 0, w, h);
}

void keyboard(unsigned char c, int, int) {
	switch (c) {
	case 27: exit(0);
	}
}

void drawPlane(float width, float interval) {
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	for (float i = -width; i <= width; i += interval) {
		glVertex3f(i, 0, -width);
		glVertex3f(i, 0, width);
		glVertex3f(width, 0, i);
		glVertex3f(-width, 0, i);
	}
	glEnd();
}

void drawAxes(float size) {
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0); glVertex3f(size, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0); glVertex3f(0, size, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0); glVertex3f(0, 0, size);
	glEnd();
}



void display() {


	// world
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	static float angle = 0;
	gluLookAt(2.0*cos(angle), 2, 2.0*sin(angle), 0, 0, 0, 0, 1, 0);
	angle += 0.01;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SetLightPosition();

	glLineWidth(1);
	//draw axes
	drawAxes(1.0);

	// draw plane
	drawPlane(20, 0.5);

	// ����Ʈ�� �ϸ� glColor3f �� ���� ����
	// ù ��° ��� : draw�� ���� ����Ʈ�� ����
	// �� ��° ��� : material�� ���� �߰�����
	glEnable(GL_LIGHTING);
	// draw teapot
	glutSolidTeapot(0.5);
	glDisable(GL_LIGHTING);

	glutSwapBuffers();
}

// �ʱ�ȭ�� ��
void init(void){
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	// light enable
	glEnable(GL_LIGHTING); 
	glEnable(GL_LIGHT0); 
	SetLighting();
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