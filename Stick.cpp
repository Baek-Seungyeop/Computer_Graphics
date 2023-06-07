#include "Constant.h"
#include "HeaderCollect.h"
#include "Stick.h"

Stick::Stick(int l, int r, int b, int t, Color c) 
	: left(l), right(r), bottom(b), top(t), color(c) {}
Stick::Stick(const Stick& s) : left(s.left), right(s.right), bottom(s.bottom), top(s.top), color(s.color) {}

void Stick::draw_stick(Color c) {
	glColor3f(c.r, c.g, c.b);
	glBegin(GL_POLYGON);
	glVertex2f(left, bottom);
	glVertex2f(left, top);
	glVertex2f(right, top);
	glVertex2f(right, bottom);
	glEnd();
}