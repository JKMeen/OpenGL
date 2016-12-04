#include "Header.h"
#include "STBImage.h"

//#define TEXSIZE 8

class Texture{
	//GLubyte myTex[TEXSIZE][TEXSIZE][3];
	unsigned char *myTex;
	int texWidth, texHeight, bitPerPixel;

public:
	void CreateTexture();
	void SetupTexture();
};