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

void keyboard(unsigned char c, int, int) {
	switch (c) {
	case 27: exit(0); break;
	case 'q': count++; if (count > 4) count = 0; break;
	}
}

void display() {
	// world
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(100.0*cos(angle), 50, 100.0*sin(angle), 0, 50, 0, 0, 1, 0);
	gluLookAt(30.0, 50, 30.0, 0, 50, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static float angle = 0;
	angle += 0.2;

	static GLfloat lit_position[] = { 1, 1, 1, 0 };
	lit_position[0] = 60 * sin(angle/10);
	lit_position[1] = 10;
	lit_position[2] = 60 *cos(angle/10);

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

	glRotatef(angle, 0, 1, 0);
	// draw mesh
	glColor3f(242/255, 108/255, 79/255);
	mesh1.show();


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
		}

	//glDisable(GL_LIGHTING);

	glutSwapBuffers();
}


void init(void) {
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	// texture enable
	tex1.CreateTexture();
	tex1.SetupTexture();

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

	init();


	glutMainLoop();
	return 1;
}