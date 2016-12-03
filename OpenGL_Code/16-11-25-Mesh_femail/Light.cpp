#include "Light.h"


//light parameters
GLfloat lit_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat lit_position[] = { 5, 5, 0, 1 };
// material parameters
GLfloat mat_diffuse[] = { 1.0, 1.0, 0.5, 1.0 };

void SetLighting(void) {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lit_diffuse);
}

void SetLightPosition(void) {
	glLightfv(GL_LIGHT0, GL_POSITION, lit_position);
}