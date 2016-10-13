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

	

	for (int i=0; i<=7; i++){ // ����
		switch(i){
			case 0: rt[i]+=0.4726; break;  // ����   / ������ 2500  / ���� 88��   / ���� 59��        / ���� x
			case 1: rt[i]+=0.3502; break;  // �ݼ�   / ������ 6000  / ���� 225��  / ���� 223��       / ���� x
			case 2: rt[i]+=0.2978; break;  // ����   / ������ 6400  / ���� 365��  / ���� 1��         / ���� 1��
			case 3: rt[i]+=0.2408; break;  // ȭ��   / ������ 3400  / ���� 687��  / ���� 24�ð� 37�� / ���� 2��
			case 4: rt[i]+=0.1306; break;  // ��   / ������ 71000 / ���� 11.9�� / ���� 9�ð� 50��  / ���� 16��
			case 5: rt[i]+=0.0965; break;  // �伺   / ������ 60000 / ���� 29.5�� / ���� 10�ð� 14�� / ���� 23��/ ��
			case 6: rt[i]+=0.0681; break;  // õ�ռ� / ������ 27900 / ���� 84��   / ���� 15�ð�      / ���� 15�� / ��
			case 7: rt[i]+=0.0544; break;  // �ؿռ� / ������ 24300 / ���� 165��  / ���� 15�ð� 18�� / ���� 5�� / ��
		}                                        // �� / ������ 1700 / ���� 30�� / ���� 273��
		if (rt[i] >= 360){
			rt[i] = 0;
		}
	}

	for (int i=0; i<=8; i++){ // ����
		switch(i){
			case 0: srt[i]+= 0.4726; break;  // �¾�
			case 1: srt[i]+= 0.2409; break;  // ����
			case 2: srt[i]+=0.6102; break;  // �ݼ�
			case 3: srt[i]+=1.0; break;  // ����
			case 4: srt[i]+=1.8809; break;  // ȭ��
			case 5: srt[i]+=11.862; break;  // ��
			case 6: srt[i]+=29.458; break;  // �伺
			case 7: srt[i]+=84.022; break;  // õ�ռ�
			case 8: srt[i]+=164.774; break;  // �ؿռ�
		}
		if (srt[i] >= 360){
			srt[i] = 0;
		}
	}

	// �¾�
	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotatef(srt[0], 0, 1, 0);
	glutWireSphere(27, 20, 20); // ����� (������, �浵, ����)
	glPopMatrix();

	// ����
	glPushMatrix();
	glColor3f(0, 0, 1);
	glRotatef(srt[1], 0, 1, 0);
	glTranslatef(10, 0, 0); // �¾���� �Ÿ�
	glRotatef(srt[1], 1, 0, 0);
	glutWireSphere(0.25, 10, 10); // ����� (������, �浵, ����)
	glPopMatrix();

	// �ݼ�
	glPushMatrix();
	glColor3f(1, 1, 0);
	glRotatef(srt[2], 0, 1, 0);
	glTranslatef(20, 0, 0); // �¾���� �Ÿ�
	glRotatef(srt[2]*2, 1, 0, 0);
	glutWireSphere(0.6, 10, 10); // ����� (������, �浵, ����)
	glPopMatrix();

	// ����
	glPushMatrix();
	glColor3f(0, 1, 0);
	glRotatef(srt[3], 0, 1, 0);
	glTranslatef(30, 0, 0); // �¾���� �Ÿ�
	glRotatef(srt[3]*2, 1, 0, 0);
	glutWireSphere(0.64, 10, 10); // ����� (������, �浵, ����)
	  // ��
	glRotatef(-srt[3], 1, 0, 0);
	glColor3f(1, 1, 1);
	glRotatef(srt[3], 0, 1, 0);
	glTranslatef(0.5, 0, 0);
	glRotatef(srt[3], 0, 1, 0);
	glRotatef(srt[3], 0, 0, 1);
	glutWireSphere(0.17, 10, 10); // ����� (������, �浵, ����)
	glPopMatrix();

	// ȭ��
	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotatef(srt[4], 0, 1, 0);
	glTranslatef(40, 0, 0); // �¾���� �Ÿ�
	glRotatef(srt[4]*2, 1, 0, 0);
	glutWireSphere(0.34, 10, 10); // ����� (������, �浵, ����)
	  // ����1
	glRotatef(-srt[4], 1, 0, 0);
	glColor3f(1, 1, 1);
	glRotatef(srt[4], 0, 1, 0);
	glTranslatef(0.5, 0, 0);
	glRotatef(srt[4], 0, 1, 0);
	glRotatef(srt[4], 0, 0, 1);
	glutWireSphere(0.17, 10, 10); // ����� (������, �浵, ����)
	  // ����2
	glRotatef(-srt[4], 1, 0, 0);
	glColor3f(1, 1, 1);
	glRotatef(srt[4], 0, 1, 0);
	glTranslatef(0.5, 0, 0);
	glRotatef(srt[4], 0, 1, 0);
	glRotatef(srt[4], 0, 0, 1);
	glutWireSphere(0.17, 10, 10); // ����� (������, �浵, ����)
	glPopMatrix();
	
	// ��
	glPushMatrix();
	glColor3f(0.5, 0, 0);
	glRotatef(srt[4], 0, 1, 0);
	glTranslatef(80, 0, 0); // �¾���� �Ÿ�
	glRotatef(srt[4]*2, 1, 0, 0);
	glutWireSphere(7.1, 10, 10); // ����� (������, �浵, ����)
		 // ����1
	//for (int i=0; i<16; i++){
		glRotatef(-srt[4], 1, 0, 0);
		glColor3f(1, 1, 1);
		glRotatef(srt[4], 0, 1, 0);
		glTranslatef(0.5, 0, 0);
		glRotatef(srt[4], 0, 1, 0);
		glRotatef(srt[4], 0, 0, 1);
		glutWireSphere(0.17, 10, 10); // ����� (������, �浵, ����)
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
	glutCreateWindow("12510096 ������");
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}