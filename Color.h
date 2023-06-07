#pragma once
class Color {
public:
	float r;
	float g;
	float b;

	Color(float red = 0.0F, float green = 0.0F, float blue = 0.0F);
	Color(const Color& c);
};