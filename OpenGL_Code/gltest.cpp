#define GLUT_DISABLE_ATEXIT_HACK

#include <Windows.h>
#include <gl/glut.h>
#include <stdio.h>
#include <math.h>
#include <conio.h> // getch(); 함수를 사용
//
//#pragma comment(lib, "freeglut.lib")
//#pragma comment(lib, "glut.lib")

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

#define   PI   3.1415926535897932384626

// set window size & image size coordinates & image view mode 
GLsizei   viewmode;
GLsizei   wwidth = 320, wheight = 320; // initial window width & height
GLdouble  magfac = 0.60;
GLdouble  ix1 = 0.0, ix2 = 2.0,iy1 = 0.0, iy2 = 2.0,iz1 = -1.0, iz2 = 1.0;
GLfloat   xrot, yrot, zrot;
GLfloat   red = 1.0, green = 1.0, blue = 1.0, alpha = 1.0;

int ch;
float eyey = 3.5, eyex = 3.5;

void drawAxes() {
	glBegin(GL_TRIANGLES);

	glColor3f(1, 0, 0);
	glVertex3f(1, 0, 0); // x
	glColor3f(0, 1, 0);
	glVertex3f(0, 1, 0); // y
	glColor3f(0, 0, 1);
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
		xrot -= 2.0f;
		if (xrot < -360.0f) xrot += 360.0f;
		break;
	case GLUT_KEY_DOWN:
		xrot += 2.0f;
		if (xrot > +360.0f) xrot -= 360.0f;
		break;
	case GLUT_KEY_LEFT:
		yrot -= 2.0f;
		if (yrot < -360.0f) yrot += 360.0f;
		break;
	case GLUT_KEY_RIGHT:
		yrot += 2.0f;
		if (yrot > +360.0f) yrot -= 360.0f;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}


void myDisplay() {
	char info[128];

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//카메라 설정 행렬
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluPerspective(60, 1, 0.1, 100); //-2.0, 2.0, -2.0, 2.0, -1.0, 1.0);

	static float angle = 0.0;
	angle += 0.01;
	glMatrixMode(GL_MODELVIEW); // 오브젝트 설정 행렬
	glLoadIdentity();
	gluLookAt(3.0*cos(angle), eyey, 3.0*sin(angle), 0, 1.5, 0, 0, 1, 0);

	glLineWidth(1);
	drawPlane();
	glColor3f(1.0, 0.0, 0.0);
	drawAxes();

	glLineWidth(3);
	glTranslatef(0, 0.5, 0);
	drawBox(0.25, 1);

	glTranslatef(0, 0.5, 0);
	glRotatef(45, 0, 0, 1);
	glTranslatef(0, 0.5, 0);
	//drawAxes();
	drawBox(0.25, 1);

	static float tAngle;
	tAngle += 0.1;
	float hAngle = sin(tAngle);
	hAngle *= hAngle;

	// hand 1
	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	glRotatef(yrot, 1.0f, 0.0f, 0.0f);
	glTranslatef(0, 0.25, 0);
	//drawAxes();
	drawBox(0.1, 0.5);
	glPopMatrix();

	// hand 2
	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	glRotatef(yrot, 1.0f, 0.0f, 0.0f);
	glTranslatef(0, 0.25, 0);
	//drawAxes();
	drawBox(0.1, 0.5);
	glPopMatrix();

	glColor4f(red, green, blue, alpha);

	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Transform");

	glEnable(GL_DEPTH_TEST);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	//glutKeyboardFunc( keyboard );
	glutSpecialFunc(special);
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutMainLoop();

	return 0;
}