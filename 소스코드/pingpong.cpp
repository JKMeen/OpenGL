#define GLUT_DISABLE_ATEXIT_HACK

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

float movex = 0, shoot = -1;
float ballx = 0.003, bally = 0.001, changex = -1, changey = -1;
int xspeed, yspeed;
float blockx[9], blocky[9];
int k = 0, delay = 0, block[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void special(int key, int x, int y){
	switch (key){
	case GLUT_KEY_LEFT: movex -= 0.1;
		if (movex <= -0.7) movex = -0.7;
		break;
	case GLUT_KEY_RIGHT: movex += 0.1;
		if (movex >= 0.7) movex = 0.7;
		break;
	}
}

void keyboard(unsigned char key, int x, int y){
	switch (key){
	case 'Z': shoot *= -1;
		break;
	}
}

void drawObject(int s){
	if (s == 0){ // Room
		glBegin(GL_LINE_LOOP);
		glColor3f(1, 0, 0);
		glVertex3f(-0.9, -0.9, 0);
		glVertex3f(0.9, -0.9, 0);
		glVertex3f(0.9, 0.9, 0);
		glVertex3f(-0.9, 0.9, 0);
		glEnd();
	}
	else if (s == 1){ // Player
		glBegin(GL_LINE_LOOP);
		glColor3f(0, 0, 1);
		glVertex3f(-0.2, -0.75, 0);
		glVertex3f(0.2, -0.75, 0);
		glVertex3f(0.2, -0.7, 0);
		glVertex3f(-0.2, -0.7, 0);
		glEnd();
	}
	else if (s == 2){ // Ball
		glBegin(GL_LINE_LOOP);
		int Points = 20;
		float radius = 0.05;
		glColor3f(0, 1, 0);
		float angle = 0.0;
		float step = (3.14159*2.0) / Points;
		while (angle <3.14159*2.0) {
			glVertex3f(radius*cos(angle), radius*sin(angle), 0);
			angle += step;
		}
		glEnd();
	}
}

void drawBlock(float x, float y){
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 0);
	glVertex3f(-0.15 + x, y, 0);
	glVertex3f(0.15 + x, y, 0);
	glVertex3f(0.15 + x, y + 0.05, 0);
	glVertex3f(-0.15 + x, y + 0.05, 0);
	glEnd();
}

void myDisplay(){
	
	if (delay == 0){
		srand((unsigned int)time(NULL));
		xspeed = rand() % 4 + 2;
		yspeed = rand() % 3 + 2;
		delay = 1;
	}

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	if (ballx >= 0.85 || ballx <= -0.85) // 좌,우 충돌
		changex *= -1;
	if (bally >= 0.85) // 천장 충돌
		changey = -1;
	if (bally <= -0.85) // 바닥 충돌 (점수--)
		changey = 1;
	if (ballx <= movex + 0.2 && ballx >= movex - 0.2 && bally <= -0.65) // 플레이어 충돌
		changey = 1;

	ballx += 0.0001*changex;
	bally += 0.0001*changey;

	// Room
	drawObject(0);

	// Player
	glPushMatrix();
	glTranslatef(movex, 0, 0);
	drawObject(1);
	glPopMatrix();

	// Ball
	glPushMatrix();
	glTranslatef(ballx, bally, 0);
	drawObject(2);
	glPopMatrix();
	
	glFlush();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("12510096");
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);

	glClearColor(0, 0, 0, 1);

	glutMainLoop();

	return 0;
}