#include "Color.h"

#pragma once
class Brick {
public:
	int left;
	int right;
	int bottom;
	int top;
	Color color;
	bool visible;

	Brick(int l = 0, int r = 0, int b = 0, int t = 0, Color c = Color(0.58F, 0.29F, 0.0F), bool v = true);
	Brick(const Brick& b);
	~Brick();
	void draw_brick(Color c);
	void destory_brick(Brick* brick);
	void push_brick(int dy);
};