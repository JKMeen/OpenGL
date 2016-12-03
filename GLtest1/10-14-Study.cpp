#define GLUT_DISABLE_ATEXIT_HACK

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>

GLfloat range = 1.0;
GLfloat aspRatio = 1.0;
GLfloat dX = 0.0;
GLfloat rt[8] = { 0, 0, 0, 0, 0, 0, 0 };
GLfloat srt[9] = { 0, 0, 0, 0, 0, 0, 0 };
GLint num = 15, pnum=90, headrotate=180;
GLfloat P_distance = 0, Prt;

////////////////////////////////////////////////
// ���콺
GLdouble angle = 0.0; // ȸ�� ��
GLfloat cx, cy, cz; // Ŭ�� ��ǥ
GLfloat ca; // Ŭ�� �ޱ�
// ���콺 �̵��� ����

GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
GLfloat pos[] = { 3.0, 4.0, 5.0, 1.0 };
GLdouble ex = 0.0, ey = 0.0, ez = 10.0;
GLdouble tx = 0.0, ty = 0.0, tz = 0.0;
GLdouble ax = 0.0, ay = 1.0, az; // ȸ�� ��

GLdouble sx, sy;
#define SCALE 360.0

////////////////////////////////////////////////
// ������ ������ 1�̸� �������̰�, 0�̸� ���Ɽ��(directional light source)

//������ ���ݻ�, ���ݻ�, �ֺ���, �����Ÿ� Ư������ ���� ������
GLfloat matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat matDiff[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat matAmbi[] = { 0.5, 0.1, 0.1, 1.0 };
GLfloat matShin[] = { 200.0 };

// ������ ���ݻ�, ���ݻ�, �ֺ��� Ư������ ���� ������
//GLfloat light[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lit_specular[] = { 1.0, 1.0f, 1.0f, 1.0f };
GLfloat lit_diffuse[] = { 0.0, 1.0f, 1.0f, 1.0f };
GLfloat lit_ambient[] = { 0.5, 1.0f, 1.0f, 1.0f };


// ������ ��ġ�� ���� ������
GLfloat lightPos[] = { 1.0, 1.0, 1.0, 1.0 };//{ -1.0, 1.0, 1.0, 1.0 };

////////////////////////////////////////////////

// ����� ������ Ư���� �غ�� �����ͷ� �����ϴ� �Լ�
void LightSet() {

	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbi);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShin);

	glLightfv(GL_LIGHT0, GL_SPECULAR, lit_specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lit_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lit_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

// ������ ��ġ�� �����ϴ� �Լ�
void LightPosition() {
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

void  special(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		num -= 2;
		if (num <= 0) num = 0;
		break;
	case GLUT_KEY_DOWN:
		num += 2;
		if (num >= 180) num = 180;
		break;
	case GLUT_KEY_LEFT:
		pnum += 2;
		if (pnum >= 75) pnum = 75;
		headrotate += 3;
		if (headrotate > 270) headrotate = 270;
		break;
	case GLUT_KEY_RIGHT:
		pnum -= 2;
		if (pnum <= 15) pnum = 15;
		headrotate -= 3;
		if (headrotate < 90) headrotate = 90;
		break;
	default:
		break;
	}
	glutPostRedisplay(); // �����츦 �׷��� �� ���� �׷��� (glutIdleFunc�� �Ƚᵵ��)
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
	case GLUT_DOWN:
		// ���콺 ��ư�� ���� ��ġ�� ���
		cx = x;
		cy = y;
		// ǥ���ϰ� �ִ� ��ü�� ȸ�� ���� ���
		ca = angle;
		break;
	default:
		break;
	}
}

void drawPlane(float width, float interval){
	int w = width;
	glColor3f(1, 1, 1);

	glBegin(GL_LINES);
	for (int j = -w; j <= w; j += interval){

		glVertex3f(j, 0, -w);
		glVertex3f(j, 0, w);

		glVertex3f(-w, 0, j);
		glVertex3f(w, 0, j);
	}
	glEnd();
}

void SetCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-P_distance, P_distance, -P_distance, P_distance, -P_distance, P_distance);
	gluPerspective(0, aspRatio, 0.1, 100);
}

void reshape(int w, int h){
	aspRatio = float(w) / h;
	SetCamera();
	glViewport(0, 0, w, h);

	// ���콺 ������ ��ġ �������� ������� ��ġ�� ȯ�� ��
	sx = 1.0 / (double)w;
	sy = 1.0 / (double)h;
}

