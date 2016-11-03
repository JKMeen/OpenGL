#include "MyPannel.h"
#include "OpenGLHeaders.h"

float pannelx = 0, pannely = 0;

void PannelMove(float dx, float dy){
	pannelx = dx*0.0025;
	if (pannelx >= 0.75){ pannelx = 0.75; }
	else if (pannelx <= -0.75){ pannelx = -0.75; }
	pannely = -dy*0.0025;
	if (pannely >= 0.75){ pannely = 0.75; }
	else if (pannely <= -0.75){ pannely = -0.75; }
}

void PannelDraw(){
	glPushMatrix();
	glTranslatef(pannelx, pannely, 1.0);
	glScalef(0.5, 0.5, 0.01);
	glutSolidCube(1.0);
	glPopMatrix();
}

float GetPannelX(){
	return pannelx;
}

float GetPannelY(){
	return pannely;
}