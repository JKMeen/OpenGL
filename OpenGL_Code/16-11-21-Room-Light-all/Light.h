#ifndef LIGHT_H
#define LIGHT_H

#include "GL_header.h"

void SetSpot(int flag, float cutoff_angle);
void SetLightPosition(float pos[], float pos1[], float pos2[]);
void SetMaterial(float dr, float dg, float db, float sr, float sg, float sb, float ar, float ag, float ab);

// ���̷��� ����Ʈ
void SetLight(float r, float g, float b, float sr, float sg, float sb);

// ����Ʈ ����Ʈ
void SetLight1(float r, float g, float b, float sr, float sg, float sb);

// ����Ʈ ����Ʈ
void SetLight2(float r, float g, float b, float sr, float sg, float sb);

#endif