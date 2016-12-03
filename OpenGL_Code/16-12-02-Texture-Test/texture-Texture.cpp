#include "texture-Texture.h"

// texture image create
void Texture::CreateTexture(){
	for (int i = 0; i < TEXSIZE; i++){
		for (int j = 0; j < TEXSIZE; j++){
			myTex[i][j][0] = rand() % 255; // 255 * ((i + j) % 2);
			myTex[i][j][1] = rand() % 255; // 255 * ((i + j) % 2);
			myTex[i][j][2] = rand() % 255; // 255 * ((i + j) % 2);
		}
	}
}

void Texture::SetupTexture(){
	// GPU�� �̹����� ������ �۾� 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXSIZE, TEXSIZE, 0, 
		GL_RGB, GL_UNSIGNED_BYTE, &myTex[0][0][0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glEnable(GL_TEXTURE_2D); 
	// �ؽ��ĸ� �ѳ��� �۾��ϸ� ��귮�� ���� ������ GPU�� ���� �� �������� Enable��
}