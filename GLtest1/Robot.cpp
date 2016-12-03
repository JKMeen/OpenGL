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
GLfloat num = 15, pnum = 90, headrotate = 180, headupdown = 0; // 머리 회전
GLfloat armupdown = 0; // 팔 회전
GLfloat handrotate = 45; // 손 집게 회전
GLfloat movex = 0, movez = 0, rot = 0, movenum = -1;
GLfloat P_distance = 0, Prt;
GLint Cameranum = 0, Boxup = -1, Boxx = 0, Boxy = 3, Boxz = 0, Boxcase = 0, Boxrotate = 0;
GLint Cameraone = 10, Cameradelay= -1;

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

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		// 팔 상하 회전
		armupdown += 2;
		if (armupdown >= 45) armupdown = 45;
		break;
	case 's':
		// 팔 상하 회전
		armupdown -= 2;
		if (armupdown <= -45) armupdown = -45;
		break;
	case 'b':
		// 집게
		handrotate += 2;
		if (handrotate >= 45) handrotate = 45;
		break;
	case 'v':
		// 집게
		handrotate -= 2;
		if (handrotate <= 15) handrotate = 15;
		break;
	case 'z':
		// 카메라 변환
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
	// 마우스 회전 원상복귀
	case 'i':
		angle = 0, ax = 0, ay = 0;
		break;
	case 'c':
		// 그랩
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

	/*// 그랩
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
		// 이동
		movex += sin(headrotate * 3.14159 / 180);
		movez -= cos(headrotate * 3.14159 / 180);
		
		// 머리 업다운
		headupdown -= 3;
		if (headupdown < 0) headupdown = 0;
		break;
	case GLUT_KEY_DOWN:
		num += 2;
		if (num >= 180) num = 180;
		// 이동
		movex -= sin(headrotate * 3.14159 / 180);
		movez += cos(headrotate * 3.14159 / 180);
		
		// 머리 업다운
		headupdown += 3;
		if (headupdown > 15) headupdown = 15;
		break;
		// 왼쪽 오른쪽 회전
	case GLUT_KEY_LEFT:
		rot += 3;
		// 몸통 회전
		pnum += 2;
		if (pnum >= 75) pnum = 75;
		// 머리 회전
		headrotate += 15;
		if (headrotate == 360)
			headrotate = 0;
		break;
	case GLUT_KEY_RIGHT:
		rot -= 3;
		// 몸통 회전
		pnum -= 2;
		if (pnum <= 15) pnum = 15;
		// 머리 회전
		headrotate -= 15;
		if (headrotate == 0)
			headrotate = 0;
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
	glOrtho(-P_distance, P_distance, -P_distance, P_distance, -P_distance * 5, P_distance * 5);
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
	glPopMatrix(); // 머리1
}

void drawArm(int num){
	// 어깨
	glPushMatrix();
	glColor3f(0.5, 0.5, 0);
	glTranslatef(2.5*num, 2, 0);
	glRotatef(armupdown, 1, 0, 0);
	drawBox(1, 1, 1);

	// 팔-1
	glPushMatrix();
	glColor3f(0.5, 0.5, 0);
	glTranslatef(1 * num, 0, 0);
	glRotatef((-handrotate*num) + (30 * num), 0, 1, 0);
	glTranslatef(0, 0, -1);
	drawBox(1, 1, 3);

	// 팔-2
	glPushMatrix();
	glColor3f(0, 0.7, 0.7);
	glTranslatef(0, 0, -2.5);
	drawBox(0.5, 0.5, 2);
	////////////////////////////////////////////
	// 집게 1-1
	glPushMatrix();
	glColor3f(0, 0.7, 0.7);
	glTranslatef(0, 0, -1);
	glRotatef(handrotate, 0, 1, 0);
	glTranslatef(0, 0, -0.5);
	drawBox(0.1, 0.5, 1);

	// 집게 1-2
	glPushMatrix();
	glColor3f(0, 0.7, 0.7);
	glTranslatef(0, 0, -0.5);
	glRotatef(-handrotate, 0, 1, 0);
	glTranslatef(0, 0, -0.5);
	drawBox(0.1, 0.5, 1);

	glPopMatrix(); // 집게 1-2
	glPopMatrix(); // 집게 1-1

	// 집게 2-1
	glPushMatrix();
	glColor3f(0, 0.7, 0.7);
	glTranslatef(0, 0, -1);
	glRotatef(-handrotate, 0, 1, 0);
	glTranslatef(0, 0, -0.5);
	drawBox(0.1, 0.5, 1);

	// 집게 2-2
	glPushMatrix();
	glColor3f(0, 0.7, 0.7);
	glTranslatef(0, 0, -0.5);
	glRotatef(handrotate, 0, 1, 0);
	glTranslatef(0, 0, -0.5);
	drawBox(0.1, 0.5, 1);

	glPopMatrix(); // 집게 2-2
	glPopMatrix(); // 집게 2-1
	//////////////////////////////////////////
	glPopMatrix(); // 팔-2
	glPopMatrix(); // 팔-1

	glPopMatrix(); // 어깨
}

void drawWillE(){
	glPushMatrix();
	glTranslatef(0, 4, 0);
	//몸통
	glColor3f(0.5, 0.5, 0);
	drawBox(5, 5, 5);
	////////////////////////////////////////////////////////////////////////////////
	// 목
	glPushMatrix();
	glColor3f(0, 0.7, 0.7);
	glTranslatef(0, 2.5, 0);
	glRotatef(headupdown, 1, 0, 0);
	//glRotatef(headrotate, 0, 1, 0); // 좌우 회전
	glTranslatef(0, 1, 0);
	drawBox(1, 2, 1);

	// 머리1
	drawhead(1);

	// 머리2
	drawhead(-1);

	glPopMatrix(); // 목

	// 왼쪽 팔
	drawArm(1);

	// 오른쪽 팔
	drawArm(-1);

	glPopMatrix();
	glPopMatrix();

	// 왼쪽 바퀴
	glPushMatrix();
	glColor3f(1, 0, 1);
	glTranslatef(-2.5, 0, 0);
	drawBox(2, 2, 6);
	glPopMatrix; //바퀴

	// 오른쪽 바퀴
	glPushMatrix();
	glColor3f(1, 0, 1);
	glTranslatef(5, 0, 0);
	drawBox(2, 2, 6);
	glPopMatrix; //바퀴

	///////////////////////////////////////////////////////////////////////////
	glPopMatrix(); // 몸통
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
	//카메라 설정
	SetCamera();

	// ortho 크기
	P_distance = Cameraone;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	switch (Cameranum){
	case 0: gluLookAt(1, 0, 1, 0, 1, 0, 0, 1, 0); break; // 대각선
	case 1: gluLookAt(0, -1,1, 0, 0, 0, 0, 1, 0); break; // 윗면
	case 2: gluLookAt(0, 1, 1, 0, 1, 0, 0, 1, 0); break; // 앞면
	case 3: gluLookAt(0, 1, 1, 0, 1, 0, 0, 1, 0); break; // 뒷면
	case 4: gluLookAt(-1, 0, 0, 0, 0, 0, 0, 1, 0); break; // 왼쪽
	case 5: gluLookAt(1, 0, 0, 0, 0, 0, 0, 1, 0); break; // 오른쪽
	}

	// 마우스 클릭 - 회전
	glRotated(angle, ax, ay, 0.0);


	// 빛 설정
	LightPosition();
	//glDisable(GL_LIGHTING);

	// 혼합을 켠다. 
	glEnable(GL_BLEND);
	// 깊이 버퍼를 읽기 전용으로 설정
	glDepthMask(GL_FALSE);
	// 반투명 효과를 위한 혼합 함수들을 설정
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glTranslatef(0, -3, 0);

	// 윌E
	glPushMatrix();
	drawWillE();
	glPopMatrix();

	// 상자
	glPushMatrix();
	drawBox();
	glPopMatrix();

	// 상자 범위
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

	//바닥
	glPushMatrix();
	glRotatef(headrotate, 0, 1, 0);
	glTranslatef(movex*movenum, 0, movez*movenum);
	drawPlane(100, 5);
	glPopMatrix();

	// 깊이 버퍼를 보통 모드( 쓰기 가능 )로 되돌림
	glDepthMask(GL_TRUE);
	// 혼합 끈다 
	glDisable(GL_BLEND);

	glDisable(GL_LIGHTING);

	// 스왑 버퍼
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("12510096 조광민 윌E");

	GLInit();

	glutDisplayFunc(myDisplay);
	glutReshapeFunc(reshape);
	glutIdleFunc(myDisplay);

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special); // 키보드 특수 키
	glutMouseFunc(mouse); // 마우스 클릭 시 발생되는 이벤트
	glutMotionFunc(motion); // 마우스 클릭 후 이동 시 발생되는 이벤트

	glutMainLoop();

	return 0;
}