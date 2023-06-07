#include "Color.h"

#pragma once
class Stick {
public:
	int left;
	int right;
	int bottom;
	int top;
	Color color;

	Stick(int l = 0, int r = 0, int b = 0, int t = 0, Color c = Color(1.0F, 0.0F, 1.0F));
	Stick(const Stick& s);
	void draw_stick(Color c);
};