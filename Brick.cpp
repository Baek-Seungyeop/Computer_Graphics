#include "HeaderCollect.h"
#include "Constant.h"
#include "Brick.h"
#include "Color.h"

Brick::Brick(int l, int r, int b, int t, Color c, bool v) : left(l), right(r), bottom(b), top(t), color(c), visible(v) {}

Brick::Brick(const Brick& b) : left(b.left), right(b.right), bottom(b.bottom), top(b.top), color(b.color), visible(b.visible) {}

void Brick::destory_brick(Brick* brick) {
	brick->visible = false;
}

Brick::~Brick() {
	
}

void Brick::draw_brick(Color c) {
	glColor3f(c.r, c.g, c.b);
	glBegin(GL_POLYGON);
	glVertex2f(left, bottom);
	glVertex2f(left, top);
	glVertex2f(right, top);
	glVertex2f(right, bottom);
	glEnd();
}

void Brick::push_brick(int dy) {
	this->bottom -= dy;
	this->top -= dy;
}