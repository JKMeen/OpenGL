#include "Ball.h"
#include "OpenGLHeaders.h"
#include "MyPannel.h"
#include "EnemyPannel.h"

#define RAD 0.1

struct Vector3f{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

Vector3f ballPosition;
Vector3f ballVelocity;

void BallSet(float x, float y, float z, float vx, float vy, float vz){
	ballPosition.x = x;
	ballPosition.y = y;
	ballPosition.z = z;
	ballVelocity.x = vx;
	ballVelocity.y = vy;
	ballVelocity.z = vz;
}

void BallMove(){
	// v = dx/dt;
	// dx = v*dt;
	// dx = 현재위치 - 이전위치
	ballPosition.x = ballPosition.x + ballVelocity.x * 0.01;
	ballPosition.y = ballPosition.y + ballVelocity.y * 0.01;
	ballPosition.z = ballPosition.z + ballVelocity.z * 0.01;

	EnemyPannelMove(ballPosition.x, ballPosition.y);

	if (ballPosition.x + RAD > 1.0 || ballPosition.x-RAD < -1.0){
		ballVelocity.x *= -1;
	}

	if (ballPosition.y + RAD > 1.0 || ballPosition.y - RAD < -1.0){
		ballVelocity.y *= -1;
	}

	if (ballPosition.z + RAD < -0.9 && GetEnemyPannelX() - 0.5 <= ballPosition.x && GetPannelX() + 0.5 >= ballPosition.x && GetEnemyPannelY() - 0.5 <= ballPosition.y && GetEnemyPannelY() + 0.5 >= ballPosition.y){
		ballVelocity.z *= -1;
	}

	if (ballPosition.z + RAD > 0.9 && GetPannelX() - 0.5 < ballPosition.x && GetPannelX() + 0.5 > ballPosition.x && GetPannelY() - 0.5 < ballPosition.y && GetPannelY() + 0.5 > ballPosition.y){
		ballVelocity.z *= -1;
	}

	if (ballPosition.z > 1.3){ exit(true); }
}

void BallDraw(){
	glPushMatrix();
	glTranslatef(ballPosition.x, ballPosition.y, ballPosition.z);
	glutSolidSphere(RAD, 30, 30);
	glPopMatrix();
}