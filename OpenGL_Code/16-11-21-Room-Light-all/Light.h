#ifndef LIGHT_H
#define LIGHT_H

#include "GL_header.h"

void SetSpot(int flag, float cutoff_angle);
void SetLightPosition(float pos[], float pos1[], float pos2[]);
void SetMaterial(float dr, float dg, float db, float sr, float sg, float sb, float ar, float ag, float ab);

// 다이렉션 라이트
void SetLight(float r, float g, float b, float sr, float sg, float sb);

// 스포트 라이트
void SetLight1(float r, float g, float b, float sr, float sg, float sb);

// 포인트 라이트
void SetLight2(float r, float g, float b, float sr, float sg, float sb);

#endif