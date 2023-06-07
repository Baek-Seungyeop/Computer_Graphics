#include "Point.h"

Point::Point(float xx, float yy) : x(xx), y(yy) {}
Point::Point(const Point& p) : x(p.x), y(p.y) {}