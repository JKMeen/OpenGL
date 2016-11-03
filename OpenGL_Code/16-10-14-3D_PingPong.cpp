#define GLUT_DISABLE_ATEXIT_HACK

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>
#include <conio.h> // getch(); 함수를 사용

//GLfloat ax, ay, az;
GLdouble angle = 0.0; // 회전 각
GLfloat cx, cy, cz; // 클릭 좌표
GLfloat ca; // 클릭 앵글
// 마우스 이동량 배율

GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
GLfloat pos[] = { 3.0, 4.0, 5.0, 1.0 };
GLdouble ex = 0.0, ey = 0.0, ez = 10.0;
GLdouble tx = 0.0, ty = 0.0, tz = 0.0;
GLdouble ax = 0.0, ay = 1.0, az; // 회전 축

double sx, sy;
#define SCALE 360.0

/////////////////////////////////////
float mvx= 0, mvz = 0;
float ballx = 0, bally = 0, ballz = 0;
float xc = 1, yc = 1, zc = 1;
float viewx = 0, viewy = 0, viewz = 0;

void drawRactangle(float xscale, float yscale, float zscale){
	/// 선 생성
	
	glColor3f(1, 0, 0);
	// 앞부분
	glBegin(GL_LINE_LOOP);
	glVertex3f(-xscale, -yscale, zscale);
	glVertex3f(xscale, -yscale, zscale);
	glVertex3f(xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, zscale);
	glEnd();
	// 뒷부분
	glBegin(GL_LINE_LOOP);
	glVertex3f(-xscale, yscale, -zscale);
	glVertex3f(xscale, yscale, -zscale);
	glVertex3f(xscale, -yscale, -zscale);
	glVertex3f(-xscale, -yscale, -zscale);
	glEnd();
	// 윗부분
	glBegin(GL_LINE_LOOP);
	glVertex3f(xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, -zscale);
	glVertex3f(xscale, yscale, -zscale);
	glEnd();
	// 아래 부분
	glBegin(GL_LINE_LOOP);
	glVertex3f(-xscale, -yscale, zscale);
	glVertex3f(xscale, -yscale, zscale);
	glVertex3f(xscale, -yscale, -zscale);
	glVertex3f(-xscale, -yscale, -zscale);
	glEnd();
	// 왼쪽
	glBegin(GL_LINE_LOOP);
	glVertex3f(-xscale, -yscale, zscale);
	glVertex3f(-xscale, yscale, zscale);
	glVertex3f(-xscale, yscale, -zscale);
	glVertex3f(-xscale, -yscale, -zscale);
	glEnd();
	// 오른쪽
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

// 마우스 입력
/*
void mouse(int x, int y){

}*/

void resize(int w, int h){
	// 마우스 포인터 위치 윈도우의 상대적인 위치에 환율 용
	sx = 1.0 / (double)w;
	sy = 1.0 / (double)h;
}

void motion(int x, int y){
	double dx, dy, a;

	// 마우스 포인터 위치의 끌기 시작 위치에서의 변위
	dx = (x - cx) * sx;
	dy = (y - cy) * sy;

	// 마우스 포인터 위치의 끌기 시작 위치에서의 거리
	a = sqrt(dx * dx + dy * dy);

	if (a != 0.0){
		// 거리를 각도로 환산하여 드래그 시작시의 회전 각에 가산
		angle = fmod(ca + SCALE * a, 360.0);

		// 마우스 포인터의 변위에서 회전축 벡터를 요청
		ax = dy / a;
		ay = dx / a;
		az = 0.0;

		// 도형의 재 묘화
		glutPostRedisplay();
	}
}

void mouse(int button, int direction, int x, int y)
{
	switch (direction){
	case GLUT_DOWN :
		// 마우스 버튼을 누른 위치를 기록
		cx = x;
		cy = y;
		// 표시하고 있는 물체의 회전 각을 기록
		ca = angle;
		break;
	default :
		break;
	}
}
// 키 입력
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

	// 벽 충돌 이벤트
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
	glutCreateWindow("12510096 조광민");

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkey);
	
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutReshapeFunc(resize);

	glutMouseFunc(mouse); // 마우스 클릭 시 발생되는 이벤트
	glutMotionFunc(motion); // 마우스 클릭 후 이동 시 발생되는 이벤트
	//glutPassiveMotionFunc(); // 마우스 클릭 안하고 이동 시 발생되는 이벤트

	glutMainLoop();

	return 0;
}
