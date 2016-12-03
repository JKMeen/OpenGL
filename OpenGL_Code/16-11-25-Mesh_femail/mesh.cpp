#include "mesh.h"

CMesh::CMesh() { }

CMesh::~CMesh() {
	delete[] verts;
}

void CMesh::read(char *fname) {
	FILE *f;
	fopen_s(&f, fname, "r");
	if (!f) { printf("file not found\n"); return; }

	fscanf(f, "%d", &nV);
	verts = new vertex[nV];
	for (int i = 0; i < nV; i++) {
		fscanf(f, "%f", &verts[i].x);
		fscanf(f, "%f", &verts[i].y);
		fscanf(f, "%f", &verts[i].z);
	}
	fscanf(f, "%d", &nF);
	tris = new triangle[nF];
	for (int i = 0; i < nF; i++) {
		fscanf(f, "%d", &tris[i].v0);
		fscanf(f, "%d", &tris[i].v1);
		fscanf(f, "%d", &tris[i].v2);
	}
}

void CMesh::show() {
	glDisable(GL_LIGHTING);
	/*
	// Á¡
	glBegin(GL_POINTS);
	for (int i = 0; i < nV; i++) {
		glVertex3f(verts[i].x, verts[i].y, verts[i].z);
	}
	glEnd();
	*/
	
	// »ï°¢Çü
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < nF; i++) {
		//glBegin(GL_LINE_LOOP);
		// current face = tris[i]
		// three vertices : tris[i].v0, v1, v2
		int v0 = tris[i].v0;
		int v1 = tris[i].v1;
		int v2 = tris[i].v2;
		glVertex3f(verts[v0].x, verts[v0].y, verts[v0].z);
		glVertex3f(verts[v1].x, verts[v1].y, verts[v1].z);
		glVertex3f(verts[v2].x, verts[v2].y, verts[v2].z);
	}
	glEnd();
}