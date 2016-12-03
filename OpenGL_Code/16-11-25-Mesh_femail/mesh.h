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
	triangle *tris;

	//methods
public:
	CMesh();
	void read(char *fName);
	void show();
	~CMesh();
};