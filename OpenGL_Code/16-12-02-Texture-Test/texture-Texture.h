#include "textrue-header.h"

#define TEXSIZE 8

class Texture{
	GLubyte myTex[TEXSIZE][TEXSIZE][3];
public:
	void CreateTexture();
	void SetupTexture();
};