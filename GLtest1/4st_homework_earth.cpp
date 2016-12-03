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
	glRotatef(Revolution, Rx, Ry, Rz); // 공전
	glTranslatef(distance, 0, 0); // 태양과의 거리
	glRotatef(rotation, rx, ry, rz); // 자전
	glutWireSphere(radius, 20, 20); 
	//glutSolidSphere(radius, 20, 20); // 스페어 (반지름, 경도, 위도)
}

void drawMoon(float distance, int num, float radius){ // 달
	glPushMatrix();
	glRotatef(-srt[num], 1, 0, 0);
	glColor3f(1, 1, 0);
	glRotatef(srt[num], 0, 1, 0);
	glTranslatef(distance, 0, 0);
	glRotatef(srt[num], 0, 1, 0);
	glRotatef(srt[num], 0, 0, 1);
	glutSolidSphere(radius, 10, 10); // 스페어 (반지름, 경도, 위도)
	glPopMatrix();
}

void displayPlanet(){
	// 태양
	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotatef(srt[0], 0, 1, 0); // 자전
	//glutWireSphere(radius, 20, 20); 
	//glutWireSphere(27*2, 20, 20); // 스페어 (반지름, 경도, 위도)
	drawPlanet(1, 0, 0, 0, 0, 0, 0, 0, srt[0], 0, 1, 0, 27 * 2);
	glPopMatrix();

	// 수성(Mercury)
	glPushMatrix();
	glColor3f(0, 0, 1);
	drawPlanet(0, 0, 1, rt[0], 0, 1, 0, 57.9, srt[1], 1, 0, 0, 0.25 * 10);
	glPopMatrix();

	// 금성(Venus) 
	glPushMatrix();
	drawPlanet(1, 1, 0, rt[1], 0, 1, 0, 108.2, srt[2], 1, 0, 0, 0.6 * 10);
	glPopMatrix();

	// 지구(Earth)
	glPushMatrix();
	drawPlanet(0, 1, 0, rt[2], 0, 1, 0, 149.6, srt[3], 1, 0, 0, 0.64 * 10);
	drawMoon(10, 1, 1.17);
	glPopMatrix();

	// 화성(Mars)
	glPushMatrix();
	drawPlanet(1, 0, 0, rt[3], 0, 1, 0, 228.0, srt[4], 1, 0, 0, 0.34 * 10);
	drawMoon(10, 1, 1.3);
	drawMoon(10, 2, 1.7);
	glPopMatrix();

	// 목성(Jupiter)
	glPushMatrix();
	drawPlanet(0.5, 0, 0, rt[4], 0, 1, 0, 778.3, srt[5], 1, 0, 0, 7.1 * 10);
	drawMoon(100, 2, 3);
	drawMoon(100, 3, 9);
	drawMoon(100, 4, 5);
	glPopMatrix();

	// 토성(Saturn)
	glPushMatrix();
	drawPlanet(1, 0.5, 0, rt[5], 0, 1, 0, 1427.0, srt[6], 1, 0, 0, 6.0 * 10);
	drawMoon(90, 3, 4);
	drawMoon(90, 1, 7);
	drawMoon(90, 4, 6);
	glPushMatrix();
	glutWireSphere(120, 2, 20);
	glPopMatrix();
	glPopMatrix();

	// 천왕성(Uranus)
	glPushMatrix();
	drawPlanet(0, 0, 0.7, rt[6], 0, 1, 0, 2900.0, srt[7], 1, 0, 0, 2.79 * 10);
	glPopMatrix();

	// 해왕성(Neptune)
	glPushMatrix();
	drawPlanet(0, 0, 0.9, rt[7], 0, 1, 0, 4497.0, srt[8], 1, 0, 0, 2.43 * 10);
	glPopMatrix();
}

void setRotation(){
	// 수성(Mercury)   / 반지름 2500  / 공전 88일(4736)   / 자전 59일        / 위성 x
	// 금성(Venus)     / 반지름 6000  / 공전 225일(3502)  / 자전 223일       / 위성 x
	// 지구(Earth)     / 반지름 6400  / 공전 365일(2978)  / 자전 1일         / 위성 1개
	// 화성(Mars)      / 반지름 3400  / 공전 687일(2408)  / 자전 24시간 37분 / 위성 2개
	// 목성(Jupiter)   / 반지름 71000 / 공전 11.9년(1306) / 자전 9시간 50분  / 위성 16개
	// 토성(Saturn)    / 반지름 60000 / 공전 29.5년(965)  / 자전 10시간 14분 / 위성 23개/ 고리
	// 천왕성(Uranus)  / 반지름 27900 / 공전 84년(681)    / 자전 15시간      / 위성 15개 / 고리
	// 해왕성(Neptune) / 반지름 24300 / 공전 165년(544)   / 자전 15시간 18분 / 위성 5개 / 고리
	//* 달 / 반지름 1700 / 공전 30일 / 자전 273일
	for (int i = 0; i <= 7; i++){ // 공전
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

	for (int i = 0; i <= 8; i++){ // 자전
		switch (i){
		case 0: srt[i] += 0.59; break;  // 태양
		case 1: srt[i] += 0.59; break;  // 수성
		case 2: srt[i] += 0.223; break;  // 금성
		case 3: srt[i] += 1.0; break;  // 지구
		case 4: srt[i] += 1.1; break;  // 화성
		case 5: srt[i] += 2.5; break;  // 목성
		case 6: srt[i] += 2.3; break;  // 토성
		case 7: srt[i] += 4.16; break;  // 천왕성
		case 8: srt[i] += 4.162; break;  // 해왕성
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

void myDisplay() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//카메라 설정
	SetCamera();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3*cos(10.0), 1, 3*sin(10.0), 0, 0, 0, 0, 1, 0);

	// 빛 설정
	LightPosition();
	glDisable(GL_LIGHTING);

	// 마우스 클릭 - 회전
	glRotated(angle, ax, ay, 0.0);

	// 공전 / 자전 설정
	setRotation();

	drawPlane(1000, 100);

	// 빛 실행
	glEnable(GL_LIGHTING);
	// 혼합을 켠다. 
	glEnable(GL_BLEND);
	// 깊이 버퍼를 읽기 전용으로 설정
	glDepthMask(GL_FALSE);
	// 반투명 효과를 위한 혼합 함수들을 설정
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	
	// 각 행성 디스플레이
	displayPlanet();

	// 깊이 버퍼를 보통 모드( 쓰기 가능 )로 되돌림
	glDepthMask(GL_TRUE);
	// 혼합 끈다 
	glDisable(GL_BLEND);

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