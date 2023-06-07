#include "Vector.h"

Vector::Vector(float xx, float yy) : x(xx), y(yy) {}
Vector::Vector(const Vector& v) : x(v.x), y(v.y) {}