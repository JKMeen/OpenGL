#include "texture.h"

#define TEXNUM 3

void Texture::PrepareTextures(void){
	// 0. glGenTextures(2, tex)로 두 개의 이미지를 쓴다고 정의
	// 1. tex[0]를 GL_TEXTURE_2D에 Bind 시킴
	// 2. image 1을 읽어 들이고, mytex에 그림을 그림
	// 3. GPU로 텍스쳐를 보내고, tex[0]라는 이름으로 관리됨
	// 4. delete[] mytex로 그 때 그 때 텍스쳐를 지움
	// 5. image 2를 읽어 들이고, mytex에 그림을 그림
	// 6. GPU로 텍스쳐를 보내고, tex[1]이라는 이름으로 관리됨
	// 7. delete[] mytex로 그 때 그 때 텍스쳐를 지움 (CPU에 있는 그림은 쓰지 않음)
	// 8. 원하는 그림을 그리고 싶을 때는 Bind를 새로 함
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
//	// GPU로 이미지를 보내는 작업 
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0,
//		GL_RGB, GL_UNSIGNED_BYTE, myTex);
//	/*glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXSIZE, TEXSIZE, 0, 
//		GL_RGB, GL_UNSIGNED_BYTE, myTex);*/
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glEnable(GL_TEXTURE_2D); 
//	// 텍스쳐를 켜놓고 작업하면 계산량이 많아 꺼놓고 GPU로 보낸 뒤 마지막에 Enable함
//}
