#include "Header.h"
#include "STBImage.h"

//#define TEXSIZE 8

class Texture{
	//GLubyte myTex[TEXSIZE][TEXSIZE][3];
	GLuint tex[10]; // �ڵ鷯, ���� int�� ����
	unsigned char *myTex;
	int texWidth, texHeight, bitPerPixel;

public:
	void PrepareTextures();
	/*void CreateTexture();
	void SetupTexture();*/
};