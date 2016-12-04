#include "header.h"
#include "texture.h"

Texture t;

void myDisplay(){
	/*
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	static float t = 0.0;
	glTranslatef(t, 0, 0);
	t += 0.01;*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(2, 2, 2, 0, 0, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glColor3f(1, 1, 1);
	static float angle = 0.0;

	// 1. 공처럼 매핑
	glPushMatrix();
	glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTranslatef(-2, 0, 0);
	
	glRotatef(angle, 1, 1, 1);
	glutSolidTeapot(1.0);
	glPopMatrix();

	// 2. 눈으로 보는 시각 매핑
	glPushMatrix();
	glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTranslatef(0, 0, -2);
	glRotatef(angle, 1, 1, 1);
	glutSolidTeapot(1.0);
	glPopMatrix();

	angle += 0.1;

	glutSwapBuffers();
}

void init(){
	glClearColor(0, 0, 0, 1);
	t.CreateTexture();
	t.SetupTexture();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	// 1. 공처럼 맵핑
	//glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	//glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	// 2. 눈으로 프로젝트 처럼 쏘게하는 방법
	//glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	//glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
}

void main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Texture_Mapping");

	init();

	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);

	glutMainLoop();
}