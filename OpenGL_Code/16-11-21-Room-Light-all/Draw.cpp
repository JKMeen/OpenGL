#include "Draw.h"

void drawWall(){
	glPushMatrix();
	for (int i = -3; i <= 3; i++){
		for (int j = -5; j <= 5; j++){
			glPushMatrix();
			//glColor3f(0.1, 0.1, 0.1);
			glTranslatef(0, i, j);
			glScalef(0.1, 10, 10);
			glutSolidCube(0.1);
			glPopMatrix();
			glPushMatrix();
			//glColor3f(0, 0, 0);
			glTranslatef(0, i, j);
			glScalef(0.1, 10, 10);
			glutWireCube(0.1);
			glPopMatrix();
		}
	}
	glPopMatrix();
}

void drawPlane(){
	glPushMatrix();
	for (int i = -5; i <= 5; i++){
		for (int j = -5; j <= 5; j++){
			glPushMatrix();
			//glColor3f(0.1, 0.1, 0.1);
			glTranslatef(i, 0, j);
			glScalef(10, 0.1, 10);
			glutSolidCube(0.1);
			glPopMatrix();
			glPushMatrix();
			//glColor3f(0, 0, 0);
			glTranslatef(i, 0, j);
			glScalef(10, 0.1, 10);
			glutWireCube(0.1);
			glPopMatrix();
		}
	}
	glPopMatrix();
}

void drawChair(){
	glPushMatrix();
	glTranslatef(0, 0.35, 0);
	//glColor3f(0.5, 0.3, 0.3);
	glPushMatrix();
	glScalef(5.0, 0.5, 5.0);
	glutSolidCube(0.1);
	glPopMatrix();
	
	// 등받이
	glPushMatrix();
	glTranslatef(0, 0.25, -0.25);
	glScalef(5.0, 5.0, 0.5);
	glutSolidCube(0.1);
	glPopMatrix();

	// 다리 설정
	glTranslatef(0, -0.175, 0);

	// 다리1
	glPushMatrix();
	glTranslatef(0.2, 0, 0.2);
	glScalef(0.5, 3.5, 0.5);
	glutSolidCube(0.1);
	glPopMatrix();

	// 다리2
	glPushMatrix();
	glTranslatef(0.2, 0, -0.2);
	glScalef(0.5, 3.5, 0.5);
	glutSolidCube(0.1);
	glPopMatrix();

	// 다리3
	glPushMatrix();
	glTranslatef(-0.2, 0, -0.2);
	glScalef(0.5, 3.5, 0.5);
	glutSolidCube(0.1);
	glPopMatrix();

	// 다리4
	glPushMatrix();
	glTranslatef(-0.2, 0, 0.2);
	glScalef(0.5, 3.5, 0.5);
	glutSolidCube(0.1);
	glPopMatrix();

	glPopMatrix();
}

void drawTable(){
	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	//glColor3f(0.5, 0.3, 0.3);
	glPushMatrix();
	glScalef(10.0, 0.5, 7.5);
	glutSolidCube(0.1);
	glPopMatrix();

	// 다리 설정
	glTranslatef(0, -0.25, 0);

	// 다리1
	glPushMatrix();
	glTranslatef(0.45, 0, 0.325);
	glScalef(0.5, 5.0, 0.5);
	glutSolidCube(0.1);
	glPopMatrix();

	// 다리2
	glPushMatrix();
	glTranslatef(0.45, 0, -0.325);
	glScalef(0.5, 5.0, 0.5);
	glutSolidCube(0.1);
	glPopMatrix();

	// 다리3
	glPushMatrix();
	glTranslatef(-0.45, 0, -0.325);
	glScalef(0.5, 5.0, 0.5);
	glutSolidCube(0.1);
	glPopMatrix();

	// 다리4
	glPushMatrix();
	glTranslatef(-0.45, 0, 0.325);
	glScalef(0.5, 5.0, 0.5);
	glutSolidCube(0.1);
	glPopMatrix();

	glPopMatrix();
}

