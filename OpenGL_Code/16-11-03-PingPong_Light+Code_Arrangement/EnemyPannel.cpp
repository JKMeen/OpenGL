#include "EnemyPannel.h"
#include "OpenGLHeaders.h"

float epannelx = 0, epannely = 0;

void EnemyPannelMove(float dx, float dy){
	epannelx = dx;
	epannely = dy;
}

void EnemyPannelDraw(){
	glPushMatrix();
	glTranslatef(epannelx, epannely, -1.0);
	glScalef(0.5, 0.5, 0.01);
	glutSolidCube(1.0);
	glPopMatrix();
}

float GetEnemyPannelX(){
	return epannelx;
}

float GetEnemyPannelY(){
	return epannely;
}