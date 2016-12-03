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
// 마우스
GLdouble angle = 0.0; // 회전 각
GLfloat cx, cy, cz; // 클릭 좌표
GLfloat ca; // 클릭 앵글
// 마우스 이동량 배율

GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
GLfloat pos[] = { 3.0, 4.0, 5.0, 1.0 };
GLdouble ex = 0.0, ey = 0.0, ez = 10.0;
GLdouble tx = 0.0, ty = 0.0, tz = 0.0;
GLdouble ax = 0.0, ay = 1.0, az; // 회전 축

GLdouble sx, sy;
#define SCALE 360.0

////////////////////////////////////////////////
// 마지막 성분이 1이면 점광원이고, 0이면 방향광원(directional light source)

//재질의 정반사, 난반사, 주변광, 반질거림 특성으로 사용될 데이터
GLfloat matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat matDiff[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat matAmbi[] = { 0.5, 0.1, 0.1, 1.0 };
GLfloat matShin[] = { 200.0 };

// 광원의 정반사, 난반사, 주변광 특성으로 사용될 데이터
//GLfloat light[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lit_specular[] = { 1.0, 1.0f, 1.0f, 1.0f };
GLfloat lit_diffuse[] = { 0.0, 1.0f, 1.0f, 1.0f };
GLfloat lit_ambient[] = { 0.5, 1.0f, 1.0f, 1.0f };


// 광원의 위치로 사용될 데이터
GLfloat lightPos[] = { 1.0, 1.0, 1.0, 1.0 };//{ -1.0, 1.0, 1.0, 1.0 };

////////////////////////////////////////////////

// 조명과 재질의 특성을 준비된 데이터로 설정하는 함수
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

// 조명의 위치를 설정하는 함수
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
	glutPostRedisplay(); // 윈도우를 그려야 할 때만 그려줌 (glutIdleFunc를 안써도됨)
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
	case GLUT_DOWN:
		// 마우스 버튼을 누른 위치를 기록
		cx = x;
		cy = y;
		// 표시하고 있는 물체의 회전 각을 기록
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

	// 마우스 포인터 위치 윈도우의 상대적인 위치에 환율 용
	sx = 1.0 / (double)w;
	sy = 1.0 / (double)h;
}

void GLInit() {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// 조명의 특성과 재질의 특성을 설정
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
	// 바닥 상자
	glPushMatrix();
	glTranslatef(0, 1, 0);
	drawBox(3, 2, 3);

	// 기둥팔 1
	glPushMatrix();
	glTranslatef(0, 2, 0);
	drawBox(1, 2, 1);

	// 움직이는 팔1
	glPushMatrix();
	glTranslatef(0, 1, 0);
	glRotatef(num, 0, 0, 1);
	glTranslatef(0, 2.5, 0);
	drawBox(1, 5, 1);

	// 손가락(1)
	glPushMatrix();
	glTranslatef(0, 2.5, 0);
	// 손가락 1
	glPushMatrix();
	glRotatef(-pnum, 0, 0, 1);
	glTranslatef(0, 1, 0);
	drawBox(0.5, 2, 0.5);

	// 손가락(2)
	glPushMatrix();
	glTranslatef(0, 1, 0);
	// 손가락 3
	glPushMatrix();
	glRotatef(pnum, 0, 0, 1);
	glTranslatef(0, 1, 0);
	drawBox(0.5, 2, 0.5);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	// 손가락 2
	glPushMatrix();
	glRotatef(pnum, 0, 0, 1);
	glTranslatef(0, 1, 0);
	drawBox(0.5, 2, 0.5);

	// 손가락(2)
	glPushMatrix();
	glTranslatef(0, 1, 0);
	// 손가락 4
	glPushMatrix();
	glRotatef(-pnum, 0, 0, 1);
	glTranslatef(0, 1, 0);
	drawBox(0.5, 2, 0.5);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix(); // 손가락(1)

	glPopMatrix(); // 손가락(2)

	glPopMatrix(); // 움팔
	glPopMatrix(); // 기팔
	glPopMatrix(); // 상자
}

void drawWillE(){
	glPushMatrix();
	glTranslatef(0, 3, 0);
	//몸통
	drawBox(5, 5, 5);
	
	// 목
	glPushMatrix();
	glRotatef(headrotate, 0, 1, 0);
	glTranslatef(0, 3.5, 0);
	drawBox(1, 2, 1);

	// 머리
	glPushMatrix();
	glTranslatef(0, 1, 0);
	drawBox(2, 1, 1);

	glPopMatrix(); // 머리
	glPopMatrix(); // 목
	glPopMatrix(); // 몸통
}

void myDisplay() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//카메라 설정
	SetCamera();

	// ortho 크기
	P_distance = 10;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, -1, 0, 0, 0, 0, 1, 0);

	// 마우스 클릭 - 회전
	glRotated(angle, ax, ay, 0.0);
	

	// 빛 설정
	LightPosition();
	glDisable(GL_LIGHTING);
	// 빛 실행
	glEnable(GL_LIGHTING);
	//drawRobot();

	// 혼합을 켠다. 
	glEnable(GL_BLEND);
	// 깊이 버퍼를 읽기 전용으로 설정
	glDepthMask(GL_FALSE);
	// 반투명 효과를 위한 혼합 함수들을 설정
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	// 윌E
	glTranslatef(0, -4, 0);
	drawWillE();

	// 깊이 버퍼를 보통 모드( 쓰기 가능 )로 되돌림
	glDepthMask(GL_TRUE);
	// 혼합 끈다 
	glDisable(GL_BLEND);
	
	glDisable(GL_LIGHTING);


	//바닥
	drawPlane(10, 1);
	
	// 스왑 버퍼
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("12510096 조광민 Sun");

	GLInit();

	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutReshapeFunc(reshape);

	glutSpecialFunc(special); // 키보드 특수 키
	glutMouseFunc(mouse); // 마우스 클릭 시 발생되는 이벤트
	glutMotionFunc(motion); // 마우스 클릭 후 이동 시 발생되는 이벤트

	glutMainLoop();

	return 0;
}