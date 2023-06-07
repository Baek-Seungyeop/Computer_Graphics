#include "Color.h"

Color::Color(float red, float green, float blue) : r(red), g(green), b(blue) {}
Color::Color(const Color& c) : r(c.r), g(c.g), b(c.b) {}