void GLInit() {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// ������ Ư���� ������ Ư���� ����
	LightSet();
	glEnable(GL_DEPTH_TEST);
}

void drawBox(float Scalefx, float Scalefy, float Scalefz){
	glPushMatrix();
	glScalef(Scalefx, Scalefy, Scalefz);
	glutSolidCube(1.0);
	glPopMatrix();
}

void drawRobot(){
	// �ٴ� ����
	glPushMatrix();
	glTranslatef(0, 1, 0);
	drawBox(3, 2, 3);

	// ����� 1
	glPushMatrix();
	glTranslatef(0, 2, 0);
	drawBox(1, 2, 1);

	// �����̴� ��1
	glPushMatrix();
	glTranslatef(0, 1, 0);
	glRotatef(num, 0, 0, 1);
	glTranslatef(0, 2.5, 0);
	drawBox(1, 5, 1);

	// �հ���(1)
	glPushMatrix();
	glTranslatef(0, 2.5, 0);
	// �հ��� 1
	glPushMatrix();
	glRotatef(-pnum, 0, 0, 1);
	glTranslatef(0, 1, 0);
	drawBox(0.5, 2, 0.5);

	// �հ���(2)
	glPushMatrix();
	glTranslatef(0, 1, 0);
	// �հ��� 3
	glPushMatrix();
	glRotatef(pnum, 0, 0, 1);
	glTranslatef(0, 1, 0);
	drawBox(0.5, 2, 0.5);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	// �հ��� 2
	glPushMatrix();
	glRotatef(pnum, 0, 0, 1);
	glTranslatef(0, 1, 0);
	drawBox(0.5, 2, 0.5);

	// �հ���(2)
	glPushMatrix();
	glTranslatef(0, 1, 0);
	// �հ��� 4
	glPushMatrix();
	glRotatef(-pnum, 0, 0, 1);
	glTranslatef(0, 1, 0);
	drawBox(0.5, 2, 0.5);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix(); // �հ���(1)

	glPopMatrix(); // �հ���(2)

	glPopMatrix(); // ����
	glPopMatrix(); // ����
	glPopMatrix(); // ����
}

void drawWillE(){
	glPushMatrix();
	glTranslatef(0, 3, 0);
	//����
	drawBox(5, 5, 5);
	
	// ��
	glPushMatrix();
	glRotatef(headrotate, 0, 1, 0);
	glTranslatef(0, 3.5, 0);
	drawBox(1, 2, 1);

	// �Ӹ�
	glPushMatrix();
	glTranslatef(0, 1, 0);
	drawBox(2, 1, 1);

	glPopMatrix(); // �Ӹ�
	glPopMatrix(); // ��
	glPopMatrix(); // ����
}

void myDisplay() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//ī�޶� ����
	SetCamera();

	// ortho ũ��
	P_distance = 10;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, -1, 0, 0, 0, 0, 1, 0);

	// ���콺 Ŭ�� - ȸ��
	glRotated(angle, ax, ay, 0.0);
	

	// �� ����
	LightPosition();
	glDisable(GL_LIGHTING);
	// �� ����
	glEnable(GL_LIGHTING);
	//drawRobot();

	// ȥ���� �Ҵ�. 
	glEnable(GL_BLEND);
	// ���� ���۸� �б� �������� ����
	glDepthMask(GL_FALSE);
	// ������ ȿ���� ���� ȥ�� �Լ����� ����
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	// ��E
	glTranslatef(0, -4, 0);
	drawWillE();

	// ���� ���۸� ���� ���( ���� ���� )�� �ǵ���
	glDepthMask(GL_TRUE);
	// ȥ�� ���� 
	glDisable(GL_BLEND);
	
	glDisable(GL_LIGHTING);


	//�ٴ�
	drawPlane(10, 1);
	
	// ���� ����
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("12510096 ������ Sun");

	GLInit();

	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutReshapeFunc(reshape);

	glutSpecialFunc(special); // Ű���� Ư�� Ű
	glutMouseFunc(mouse); // ���콺 Ŭ�� �� �߻��Ǵ� �̺�Ʈ
	glutMotionFunc(motion); // ���콺 Ŭ�� �� �̵� �� �߻��Ǵ� �̺�Ʈ

	glutMainLoop();

	return 0;
}