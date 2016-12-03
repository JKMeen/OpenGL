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
GLfloat num = 15, pnum = 90, headrotate = 180, headupdown = 0; // �Ӹ� ȸ��
GLfloat armupdown = 0; // �� ȸ��
GLfloat handrotate = 45; // �� ���� ȸ��
GLfloat movex = 0, movez = 0, rot = 0, movenum = -1;
GLfloat P_distance = 0, Prt;
GLint Cameranum = 0, Boxup = -1, Boxx = 0, Boxy = 3, Boxz = 0, Boxcase = 0, Boxrotate = 0;
GLint Cameraone = 10, Cameradelay= -1;

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

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		// �� ���� ȸ��
		armupdown += 2;
		if (armupdown >= 45) armupdown = 45;
		break;
	case 's':
		// �� ���� ȸ��
		armupdown -= 2;
		if (armupdown <= -45) armupdown = -45;
		break;
	case 'b':
		// ����
		handrotate += 2;
		if (handrotate >= 45) handrotate = 45;
		break;
	case 'v':
		// ����
		handrotate -= 2;
		if (handrotate <= 15) handrotate = 15;
		break;
	case 'z':
		// ī�޶� ��ȯ
		Cameranum += 1;
		if (Cameranum > 6) Cameranum = 0;
		break;
	case 'p':
		Cameraone -= 10;
		if (Cameraone == 10){
			Cameraone = 10;
		}
		break;
	case 'o':
		Cameraone += 10;
		if (Cameraone == 50){
			Cameraone = 50;
		}
		break;
	// ���콺 ȸ�� ���󺹱�
	case 'i':
		angle = 0, ax = 0, ay = 0;
		break;
	case 'c':
		// �׷�
		if (handrotate <= 30 && armupdown <= 0){
			if (43 - movez <= 4 && 43 - movez >= -4){
				Cameranum = 0;
				Boxx = movex*movenum;
				Boxz = movez*movenum;
				Boxrotate = headrotate;
				Boxcase = 0;
				Boxup *= -1;
			}
			else if (43 + movez <= 4 && 43 + movez >= -4){
				Cameranum = 0;
				Boxx = movex*movenum;
				Boxz = movez*movenum-100;
				Boxrotate = headrotate;
				Boxcase = 1;
				Boxup *= -1;
			}
			else if (43 - movex <= 4 && 43 - movex >= -4){
				Cameranum = 0;
				Boxx = movex*movenum+50;
				Boxz = movez*movenum-50;
				Boxrotate = headrotate;
				Boxcase = 2;
				Boxup *= -1;
			}
			
			else if (43 + movex <= 4 && 43 + movex >= -4){
				Cameranum = 0;
				Boxx = movex*movenum-50;
				Boxz = movez*movenum-50;
				Boxrotate = headrotate;
				Boxcase = 3;
				Boxup *= -1;
			}
		}
	}

	/*// �׷�
	if (43 - movez <= 4 && 43 - movez >= -4 && handrotate <= 30 && armupdown <= 0 && key == 'c'){
		Cameranum = 0;
		Boxz = movez*movenum;
		Boxx = headrotate;
		Boxup *= -1;
	}*/

	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		num -= 2;
		if (num <= 0) num = 0;
		// �̵�
		movex += sin(headrotate * 3.14159 / 180);
		movez -= cos(headrotate * 3.14159 / 180);
		
		// �Ӹ� ���ٿ�
		headupdown -= 3;
		if (headupdown < 0) headupdown = 0;
		break;
	case GLUT_KEY_DOWN:
		num += 2;
		if (num >= 180) num = 180;
		// �̵�
		movex -= sin(headrotate * 3.14159 / 180);
		movez += cos(headrotate * 3.14159 / 180);
		
		// �Ӹ� ���ٿ�
		headupdown += 3;
		if (headupdown > 15) headupdown = 15;
		break;
		// ���� ������ ȸ��
	case GLUT_KEY_LEFT:
		rot += 3;
		// ���� ȸ��
		pnum += 2;
		if (pnum >= 75) pnum = 75;
		// �Ӹ� ȸ��
		headrotate += 15;
		if (headrotate == 360)
			headrotate = 0;
		break;
	case GLUT_KEY_RIGHT:
		rot -= 3;
		// ���� ȸ��
		pnum -= 2;
		if (pnum <= 15) pnum = 15;
		// �Ӹ� ȸ��
		headrotate -= 15;
		if (headrotate == 0)
			headrotate = 0;
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
	glOrtho(-P_distance, P_distance, -P_distance, P_distance, -P_distance * 5, P_distance * 5);
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
	glLineWidth(3);
	glColor3f(0.3, 0.3, 0.3);
	glutWireCube(1.1);
	glLineWidth(1);
	glPopMatrix();
}

