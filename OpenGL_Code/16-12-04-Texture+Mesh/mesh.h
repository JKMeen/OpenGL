#include "Header.h"

#define fscanf fscanf_s

struct vertex {
	float x, y, z;
};

struct triangle {
	int v0, v1, v2;
};

class CMesh{
	// properties
	int nV;
	int nF;
	vertex *verts;
	vertex *norms;
	triangle *tris;

	//methods
	// vertex라 지었지만, Vector임
	vertex computeNormal(vertex a, vertex b, vertex c);
	vertex computeNorms();
	vertex computeNormals();

public:
	CMesh();
	void read(char *fName);
	void show();
	~CMesh();
};