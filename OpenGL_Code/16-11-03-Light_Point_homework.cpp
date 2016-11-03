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
GLfloat lit_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lit_ambient[] = { 0.7, 0.0, 0.7, 0 };

// material parameters
GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 0 };

void SetLighting(void){
	// ���ݻ�
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); // ���׸����� float vector ���·� ���� (�ո��� ĥ�ϴµ� ������ �����̵ǰ�, DiffuseĮ�� ���� ��ǻ� �ٲ���)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lit_diffuse); // GL_LIGHT0�� ���̰�, GL_DIFFUSE�� ���̴µ�, lit_diffuse�� ����
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lit_diffuse);

	// ���ݻ�
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialf(GL_FRONT, GL_SHININESS, 30); // ���� �߰�����
	glLightfv(GL_LIGHT0, GL_SPECULAR, lit_specular);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lit_specular);

	// �ֺ���
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lit_ambient);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lit_ambient);
}

void SetLightPosition(){
	glLightfv(GL_LIGHT0, GL_POSITION, lit_position); // ����Ʈ�� �������� �����
	glLightfv(GL_LIGHT1, GL_POSITION, lit_position);
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
	case 27: exit(0); break;
	}
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
	//gluLookAt(2.0*cos(angle), 3, 2.0*sin(angle), 0, 0, 0, 0, 1, 0);
	gluLookAt(0.0, 0, 10.0, 0, 0, 0, 0, 1, 0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	SetLightPosition();
	
	// ��ü �� ��ȭ
	static GLfloat rc=0, gc=0, bc=0, rcb=1, gcb=1, bcb=1;
	rc += 0.001*rcb; gc += 0.003*gcb; bc += 0.002*bcb;
	if (rc >= 1.0 || rc <= 0) rcb *= -1;
	if (gc >= 1.0 || gc <= 0) gcb *= -1;
	if (bc >= 1.0 || bc <= 0) bcb *= -1;
	mat_diffuse[0] = rc;
	mat_diffuse[1] = gc;
	mat_diffuse[2] = bc;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	// �� ȸ��
	static float angle = 0;
	angle += 0.05;
	lit_position[0] = 5.0 * cos(angle);
	lit_position[1] = 0; //5.0 * sin(angle);
	lit_position[2] = 5.0 * sin(angle);

	glLineWidth(1);
	drawAxes(1.0);

	//Light param ��¦�� ȿ��
	static float Lightmove = 0, ban= 1;
	Lightmove += 0.5 * ban;
	if (Lightmove >=128 || Lightmove <= 0){
		ban *= -1;
	}
	glEnable(GL_LIGHTING);
	for (int i = -5; i < 5; i++){
		glMaterialf(GL_FRONT, GL_SHININESS, Lightmove);
		for (int j = -5; j < 5; j++){
			glPushMatrix();
			// draw Sphere
			glTranslatef(i+0.5, j+0.5, 0);
			glutSolidSphere(0.3, 20, 20);
			glPopMatrix();
		}
	}
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
	//glEnable(GL_LIGHT1);
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