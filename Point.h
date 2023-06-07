#pragma once
class Point {
public:
	float x;
	float y;

	Point(float xx = 0.0F, float yy = 0.0F);
	Point(const Point& p);
};