#define GLUT_DISABLE_ATEXIT_HACK

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>
#include <conio.h> // getch(); 함수를 사용

GLfloat eyey = 3, eyex = 0, eyez = 0, tr = 0.01; // 시점 이동 변수
GLfloat pox = 0, poy = 0, poz = 0; // 포탑 회전 함수
GLfloat movex = 0, movey = 0, movez = 0; // 몸통 회전, 이동 함수
GLfloat tirerotate = 0; // 바퀴 회전
GLdouble delay = 1;
GLint fovy = 0; // 퍼스펙티브 뷰 시야 각도
GLfloat potan = 1, pomove = 0;

// 원기둥
void drawCircle(float radius, float size){
	glBegin(GL_POLYGON);

	int nPoints = 20;
	float angle = 0.0;
	float step = (3.14159*2.0) / nPoints;
	// 반복문 내에서 여러 개의 정점 좌표를 계산한 뒤에 지정하는 방식
	// 여기서는 원을 이루는 정점들을 계산
	while (angle <3.14159*2.0) {
		glVertex3f(radius*cos(angle), size, radius*sin(angle));
		glVertex3f(radius*cos(angle), -size, radius*sin(angle));
		glVertex3f(radius*cos(angle + step), -size, radius*sin(angle + step));
		glVertex3f(radius*cos(angle), size, radius*sin(angle));
		angle += step;
	}
	glEnd();

}

// 바퀴(원기둥)
void drawtire(float radius, float size, float msize, int Points){
	glBegin(GL_POLYGON);

	int nPoints = Points;
	float angle = 0.0;
	float step = (3.14159*2.0) / nPoints;
	// 반복문 내에서 여러 개의 정점 좌표를 계산한 뒤에 지정하는 방식
	// 여기서는 원을 이루는 정점들을 계산
	while (angle <3.14159*2.0) {
		glVertex3f(size, radius*cos(angle), radius*sin(angle));
		glVertex3f(msize, radius*cos(angle), radius*sin(angle));
		glVertex3f(msize, radius*cos(angle + step), radius*sin(angle + step));
		glVertex3f(size, radius*cos(angle), radius*sin(angle));
		angle += step;
	}
	glEnd();
}

// 지붕
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

	// 앞부분
	glVertex3f(-xscale, -yscale, zscale);
	glVertex3f(xscale, -yscale, zscale);
	glVertex3f(xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, zscale);

	// 뒷부분
	glVertex3f(-xscale, yscale, -zscale);
	glVertex3f(xscale, yscale, -zscale);
	glVertex3f(xscale, -yscale, -zscale);
	glVertex3f(-xscale, -yscale, -zscale);

	// 윗부분
	glVertex3f(xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, -zscale);
	glVertex3f(xscale, yscale, -zscale);

	// 아래 부분
	glVertex3f(-xscale, -yscale, zscale);
	glVertex3f(xscale, -yscale, zscale);
	glVertex3f(xscale, -yscale, -zscale);
	glVertex3f(-xscale, -yscale, -zscale);

	// 왼쪽
	glVertex3f(-xscale, -yscale, zscale);
	glVertex3f(-xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, -zscale);
	glVertex3f(-xscale, -yscale, -zscale);

	// 오른쪽
	glVertex3f(xscale, -yscale, zscale);
	glVertex3f(xscale, yscale, zscale);
	glVertex3f(xscale, yscale, -zscale);
	glVertex3f(xscale, -yscale, -zscale);
	glEnd();

	/// 선 생성
	glBegin(GL_LINE_STRIP);
	glColor3f(1, 0, 0);
	// 앞부분
	glVertex3f(-xscale, -yscale, zscale);
	glVertex3f(xscale, -yscale, zscale);
	glVertex3f(xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, zscale);

	// 뒷부분
	glVertex3f(-xscale, yscale, -zscale);
	glVertex3f(xscale, yscale, -zscale);
	glVertex3f(xscale, -yscale, -zscale);
	glVertex3f(-xscale, -yscale, -zscale);

	// 윗부분
	glVertex3f(xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, -zscale);
	glVertex3f(xscale, yscale, -zscale);

	// 아래 부분
	glVertex3f(-xscale, -yscale, zscale);
	glVertex3f(xscale, -yscale, zscale);
	glVertex3f(xscale, -yscale, -zscale);
	glVertex3f(-xscale, -yscale, -zscale);

	// 왼쪽
	glVertex3f(-xscale, -yscale, zscale);
	glVertex3f(-xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, -zscale);
	glVertex3f(-xscale, -yscale, -zscale);

	// 오른쪽
	glVertex3f(xscale, -yscale, zscale);
	glVertex3f(xscale, yscale, zscale);
	glVertex3f(xscale, yscale, -zscale);
	glVertex3f(xscale, -yscale, -zscale);
	glEnd();
}

