#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <stdio.h>
#include <math.h>
#include <conio.h> // getch(); ÇÔ¼ö¸¦ »ç¿ë

#define GLUT_DISABLE_ATEXIT_HACK
#define   PI   3.1415926535897932384626

// set window size & image size coordinates & image view mode 
GLsizei   viewmode;
GLsizei   wwidth = 320, wheight = 320; // initial window width & height
GLdouble  magfac = 0.60;
GLdouble  ix1 = 0.0, ix2 = 2.0,
iy1 = 0.0, iy2 = 2.0,
iz1 = -1.0, iz2 = 1.0;
GLfloat   xrot, yrot, zrot;
GLfloat   red = 1.0, green = 1.0, blue = 1.0, alpha = 1.0;

int ch, delay=0;
float eyey = 3.5, eyex = 3.5, eyez = 3.5, tr=0.01;

void drawAxes() {
	glBegin(GL_LINES);
	
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0); // x
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0); // y
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1); // z
	glEnd();
}

void drawPlane(void) {
	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_LINES);
	for (int i = 0; i<40; i++) {
		glVertex3f(-20, 0, i - 20);
		glVertex3f(20, 0, i - 20);
	}
	for (int i = 0; i<40; i++) {
		glVertex3f(i - 20, 0, -20);
		glVertex3f(i - 20, 0, 20);
	}
	glEnd();

	glColor3f(0, 0, 0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex3f(-20, 0, 0);
	glVertex3f(20, 0, 0);
	glVertex3f(0, 0, -20);
	glVertex3f(0, 0, 20);
	glEnd();

}

void drawBox(float w, float h) {
	glPushMatrix();
	glScalef(w, h, w);
	glutWireCube(1);
	glPopMatrix();
}

void  special(int key, int x, int y)
{
	switch (key) {
		//  spin key for image rotation
	case GLUT_KEY_UP:
		eyey += 0.3;
		break;
	case GLUT_KEY_DOWN:
		eyey -= 0.3;
		break;
	case GLUT_KEY_LEFT:
		eyex -= 0.3;
		break;
	case GLUT_KEY_RIGHT:
		eyex += 0.3;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void myDisplay() {
	char info[128];

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 0.1, 100); //-2.0, 2.0, -2.0, 2.0, -1.0, 1.0);

	static float angle = 0.0;
	angle += 0.01;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, 0, 1.5, 0, 0, 1, 0);

	for (int i = 0; i < 30; i++){
		if (delay == 0){
			tr += 0.3;
			if (tr > 100){
				delay = 1;
			}
		}
		else (delay == 1){
			tr -= 0.3;
			if (tr < 0){
				delay = 0;
			}
		}
		drawPlane();
		glLineWidth(i);
		glTranslatef(0, tr, 0);
		glRotatef(tr, 0, 0, 1);
		drawBox(0.1, 0.1);
	}

	static float tAngle;
	tAngle += 0.1;
	float hAngle = sin(tAngle);
	hAngle *= hAngle;

	glColor4f(red, green, blue, alpha);

	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("12510096 Á¶±¤¹Î");

	glEnable(GL_DEPTH_TEST);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutSpecialFunc( special );
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutMainLoop();

	return 0;
}