void drawhead(int num){
	glPushMatrix();
	glColor3f(0, 0.7, 0.7);
	glTranslatef(0, 1, 0);
	glRotatef(-headupdown, 1, 0, 0);
	glRotatef(-15 * num, 0, 0, 1);
	glTranslatef(1 * num, 0, -1);
	drawBox(2, 1, 3);
	glPopMatrix(); // �Ӹ�1
}

void drawArm(int num){
	// ���
	glPushMatrix();
	glColor3f(0.5, 0.5, 0);
	glTranslatef(2.5*num, 2, 0);
	glRotatef(armupdown, 1, 0, 0);
	drawBox(1, 1, 1);

	// ��-1
	glPushMatrix();
	glColor3f(0.5, 0.5, 0);
	glTranslatef(1 * num, 0, 0);
	glRotatef((-handrotate*num) + (30 * num), 0, 1, 0);
	glTranslatef(0, 0, -1);
	drawBox(1, 1, 3);

	// ��-2
	glPushMatrix();
	glColor3f(0, 0.7, 0.7);
	glTranslatef(0, 0, -2.5);
	drawBox(0.5, 0.5, 2);
	////////////////////////////////////////////
	// ���� 1-1
	glPushMatrix();
	glColor3f(0, 0.7, 0.7);
	glTranslatef(0, 0, -1);
	glRotatef(handrotate, 0, 1, 0);
	glTranslatef(0, 0, -0.5);
	drawBox(0.1, 0.5, 1);

	// ���� 1-2
	glPushMatrix();
	glColor3f(0, 0.7, 0.7);
	glTranslatef(0, 0, -0.5);
	glRotatef(-handrotate, 0, 1, 0);
	glTranslatef(0, 0, -0.5);
	drawBox(0.1, 0.5, 1);

	glPopMatrix(); // ���� 1-2
	glPopMatrix(); // ���� 1-1

	// ���� 2-1
	glPushMatrix();
	glColor3f(0, 0.7, 0.7);
	glTranslatef(0, 0, -1);
	glRotatef(-handrotate, 0, 1, 0);
	glTranslatef(0, 0, -0.5);
	drawBox(0.1, 0.5, 1);

	// ���� 2-2
	glPushMatrix();
	glColor3f(0, 0.7, 0.7);
	glTranslatef(0, 0, -0.5);
	glRotatef(handrotate, 0, 1, 0);
	glTranslatef(0, 0, -0.5);
	drawBox(0.1, 0.5, 1);

	glPopMatrix(); // ���� 2-2
	glPopMatrix(); // ���� 2-1
	//////////////////////////////////////////
	glPopMatrix(); // ��-2
	glPopMatrix(); // ��-1

	glPopMatrix(); // ���
}

void drawWillE(){
	glPushMatrix();
	glTranslatef(0, 4, 0);
	//����
	glColor3f(0.5, 0.5, 0);
	drawBox(5, 5, 5);
	////////////////////////////////////////////////////////////////////////////////
	// ��
	glPushMatrix();
	glColor3f(0, 0.7, 0.7);
	glTranslatef(0, 2.5, 0);
	glRotatef(headupdown, 1, 0, 0);
	//glRotatef(headrotate, 0, 1, 0); // �¿� ȸ��
	glTranslatef(0, 1, 0);
	drawBox(1, 2, 1);

	// �Ӹ�1
	drawhead(1);

	// �Ӹ�2
	drawhead(-1);

	glPopMatrix(); // ��

	// ���� ��
	drawArm(1);

	// ������ ��
	drawArm(-1);

	glPopMatrix();
	glPopMatrix();

	// ���� ����
	glPushMatrix();
	glColor3f(1, 0, 1);
	glTranslatef(-2.5, 0, 0);
	drawBox(2, 2, 6);
	glPopMatrix; //����

	// ������ ����
	glPushMatrix();
	glColor3f(1, 0, 1);
	glTranslatef(5, 0, 0);
	drawBox(2, 2, 6);
	glPopMatrix; //����

	///////////////////////////////////////////////////////////////////////////
	glPopMatrix(); // ����
}

