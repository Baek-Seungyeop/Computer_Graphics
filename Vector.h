#pragma once
class Vector {
public:
	float x;
	float y;

	Vector(float xx = 0.0F, float yy = 0.0F);
	Vector(const Vector& v);
};