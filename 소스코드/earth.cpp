#define GLUT_DISABLE_ATEXIT_HACK

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>

float range = 1.0;
float aspRatio = 1.0;
float dX = 0.0;
float rt[8] = {0, 0, 0, 0, 0, 0, 0};
float srt[9] = {0, 0, 0, 0, 0, 0, 0};

void drawAxis(){
	glBegin(GL_LINES);

	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	
	glEnd();
}

void myDisplay() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2, 2, 2, 0, 0, 0, 0, 1, 0);
	
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	/*
	glLineWidth(5);
	drawAxis();
	glLineWidth(1);
	*/

	

	for (int i=0; i<=7; i++){ // 공전
		switch(i){
			case 0: rt[i]+=0.4726; break;  // 수성   / 반지름 2500  / 공전 88일   / 자전 59일        / 위성 x
			case 1: rt[i]+=0.3502; break;  // 금성   / 반지름 6000  / 공전 225일  / 자전 223일       / 위성 x
			case 2: rt[i]+=0.2978; break;  // 지구   / 반지름 6400  / 공전 365일  / 자전 1일         / 위성 1개
			case 3: rt[i]+=0.2408; break;  // 화성   / 반지름 3400  / 공전 687일  / 자전 24시간 37분 / 위성 2개
			case 4: rt[i]+=0.1306; break;  // 목성   / 반지름 71000 / 공전 11.9년 / 자전 9시간 50분  / 위성 16개
			case 5: rt[i]+=0.0965; break;  // 토성   / 반지름 60000 / 공전 29.5년 / 자전 10시간 14분 / 위성 23개/ 고리
			case 6: rt[i]+=0.0681; break;  // 천왕성 / 반지름 27900 / 공전 84년   / 자전 15시간      / 위성 15개 / 고리
			case 7: rt[i]+=0.0544; break;  // 해왕성 / 반지름 24300 / 공전 165년  / 자전 15시간 18분 / 위성 5개 / 고리
		}                                        // 달 / 반지름 1700 / 공전 30일 / 자전 273일
		if (rt[i] >= 360){
			rt[i] = 0;
		}
	}

	for (int i=0; i<=8; i++){ // 자전
		switch(i){
			case 0: srt[i]+= 0.4726; break;  // 태양
			case 1: srt[i]+= 0.2409; break;  // 수성
			case 2: srt[i]+=0.6102; break;  // 금성
			case 3: srt[i]+=1.0; break;  // 지구
			case 4: srt[i]+=1.8809; break;  // 화성
			case 5: srt[i]+=11.862; break;  // 목성
			case 6: srt[i]+=29.458; break;  // 토성
			case 7: srt[i]+=84.022; break;  // 천왕성
			case 8: srt[i]+=164.774; break;  // 해왕성
		}
		if (srt[i] >= 360){
			srt[i] = 0;
		}
	}

	// 태양
	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotatef(srt[0], 0, 1, 0);
	glutWireSphere(27, 20, 20); // 스페어 (반지름, 경도, 위도)
	glPopMatrix();

	// 수성
	glPushMatrix();
	glColor3f(0, 0, 1);
	glRotatef(srt[1], 0, 1, 0);
	glTranslatef(10, 0, 0); // 태양과의 거리
	glRotatef(srt[1], 1, 0, 0);
	glutWireSphere(0.25, 10, 10); // 스페어 (반지름, 경도, 위도)
	glPopMatrix();

	// 금성
	glPushMatrix();
	glColor3f(1, 1, 0);
	glRotatef(srt[2], 0, 1, 0);
	glTranslatef(20, 0, 0); // 태양과의 거리
	glRotatef(srt[2]*2, 1, 0, 0);
	glutWireSphere(0.6, 10, 10); // 스페어 (반지름, 경도, 위도)
	glPopMatrix();

	// 지구
	glPushMatrix();
	glColor3f(0, 1, 0);
	glRotatef(srt[3], 0, 1, 0);
	glTranslatef(30, 0, 0); // 태양과의 거리
	glRotatef(srt[3]*2, 1, 0, 0);
	glutWireSphere(0.64, 10, 10); // 스페어 (반지름, 경도, 위도)
	  // 달
	glRotatef(-srt[3], 1, 0, 0);
	glColor3f(1, 1, 1);
	glRotatef(srt[3], 0, 1, 0);
	glTranslatef(0.5, 0, 0);
	glRotatef(srt[3], 0, 1, 0);
	glRotatef(srt[3], 0, 0, 1);
	glutWireSphere(0.17, 10, 10); // 스페어 (반지름, 경도, 위도)
	glPopMatrix();

	// 화성
	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotatef(srt[4], 0, 1, 0);
	glTranslatef(40, 0, 0); // 태양과의 거리
	glRotatef(srt[4]*2, 1, 0, 0);
	glutWireSphere(0.34, 10, 10); // 스페어 (반지름, 경도, 위도)
	  // 위성1
	glRotatef(-srt[4], 1, 0, 0);
	glColor3f(1, 1, 1);
	glRotatef(srt[4], 0, 1, 0);
	glTranslatef(0.5, 0, 0);
	glRotatef(srt[4], 0, 1, 0);
	glRotatef(srt[4], 0, 0, 1);
	glutWireSphere(0.17, 10, 10); // 스페어 (반지름, 경도, 위도)
	  // 위성2
	glRotatef(-srt[4], 1, 0, 0);
	glColor3f(1, 1, 1);
	glRotatef(srt[4], 0, 1, 0);
	glTranslatef(0.5, 0, 0);
	glRotatef(srt[4], 0, 1, 0);
	glRotatef(srt[4], 0, 0, 1);
	glutWireSphere(0.17, 10, 10); // 스페어 (반지름, 경도, 위도)
	glPopMatrix();
	
	// 목성
	glPushMatrix();
	glColor3f(0.5, 0, 0);
	glRotatef(srt[4], 0, 1, 0);
	glTranslatef(80, 0, 0); // 태양과의 거리
	glRotatef(srt[4]*2, 1, 0, 0);
	glutWireSphere(7.1, 10, 10); // 스페어 (반지름, 경도, 위도)
		 // 위성1
	//for (int i=0; i<16; i++){
		glRotatef(-srt[4], 1, 0, 0);
		glColor3f(1, 1, 1);
		glRotatef(srt[4], 0, 1, 0);
		glTranslatef(0.5, 0, 0);
		glRotatef(srt[4], 0, 1, 0);
		glRotatef(srt[4], 0, 0, 1);
		glutWireSphere(0.17, 10, 10); // 스페어 (반지름, 경도, 위도)
	//}
	glPopMatrix();

	glutSwapBuffers();
}

void SetCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100, 100, -100, 100, -100, 100);
	gluPerspective(0, aspRatio, 0.1, 1000);
}

void reshape(int w, int h){
	aspRatio = float(w)/h;
	SetCamera();
	glViewport(0, 0, w, h);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("12510096 조광민");
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}