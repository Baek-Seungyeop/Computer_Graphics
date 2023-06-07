#include "HeaderCollect.h"

#pragma once
static void draw_text(string s, float x, float y) {
	glColor3f(0.0, 0.0, 1.0);
	glRasterPos2f(x, y);

	for (int i = 0; i < s.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[i]);
}

#pragma once
static void draw_circle(int mode, float x, float y, float r) {
	float	delta = 2 * PI / 36.0;

	glBegin(mode);
	for (int i = 0; i < 36; i++)
		glVertex2f(x + r * cos(delta * i), y + r * sin(delta * i));
	glEnd();
}