#include "Light.h"


//light parameters
GLfloat lit_diffuse[] = { 1.0, 0.8, 0.8, 1.0 };
GLfloat lit_specular[] = { 1, 0.8, 0.8, 1.0 };
GLfloat lit_position[] = { 1, 1, 1, 0 };
// material parameters
GLfloat mat_diffuse[] = { 1, 0.8, 0.7, 1.0 };
GLfloat mat_specular[] = { 1, 1, 1, 1.0 };
GLfloat mat_ambient[] = { 1, 1, 1, 1 };
GLfloat mat_shin[] = { 1, 1, 1, 1 };

void SetLighting(void) {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lit_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lit_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shin);
}

void SetLightPosition(GLfloat pos[]) {
	lit_position[0] = pos[0];
	lit_position[1] = pos[1];
	lit_position[2] = pos[2];
	glLightfv(GL_LIGHT0, GL_POSITION, lit_position);
}