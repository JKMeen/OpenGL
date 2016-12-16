#define GLUT_DISABLE_ATEXIT_HACK
#include <Windows.h>
#include <stdio.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <math.h>
#include "STBImage.h"
// void glGenTextures(int n, GLuint *textures)
// void glBindTexture(GLenum target /*GL_TEXTURE_2D*/, GLuint texture);
GLuint tex[10]; // 핸들러, 보통 int로 관리
unsigned char *myTex; // 이미지가 들어감
int texWidth, texHeight, bitPerPixel;

void PrepareTextures(void){
	// 0. glGenTextures(2, tex)로 두 개의 이미지를 쓴다고 정의
	// 1. tex[0]를 GL_TEXTURE_2D에 Bind 시킴
	// 2. image 1을 읽어 들이고, mytex에 그림을 그림
	// 3. GPU로 텍스쳐를 보내고, tex[0]라는 이름으로 관리됨
	// 4. delete[] mytex로 그 때 그 때 텍스쳐를 지움
	// 5. image 2를 읽어 들이고, mytex에 그림을 그림
	// 6. GPU로 텍스쳐를 보내고, tex[1]이라는 이름으로 관리됨
	// 7. delete[] mytex로 그 때 그 때 텍스쳐를 지움 (CPU에 있는 그림은 쓰지 않음)
	// 8. 원하는 그림을 그리고 싶을 때는 Bind를 새로 함
	char *img = { "cosmos.jpg" };
	glGenTextures(10, tex);
	if (myTex) delete[] myTex;
	for (int i = 0; i < 10; i++){
		glBindTexture(GL_TEXTURE_2D, tex[i]);
		switch (i){
		case 0: img = { "dirty.jpg" }; break;
		case 1: img = { "cosmos.jpg" }; break;
		case 2: img = { "cosmos1.jpg" }; break;
		case 3: img = { "cosmos2.jpg" }; break;
		case 4: img = { "cosmos3.jpg" }; break;
		case 5: img = { "cosmos9.jpg" }; break;
		case 6: img = { "cosmos8.jpg" }; break;
		case 7: img = { "cosmos7.jpg" }; break;
		case 8: img = { "cosmos6.jpg" }; break;
		case 9: img = { "cosmos5.jpg" }; break;
		}
		myTex = stbi_load(img, &texWidth, &texHeight, &bitPerPixel, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, myTex);
		delete[] myTex;
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	
	myTex = NULL;
	glEnable(GL_TEXTURE_2D);
}
/*
void CreateTexture(void) {
	myTex = stbi_load("dirty.jpg", &texWidth, &texHeight, &bitPerPixel, 0);
}

void SetupTexture(void) {
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0,
		GL_RGB, GL_UNSIGNED_BYTE, myTex);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glEnable(GL_TEXTURE_2D);
}
*/

void drawQuad(void) {
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 1, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-1, -1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(1, -1, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, 0);
	glEnd();
}

void myDisplay() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	static float angle = 0.0;
	angle += 0.01;
	gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 1, 1);

	for (int i = 0; i < 10; i++){
		glBindTexture(GL_TEXTURE_2D, tex[i]);
		glPushMatrix();
		glTranslatef((i*2)-10, 0, 0);
		drawQuad();
		//glutSolidTeapot(1.0);
		glPopMatrix();
	}

	glutSwapBuffers();
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	PrepareTextures();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("My Texture");

	init();

	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);

	glutMainLoop();

	return 0;
}