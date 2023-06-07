#include "Point.h"
#include "Color.h"
#include "Vector.h"
#include "Stick.h"
#include "Brick.h"

#pragma once
class Ball {
public:
	Point center;
	float radius;
	Color color;
	Vector velocity;
	float velocity_sum;
	bool move_state;

	Ball(Point P = Point(0.0, 0.0), float r = 0.0, Color C = Color(0.0, 0.0, 0.0), Vector V = Vector(0.0, 0.0), float vs = 0.0, bool m = true);
	Ball(const Ball& b);
	void move(float deltaTime);
	void draw_ball(float r, Point Center, Color C);
	bool get_move();
	void go();
	void stop();
	void adjust_direction(int d);
	void reset(float vx, float vy, float cx, float cy);

	bool check_collision_window();
	bool check_object_collision(int left, int right, int bottom, int top, float x, float y);
	bool check_collision_stick(const Stick& stick);
	bool check_collision_brick(const Brick* brick);
private:
	bool check_corner_collision(int left, int right, int bottom, int top, float x, float y);
	bool check_left_collision(int left, int right, int bottom, int top, float x, float y);
	bool check_right_collision(int left, int right, int bottom, int top, float x, float y);
	bool check_bottom_collision(int left, int right, int bottom, int top, float x, float y);
	bool check_top_collision(int left, int right, int bottom, int top, float x, float y);
};