#include "texture.h"

#define TEXNUM 3

void Texture::PrepareTextures(void){
	// 0. glGenTextures(2, tex)�� �� ���� �̹����� ���ٰ� ����
	// 1. tex[0]�� GL_TEXTURE_2D�� Bind ��Ŵ
	// 2. image 1�� �о� ���̰�, mytex�� �׸��� �׸�
	// 3. GPU�� �ؽ��ĸ� ������, tex[0]��� �̸����� ������
	// 4. delete[] mytex�� �� �� �� �� �ؽ��ĸ� ����
	// 5. image 2�� �о� ���̰�, mytex�� �׸��� �׸�
	// 6. GPU�� �ؽ��ĸ� ������, tex[1]�̶�� �̸����� ������
	// 7. delete[] mytex�� �� �� �� �� �ؽ��ĸ� ���� (CPU�� �ִ� �׸��� ���� ����)
	// 8. ���ϴ� �׸��� �׸��� ���� ���� Bind�� ���� ��
	char *img = { "cosmos.jpg" };
	glGenTextures(TEXNUM, tex);
	if (myTex) delete[] myTex;
	for (int i = 0; i < TEXNUM; i++){
		glBindTexture(GL_TEXTURE_2D, tex[i]);
		switch (i){
		case 0: img = { "cosmos11.jpg" }; break;
		case 1: img = { "cosmos11.jpg" }; break;
		case 2: img = { "cosmos11.jpg" }; break;
		case 3: img = { "cosmos.jpg" }; break;
		case 4: img = { "cosmos.jpg" }; break;
		case 5: img = { "cosmos.jpg" }; break;
		case 6: img = { "cosmos.jpg" }; break;
		case 7: img = { "cosmos.jpg" }; break;
		case 8: img = { "cosmos.jpg" }; break;
		case 9: img = { "cosmos.jpg" }; break;
		}
		myTex = stbi_load(img, &texWidth, &texHeight, &bitPerPixel, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, myTex);
		delete[] myTex;
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	myTex = NULL;
	glEnable(GL_TEXTURE_2D);
}

//// texture image create
//void Texture::CreateTexture(){
//	myTex = stbi_load("cosmos.jpg", &texWidth, &texHeight, &bitPerPixel, 0);
//	/*
//	for (int i = 0; i < TEXSIZE; i++){
//		for (int j = 0; j < TEXSIZE; j++){
//			myTex[i][j][0] = rand() % 255; // 255 * ((i + j) % 2);
//			myTex[i][j][1] = rand() % 255; // 255 * ((i + j) % 2);
//			myTex[i][j][2] = rand() % 255; // 255 * ((i + j) % 2);
//		}
//	}*/
//}
//
//void Texture::SetupTexture(){
//	// GPU�� �̹����� ������ �۾� 
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0,
//		GL_RGB, GL_UNSIGNED_BYTE, myTex);
//	/*glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXSIZE, TEXSIZE, 0, 
//		GL_RGB, GL_UNSIGNED_BYTE, myTex);*/
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glEnable(GL_TEXTURE_2D); 
//	// �ؽ��ĸ� �ѳ��� �۾��ϸ� ��귮�� ���� ������ GPU�� ���� �� �������� Enable��
//}
