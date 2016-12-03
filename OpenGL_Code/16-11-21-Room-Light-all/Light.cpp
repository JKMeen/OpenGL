#include "Light.h"

GLfloat Light_lightPos[] = { 1, 1, 1, 1 };
GLfloat Light_lightPos1[] = { 1, 1, 1, 1 };
GLfloat Light_lightPos2[] = { 1, 1, 1, 1 };

void SetMaterial(float dr, float dg, float db, float sr, float sg, float sb, float ar, float ag, float ab) {
	GLfloat diffuse[] = { dr, dg, db, 1.0 };
	GLfloat specular[] = { sr, sg, sb, 1.0 };
	GLfloat ambient[] = { ar, ag, ab, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
}

// 다이렉트 라이트
void SetLight(float r, float g, float b, float sr, float sg, float sb) {
	GLfloat diffuse[] = { r, g, b, 1.0 };
	GLfloat specular[] = { sr, sg, sb, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
}

// 스포트 라이트
void SetLight1(float r, float g, float b, float sr, float sg, float sb) {
	GLfloat diffuse[] = { r, g, b, 1.0 };
	GLfloat specular[] = { sr, sg, sb, 1.0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
}

// 포인트 라이트
void SetLight2(float r, float g, float b, float sr, float sg, float sb) {
	GLfloat diffuse[] = { r, g, b, 1.0 };
	GLfloat specular[] = { sr, sg, sb, 1.0 };
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
}

void SetSpot(int flag, float cutoff_angle){
	if (flag == 0){
		GLfloat direction[] = { -Light_lightPos[0], -Light_lightPos[1], -Light_lightPos[2] };
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
	}
	else if (flag == 1){
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 0.0);
		GLfloat direction[] = { -Light_lightPos1[0], -Light_lightPos1[1], -Light_lightPos1[2] };
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, cutoff_angle);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
	}
	else if (flag == 2){
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 0.0);
		GLfloat direction[] = { Light_lightPos2[0], -Light_lightPos2[1], -Light_lightPos2[2] };
		//glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 50.0);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction);
	}
	else if (flag == 3){
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 0.0);
	}
}

void SetLightPosition(float pos[], float pos1[], float pos2[]) {
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	for (int i = 0; i < 4; i++) Light_lightPos[i] = pos[i];
	glLightfv(GL_LIGHT1, GL_POSITION, pos1);
	for (int i = 0; i < 4; i++) Light_lightPos1[i] = pos1[i];
	glLightfv(GL_LIGHT2, GL_POSITION, pos2);
	for (int i = 0; i < 4; i++) Light_lightPos2[i] = pos2[i];
}