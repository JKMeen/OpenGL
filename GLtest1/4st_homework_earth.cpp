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
GLint num = 8;
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
		num -= 1;
		if (num <= 0) num = 0;
		break;
	case GLUT_KEY_DOWN:
		num += 1;
		if (num >= 8) num = 8;
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
	for (int j = -w; j <= w; j+=interval){
		
		glVertex3f(j, -500, -w);
		glVertex3f(j, -500, w);

		glVertex3f(-w, -500, j);
		glVertex3f(w, -500, j);
	}
	glEnd();
}

void drawPlanet(float R, float G, float B, float Revolution, float Rx, float Ry, float Rz, float distance, float rotation, float rx, float ry, float rz, float radius){
	glColor3f(R, G, B);
	glRotatef(Revolution, Rx, Ry, Rz); // ����
	glTranslatef(distance, 0, 0); // �¾���� �Ÿ�
	glRotatef(rotation, rx, ry, rz); // ����
	glutWireSphere(radius, 20, 20); 
	//glutSolidSphere(radius, 20, 20); // ����� (������, �浵, ����)
}

void drawMoon(float distance, int num, float radius){ // ��
	glPushMatrix();
	glRotatef(-srt[num], 1, 0, 0);
	glColor3f(1, 1, 0);
	glRotatef(srt[num], 0, 1, 0);
	glTranslatef(distance, 0, 0);
	glRotatef(srt[num], 0, 1, 0);
	glRotatef(srt[num], 0, 0, 1);
	glutSolidSphere(radius, 10, 10); // ����� (������, �浵, ����)
	glPopMatrix();
}

void displayPlanet(){
	// �¾�
	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotatef(srt[0], 0, 1, 0); // ����
	//glutWireSphere(radius, 20, 20); 
	//glutWireSphere(27*2, 20, 20); // ����� (������, �浵, ����)
	drawPlanet(1, 0, 0, 0, 0, 0, 0, 0, srt[0], 0, 1, 0, 27 * 2);
	glPopMatrix();

	// ����(Mercury)
	glPushMatrix();
	glColor3f(0, 0, 1);
	drawPlanet(0, 0, 1, rt[0], 0, 1, 0, 57.9, srt[1], 1, 0, 0, 0.25 * 10);
	glPopMatrix();

	// �ݼ�(Venus) 
	glPushMatrix();
	drawPlanet(1, 1, 0, rt[1], 0, 1, 0, 108.2, srt[2], 1, 0, 0, 0.6 * 10);
	glPopMatrix();

	// ����(Earth)
	glPushMatrix();
	drawPlanet(0, 1, 0, rt[2], 0, 1, 0, 149.6, srt[3], 1, 0, 0, 0.64 * 10);
	drawMoon(10, 1, 1.17);
	glPopMatrix();

	// ȭ��(Mars)
	glPushMatrix();
	drawPlanet(1, 0, 0, rt[3], 0, 1, 0, 228.0, srt[4], 1, 0, 0, 0.34 * 10);
	drawMoon(10, 1, 1.3);
	drawMoon(10, 2, 1.7);
	glPopMatrix();

	// ��(Jupiter)
	glPushMatrix();
	drawPlanet(0.5, 0, 0, rt[4], 0, 1, 0, 778.3, srt[5], 1, 0, 0, 7.1 * 10);
	drawMoon(100, 2, 3);
	drawMoon(100, 3, 9);
	drawMoon(100, 4, 5);
	glPopMatrix();

	// �伺(Saturn)
	glPushMatrix();
	drawPlanet(1, 0.5, 0, rt[5], 0, 1, 0, 1427.0, srt[6], 1, 0, 0, 6.0 * 10);
	drawMoon(90, 3, 4);
	drawMoon(90, 1, 7);
	drawMoon(90, 4, 6);
	glPushMatrix();
	glutWireSphere(120, 2, 20);
	glPopMatrix();
	glPopMatrix();

	// õ�ռ�(Uranus)
	glPushMatrix();
	drawPlanet(0, 0, 0.7, rt[6], 0, 1, 0, 2900.0, srt[7], 1, 0, 0, 2.79 * 10);
	glPopMatrix();

	// �ؿռ�(Neptune)
	glPushMatrix();
	drawPlanet(0, 0, 0.9, rt[7], 0, 1, 0, 4497.0, srt[8], 1, 0, 0, 2.43 * 10);
	glPopMatrix();
}

