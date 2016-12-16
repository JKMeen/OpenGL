#include "Header.h"
#include "Camera.h"
#include "Light.h"
#include "mesh.h"
#include "Draw.h"
#include "texture.h"

// mesh
CMesh mesh1, mesh2;
Texture tex1;

int count = 0;

// 팔 앵글
float robotangle = 0.0;
float robothangle = 0.0;

// 빛 위치
float lightx = 0.0;
float lighty = 0.0;

// 카메라 확대 축소
float look = 0.0;

#define TEXNUM 3

// 멀티텍스쳐
GLuint tex[10]; // 핸들러, 보통 int로 관리
unsigned char *myTex;
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
	glGenTextures(TEXNUM, tex);
	if (myTex) delete[] myTex;
	for (int i = 0; i < TEXNUM; i++){
		glBindTexture(GL_TEXTURE_2D, tex[i]);
		switch (i){
		case 0: img = { "cosmos.jpg" }; break;
		case 1: img = { "cosmos2.jpg" }; break;
		case 2: img = { "cosmos11.jpg" }; break;
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

void keyboard(unsigned char c, int, int) {
	switch (c) {
	case 27: exit(0); break;
	case 'z': count++; if (count > 4) count = 0; break;
	// 카메라 확대 축소
	case 'q': look -= 0.2; if (look <= 0) look = 0; break;
	case 'e': look += 0.2; if (look >= 100) look = 100; break;
	// 로봇 팔 상하 회전
	case 'w': robothangle -= 3; break;
	case 's': robothangle += 3; break;
	// 로봇 팔 좌우 회전
	case 'd': robotangle -= 3; if (robotangle <= -30) robotangle = -30; break;
	case 'a': robotangle += 3; if (robotangle >= 30) robotangle = 30; break;
	}
}

void special(int key, int x, int y){
	switch (key){
	case GLUT_KEY_LEFT: lightx += 0.05;
		break;
	case GLUT_KEY_RIGHT: lightx -= 0.05;
		break;
	case GLUT_KEY_UP: lighty += 3;
		break;
	case GLUT_KEY_DOWN: lighty -= 3;
		break;
	}
}

void display() {
	// world
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(100.0*cos(angle), 50, 100.0*sin(angle), 0, 50, 0, 0, 1, 0);
	gluLookAt(60*sin(look)/*90.0-look*/, 150, 60*cos(look)/*90.0-look*/, 0, 50, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static float angle = 0;
	angle += 0.4;

	static GLfloat lit_position[] = { 1, 1, 1, 0 };
	lit_position[0] = 40 * sin(lightx);
	lit_position[1] = lighty;
	lit_position[2] = 40 *cos(lightx);

	SetLightPosition(lit_position);

	glPushMatrix();
	glColor3f(1, 0, 0);
	glLineWidth(5);
	glTranslatef(lit_position[0], lit_position[1], lit_position[2]);
	glutWireSphere(5, 20, 20);
	glLineWidth(1);
	glPopMatrix();

	glLineWidth(1);
	//draw axes
	drawAxes(1.0);

	glEnable(GL_LIGHTING);

	//glRotatef(angle, 0, 1, 0);
	glPushMatrix();

	glPopMatrix();
	glTranslatef(0, -20, 0);
	// 로봇 팔
	glPushMatrix();
	glPushMatrix();
	glColor3f(0, 1, 0);
	glScalef(30, 10, 20);
	glutSolidCube(1);
	glPopMatrix();
	glTranslatef(0, 5, 0);
		glPushMatrix();
		glColor3f(1, 1, 0);
		glutSolidSphere(3, 10, 10);
		glRotatef(robotangle, 0, 0, 1);
		glTranslatef(0, 4, 0);
		glPushMatrix();
		glColor3f(1, 0, 0);
		glScalef(3, 20, 3);
		glutSolidCube(1);
		glPopMatrix();
		glTranslatef(0, 10, 0);
			glPushMatrix();
			glColor3f(1, 1, 0);
			glutSolidSphere(3, 10, 10);
			glRotatef(robotangle, 0, 0, 1);
			glTranslatef(0, 9, 0);
			glPushMatrix();
			glColor3f(1, 0, 0);
			glScalef(3, 20, 3);
			glutSolidCube(1);
			glPopMatrix();
			glTranslatef(0, 10, 0);
				glPushMatrix();
				glColor3f(1, 1, 0);
				glutSolidSphere(3, 10, 10);
				glRotatef(-robotangle, 0, 0, 1);
				glTranslatef(0, 9, 0);
				glPushMatrix();
				glColor3f(1, 0, 0);
				glScalef(3, 20, 3);
				glutSolidCube(1);
				glPopMatrix();
				glTranslatef(0, 8, 0);
					glPushMatrix();
					glRotatef(-robotangle, 0, 0, 1);
					glTranslatef(0, 4, 0);
					glPushMatrix();
					glColor3f(1, 0, 0);
					glScalef(30, 5, 30);
					glutSolidCube(1);
					glPopMatrix();
					glTranslatef(0, 2.5, 5);
					// 메시
					// draw mesh
					//glColor3f(242 / 255, 108 / 255, 79 / 255);
					glRotatef(angle, 0, 1, 0);
					// 마네킹 (환경맵핑)
					glEnable(GL_TEXTURE_GEN_S);
					glEnable(GL_TEXTURE_GEN_T);
					glColor3f(1, 1, 1);
					glPushMatrix();

					glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
					glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
					glBindTexture(GL_TEXTURE_2D, tex[0]);
					mesh1.show();
					glPopMatrix();

					glDisable(GL_TEXTURE_GEN_S);
					glDisable(GL_TEXTURE_GEN_T);

					// 옷 (오브젝트 리니어)
					glEnable(GL_TEXTURE_GEN_S);
					glEnable(GL_TEXTURE_GEN_T);
					glColor3f(1, 1, 1);
					glPushMatrix();

					glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glBindTexture(GL_TEXTURE_2D, tex[1]);
					mesh2.show();
					glPopMatrix();
					//glBindTexture(GL_TEXTURE_2D, tex[0]);
					glDisable(GL_TEXTURE_GEN_S);
					glDisable(GL_TEXTURE_GEN_T);
					glBindTexture(NULL, NULL);
					/*
					switch (count){
					case 0:
						glPushMatrix();
						glColor3f(0, 0, 1);
						mesh2.show();
						glPopMatrix();
						break;

					case 1:
						// 1. 오브젝트에 고정된 맵핑
						glEnable(GL_TEXTURE_GEN_S);
						glEnable(GL_TEXTURE_GEN_T);
						glColor3f(1, 1, 1);
						glPushMatrix();

						glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
						glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
						mesh2.show();

						glPopMatrix();

						glDisable(GL_TEXTURE_GEN_S);
						glDisable(GL_TEXTURE_GEN_T);
						break;

					case 2:
						// 2. 환경 맵핑 (공처럼 맵핑)
						glEnable(GL_TEXTURE_GEN_S);
						glEnable(GL_TEXTURE_GEN_T);
						glColor3f(1, 1, 1);
						glPushMatrix();

						glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
						glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

						mesh2.show();

						glPopMatrix();

						glDisable(GL_TEXTURE_GEN_S);
						glDisable(GL_TEXTURE_GEN_T);
						break;

					case 3:
						// 3. 좌표계에 맵핑 (눈으로 보는 시점 맵핑)
						glEnable(GL_TEXTURE_GEN_S);
						glEnable(GL_TEXTURE_GEN_T);
						glColor3f(1, 1, 1);
						glPushMatrix();

						glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
						glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

						mesh2.show();

						glPopMatrix();

						glDisable(GL_TEXTURE_GEN_S);
						glDisable(GL_TEXTURE_GEN_T);
						break;

					case 4:
						// 반투명 효과
						glEnable(GL_BLEND); // 깊이 버퍼를 읽기 전용으로 설정 
						glDepthMask(GL_FALSE); // 반투명 효과를 위한 혼합 함수들을 설정 
						glBlendFunc(GL_SRC_ALPHA, GL_ONE);

						glColor3f(0, 0, 1);
						mesh2.show();
						glColor3f(1, 0, 0);
						mesh2.show();
						glColor3f(1, 0, 1);
						mesh2.show();
						glDepthMask(GL_TRUE);
						glDisable(GL_BLEND);

						break;
					}*/
					//////////////////////////////////////////////////////////
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	
	//glDisable(GL_LIGHTING);

	glutSwapBuffers();
}


void init(void) {
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	// texture enable
	PrepareTextures();
	/*tex1.CreateTexture();
	tex1.SetupTexture();*/

	// light enable
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	SetLighting();

	mesh1.read("femail.sms.txt");
	mesh2.read("sleevel.sms.txt");

}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("12510096 jkmeen Mesh");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	init();


	glutMainLoop();
	return 1;
}