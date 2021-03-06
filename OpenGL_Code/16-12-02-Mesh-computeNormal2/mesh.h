#include "Header.h"

#define fscanf fscanf_s

struct vertex {
	float x, y, z;
};

struct triangle {
	int v0, v1, v2;
};

class CMesh {
	// properties
	int nV;
	int nF;
	vertex *verts;
	triangle *tris;
	vertex *norms;
	// methods
	vertex computeNormal(vertex a, vertex b, vertex c);
	void computeNormals();

public:
	CMesh();
	~CMesh();
	void read(char *fname);
	void show();
};