void setRotation(){
	// ����(Mercury)   / ������ 2500  / ���� 88��(4736)   / ���� 59��        / ���� x
	// �ݼ�(Venus)     / ������ 6000  / ���� 225��(3502)  / ���� 223��       / ���� x
	// ����(Earth)     / ������ 6400  / ���� 365��(2978)  / ���� 1��         / ���� 1��
	// ȭ��(Mars)      / ������ 3400  / ���� 687��(2408)  / ���� 24�ð� 37�� / ���� 2��
	// ��(Jupiter)   / ������ 71000 / ���� 11.9��(1306) / ���� 9�ð� 50��  / ���� 16��
	// �伺(Saturn)    / ������ 60000 / ���� 29.5��(965)  / ���� 10�ð� 14�� / ���� 23��/ ��
	// õ�ռ�(Uranus)  / ������ 27900 / ���� 84��(681)    / ���� 15�ð�      / ���� 15�� / ��
	// �ؿռ�(Neptune) / ������ 24300 / ���� 165��(544)   / ���� 15�ð� 18�� / ���� 5�� / ��
	//* �� / ������ 1700 / ���� 30�� / ���� 273��
	for (int i = 0; i <= 7; i++){ // ����
		switch (i){
		case 0: rt[i] += 0.4736; break;
		case 1: rt[i] += 0.3502; break;
		case 2: rt[i] += 0.2978; break;
		case 3: rt[i] += 0.2408; break;
		case 4: rt[i] += 0.1306; break;
		case 5: rt[i] += 0.0965; break;
		case 6: rt[i] += 0.0681; break;
		case 7: rt[i] += 0.0544; break;
		}
		if (rt[i] >= 360){
			rt[i] = 0;
		}
	}

	for (int i = 0; i <= 8; i++){ // ����
		switch (i){
		case 0: srt[i] += 0.59; break;  // �¾�
		case 1: srt[i] += 0.59; break;  // ����
		case 2: srt[i] += 0.223; break;  // �ݼ�
		case 3: srt[i] += 1.0; break;  // ����
		case 4: srt[i] += 1.1; break;  // ȭ��
		case 5: srt[i] += 2.5; break;  // ��
		case 6: srt[i] += 2.3; break;  // �伺
		case 7: srt[i] += 4.16; break;  // õ�ռ�
		case 8: srt[i] += 4.162; break;  // �ؿռ�
		}
		if (srt[i] >= 360){
			srt[i] = 0;
		}
	}

	switch (num){
	case 0: Prt = 0;  P_distance = 27.5; break;
	case 1: Prt = rt[0];  P_distance = 57.9 + 1; break;
	case 2: Prt = rt[1];  P_distance = 108.2 + 1; break;
	case 3: Prt = rt[2];  P_distance = 149.6 + 1; break;
	case 4: Prt = rt[3];  P_distance = 228.0 + 1; break;
	case 5: Prt = rt[4];  P_distance = 778.3 + 8; break;
	case 6: Prt = rt[5];  P_distance = 1427.0 + 7; break;
	case 7: Prt = rt[6];  P_distance = 2900.0 + 3; break;
	case 8: Prt = rt[7];  P_distance = 4497.0 + 3; break;
	}
}

void SetCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-P_distance, P_distance, -P_distance, P_distance, -P_distance, P_distance);
	gluPerspective(0, aspRatio, 0.1, 10000);
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

void myDisplay() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//ī�޶� ����
	SetCamera();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3*cos(10.0), 1, 3*sin(10.0), 0, 0, 0, 0, 1, 0);

	// �� ����
	LightPosition();
	glDisable(GL_LIGHTING);

	// ���콺 Ŭ�� - ȸ��
	glRotated(angle, ax, ay, 0.0);

	// ���� / ���� ����
	setRotation();

	drawPlane(1000, 100);

	// �� ����
	glEnable(GL_LIGHTING);
	// ȥ���� �Ҵ�. 
	glEnable(GL_BLEND);
	// ���� ���۸� �б� �������� ����
	glDepthMask(GL_FALSE);
	// ������ ȿ���� ���� ȥ�� �Լ����� ����
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	
	// �� �༺ ���÷���
	displayPlanet();

	// ���� ���۸� ���� ���( ���� ���� )�� �ǵ���
	glDepthMask(GL_TRUE);
	// ȥ�� ���� 
	glDisable(GL_BLEND);

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