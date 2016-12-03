#include "textrue-header.h"
#include "texture-Texture.h"

Texture t;

void myDisplay(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 0.1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	static float t = 0.0;
	glTranslatef(t, 0, 0);
	t += 0.01;

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 2); glVertex3f(-1.0, 1.0, 0.0);
		glTexCoord2f(0, 0); glVertex3f(-1.0, -1.0, 0.0);
		glTexCoord2f(2, 0); glVertex3f(1.0, -1.0, 0.0);
		glTexCoord2f(2, 2); glVertex3f(1.0, 1.0, 0.0);
	glEnd();

	glutSwapBuffers();
}

void init(){
	glClearColor(0, 0, 0, 1);
	t.CreateTexture();
	t.SetupTexture();
}

void main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Texture");

	init();

	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutMainLoop();
}