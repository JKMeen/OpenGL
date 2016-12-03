#include "Light.h"


//light parameters
GLfloat lit_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lit_specular[] = { 1, 1, 1, 1.0 };
GLfloat lit_position[] = { 1, 1, -5, 0 };
// material parameters
GLfloat mat_diffuse[] = { 1, 0.8, 0.7, 1.0 };
GLfloat mat_specular[] = { 1, 1, 1, 1.0 };

void SetLighting(void) {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lit_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lit_diffuse);
}

void SetLightPosition(void) {
	glLightfv(GL_LIGHT0, GL_POSITION, lit_position);
}