void drawBoxLine(int x, int z){
	glRotatef(headrotate, 0, 1, 0);
	glTranslatef(movex*movenum, 0, movez*movenum);
	glTranslatef(50*x, Boxy, 50*z);
	glLineWidth(3);
	glBegin(GL_POLYGON);
	glVertex3f(-3.5, -3.5, -3.5);
	glVertex3f(3.5, -3.5, -3.5);
	glVertex3f(3.5, -3.5, 3.5);
	glVertex3f(-3.5, -3.5, 3.5);
	glEnd();
	glLineWidth(1);
}

void drawBox(){
	glColor3f(0.3, 0.3, 0.3);
	if (Boxup == -1){
		glRotatef(headrotate, 0, 1, 0);
		switch (Boxcase){
		case 0: glColor3f(1, 0, 0); glTranslatef(movex*movenum, 0, movez*movenum); break;
		case 1: glColor3f(0, 0, 1); glTranslatef(movex*movenum, 0, movez*movenum - 100); break;
		case 2: glColor3f(0, 1, 0); glTranslatef(movex*movenum + 50, 0, movez*movenum - 50); break;
		case 3: glColor3f(1, 1, 0); glTranslatef(movex*movenum - 50, 0, movez*movenum - 50); break;
		}
		
	}
	else if (Boxup == 1){
		glRotatef(Boxrotate, 0, 1, 0);
		glTranslatef(Boxx, 0, Boxz); 
	}
	
	glTranslatef(0, Boxy, 50);
	drawBox(7, 7, 7);
}

void myDisplay() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//ī�޶� ����
	SetCamera();

	// ortho ũ��
	P_distance = Cameraone;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	switch (Cameranum){
	case 0: gluLookAt(1, 0, 1, 0, 1, 0, 0, 1, 0); break; // �밢��
	case 1: gluLookAt(0, -1,1, 0, 0, 0, 0, 1, 0); break; // ����
	case 2: gluLookAt(0, 1, 1, 0, 1, 0, 0, 1, 0); break; // �ո�
	case 3: gluLookAt(0, 1, 1, 0, 1, 0, 0, 1, 0); break; // �޸�
	case 4: gluLookAt(-1, 0, 0, 0, 0, 0, 0, 1, 0); break; // ����
	case 5: gluLookAt(1, 0, 0, 0, 0, 0, 0, 1, 0); break; // ������
	}

	// ���콺 Ŭ�� - ȸ��
	glRotated(angle, ax, ay, 0.0);


	// �� ����
	LightPosition();
	//glDisable(GL_LIGHTING);

	// ȥ���� �Ҵ�. 
	glEnable(GL_BLEND);
	// ���� ���۸� �б� �������� ����
	glDepthMask(GL_FALSE);
	// ������ ȿ���� ���� ȥ�� �Լ����� ����
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glTranslatef(0, -3, 0);

	// ��E
	glPushMatrix();
	drawWillE();
	glPopMatrix();

	// ����
	glPushMatrix();
	drawBox();
	glPopMatrix();

	// ���� ����
	glPushMatrix();
	glColor3f(0.5, 0, 0);
	drawBoxLine(0, 1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0.5);
	drawBoxLine(0, -1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0.5, 0);
	drawBoxLine(1, 0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0);
	drawBoxLine(-1, 0);
	glPopMatrix();

	//�ٴ�
	glPushMatrix();
	glRotatef(headrotate, 0, 1, 0);
	glTranslatef(movex*movenum, 0, movez*movenum);
	drawPlane(100, 5);
	glPopMatrix();

	// ���� ���۸� ���� ���( ���� ���� )�� �ǵ���
	glDepthMask(GL_TRUE);
	// ȥ�� ���� 
	glDisable(GL_BLEND);

	glDisable(GL_LIGHTING);

	// ���� ����
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("12510096 ������ ��E");

	GLInit();

	glutDisplayFunc(myDisplay);
	glutReshapeFunc(reshape);
	glutIdleFunc(myDisplay);

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special); // Ű���� Ư�� Ű
	glutMouseFunc(mouse); // ���콺 Ŭ�� �� �߻��Ǵ� �̺�Ʈ
	glutMotionFunc(motion); // ���콺 Ŭ�� �� �̵� �� �߻��Ǵ� �̺�Ʈ

	glutMainLoop();

	return 0;
}