void drawPlane(void) { // 바닥 타일 생성
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

// 키 입력
void  keyboard(unsigned char key, int x, int y)
{
	int   mod;
	switch (key) {
	// 시점 이동
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
	// 포탑
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
	// 이동
	case GLUT_KEY_UP:
		movez -= 1;
		tirerotate -= 30; // 타이어 회전
		break;
	case GLUT_KEY_DOWN:
		movez += 1;
		tirerotate += 30; // 타이어 회전
		break;
	// 몸통 회전
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
			//glRotatef(45, 0, 0, 1); // 로테이션 각도, x, y, z축 지정
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
	// 시야각, 종횡비, 전방절단면, 후방절단면
	// 카메라의 상을 맻는 최소 거리와 최대 거리를 정해 입체감 있게 만듬
	glMatrixMode(GL_MODELVIEW); // 
	glLoadIdentity();

	if (delay == -1){
		gluLookAt(1, 0, 0, 0, 0, 0, 0, 1, 0); //카메라 회전
	}
	else {
		gluLookAt(2.0*cos(eyex), eyey, 2.0*sin(eyex), 0, 1.5, 0, 0, 1, 0); //카메라 회전
	}

	glPushMatrix();
	// 이동 및 회전 함수
	//glRotatef(movex, 0, 1, 0);
	glTranslatef(0, 0, -movez);
	drawPlane();
	glLineWidth(1);
	glPopMatrix();

	// 탱크 몸통
	glPushMatrix();

		glColor3f(1, 1, 1);
		glTranslatef(0, 0.8, 0.5);
		drawRactangle(2, 0.6, 3.5);

		// 탱크 포탑
		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(0, 1, 0.5);
		glRotated(pox, 0, 1, 0);
		drawRactangle(1.5, 0.5, 2);

		// 탱크 포신
		glPushMatrix();
		glColor3f(1, 0, 1);
		glTranslatef(0, 0, -1);
		glRotatef(90, 0, 1, 0);
		glRotatef(poy, 0, 0, 1);
		drawtire(0.3, 5, -0.5, 10);

		// 포탄
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

		glPopMatrix(); // 탱크 포신

		glPopMatrix(); // 탱크 포탑

		// 바퀴1-0 (좌측)
		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(2.5, 0, -2); // 위치 설정
		glRotatef(tirerotate, 1, 0, 0); // 타이어 회전
		drawtire(1, 0.4, -0.5, 5);
		glPopMatrix(); // 바퀴1-0
		/*
		// 바퀴1-1
		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(2.5, 0, 0.5);
		glRotatef(tirerotate, 1, 0, 0);
		drawtire(1, 0.4, -0.5, 5);
		glPopMatrix(); // 바퀴1-1
		*/
		// 바퀴1-2
		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(2.5, 0, 2.5);
		glRotatef(tirerotate, 1, 0, 0);
		drawtire(1, 0.4, -0.5, 5);
		glPopMatrix(); // 바퀴1-2

		// 바퀴2-0 (우측)
		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(-2.5, 0, -2);
		glRotatef(tirerotate, 1, 0, 0);
		drawtire(1, -0.4, 0.5, 5);
		glPopMatrix(); // 바퀴2-0
		/*
		// 바퀴2-1
		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(-2.5, 0, 0.5);
		glRotatef(tirerotate, 1, 0, 0);
		drawtire(1, -0.4, 0.5, 5);
		glPopMatrix(); // 바퀴2-1
		*/
		// 바퀴2-2
		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(-2.5, 0, 2.5);
		glRotatef(tirerotate, 1, 0, 0);
		drawtire(1, -0.4, 0.5, 5);
		glPopMatrix(); // 바퀴2-2

	glPopMatrix(); // 탱크 몸통

		
	
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("12510096 조광민 오픈지엘 시험");

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutMainLoop();

	return 0;
}