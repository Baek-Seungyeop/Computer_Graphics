#include "Ball.h"
#include "HeaderCollect.h"
#include "Constant.h"
#include "Function.h"

Ball::Ball(Point P, float r, Color C, Vector V, float vs, bool m)
	: center(P), radius(r), color(C), velocity(V), velocity_sum(vs), move_state(m) {}
Ball::Ball(const Ball& b) : center(b.center), radius(b.radius), color(b.color), velocity(b.velocity), velocity_sum(b.velocity_sum), move_state(b.move_state) {}

void Ball::draw_ball(float r, Point Center, Color C) {
	glColor3f(C.r, C.g, C.b);

	draw_circle(GL_POLYGON, Center.x, Center.y, r);
}

bool Ball::check_collision_window() {
	if (center.x - radius <= win_left) {
		velocity.x = -velocity.x;	center.x = win_left + radius;
		return false;
	}
	if (center.x + radius >= win_right) {
		velocity.x = -velocity.x;	center.x = win_right - radius;
		return false;
	}
	if (center.y - radius <= win_bottom) {
		return true;
	}
	if (center.y + radius >= win_top) {
		velocity.y = -velocity.y;	center.y = win_top - radius;
		return false;
	}
	return false;
}

bool Ball::check_corner_collision(int left, int right, int bottom, int top, float x, float y) {
	// left-bottom collision
	if (x > left - ball_radius && x < left && y > bottom && y < bottom + ball_radius / 3) {
		velocity.x = -fabs(velocity.x);	velocity.y = -fabs(velocity.y);
		return true;
	}
	// right-bottom collision
	if (x > right && x < right + ball_radius && y > bottom && y < bottom + ball_radius / 3) {
		velocity.x = fabs(velocity.x);	velocity.y = -fabs(velocity.y);
		return true;
	}
	// left-top collision
	if (x > left - ball_radius && x < left && y > top - ball_radius / 3 && y < top) {
		velocity.x = -fabs(velocity.x);	velocity.y = fabs(velocity.y);
		return true;
	}
	// right-top collision
	if (x > right && x < right + ball_radius && y > top - ball_radius / 3 && y < top) {
		velocity.x = fabs(velocity.x);	velocity.y = fabs(velocity.y);
		return true;
	}
	return false;
}

bool Ball::check_left_collision(int left, int right, int bottom, int top, float x, float y) {
	if (velocity.x > 0 && center.x + radius >= left && center.x + radius < right
		&& center.y >= bottom && center.y <= top) {
		velocity.x = -velocity.x;	return true;
	}
	return false;
}

bool Ball::check_right_collision(int left, int right, int bottom, int top, float x, float y) {
	// ¿ÞÂÊÀ¸·Î ÀÌµ¿ && objectÀÇ ÁÂº¯ < °øÀÇ ÁÂÃø¸é < objectÀÇ ¿ìº¯
	// objectÀÇ ¹Øº¯ <= °øÀÇ yÁÂÇ¥ <= objectÀÇ À­º¯
	if (velocity.x < 0 && center.x - radius <= right && center.x - radius > left
		&& center.y >= bottom && center.y <= top) {
		velocity.x = -velocity.x;	return true;
	}
	return false;
}

bool Ball::check_bottom_collision(int left, int right, int bottom, int top, float x, float y) {
	if (velocity.y > 0 && center.y + radius >= bottom && center.y + radius < top
		&& center.x >= left && center.x <= right) {
		velocity.y = -velocity.y;	return true;
	}
	return false;
}

bool Ball::check_top_collision(int left, int right, int bottom, int top, float x, float y) {
	if (velocity.y < 0 && center.y - radius <= top && center.y - radius > bottom
		&& center.x >= left && center.x <= right) {
		velocity.y = -velocity.y;	return true;
	}
	return false;
}

bool Ball::check_object_collision(int left, int right, int bottom, int top, float x, float y) {
	if (check_corner_collision(left, right, bottom, top, x, y)) {
		printf("corner collison\n");	return true;
	}
	if (check_left_collision(left, right, bottom, top, x, y)) {
		printf("left collision\n");	return true;
	}
	if (check_right_collision(left, right, bottom, top, x, y)) {
		printf("right collision\n");	return true;
	}
	if (check_bottom_collision(left, right, bottom, top, x, y)) {
		printf("bottom collision\n");	return true;
	}
	if (check_top_collision(left, right, bottom, top, x, y)) {
		printf("top collision\n");		return true;
	}
	return false;
}

bool Ball::check_collision_stick(const Stick& stick) {
	// check_object_collision
	if (check_top_collision(stick.left, stick.right, stick.bottom, stick.top, center.x, center.y)) {
		return true;
	}
	return false;
}

bool Ball::check_collision_brick(const Brick* brick) {
	/*printf("brick_left : %d, brick_right %d, brick_bottom : %d, brick_top %d\ncenter.x : %f, center.y : %f\n"
		, brick->left, brick->right, brick->bottom, brick->right, center.x, center.y);*/

	if (brick->visible) {
		if (check_object_collision(brick->left, brick->right, brick->bottom, brick->top, center.x, center.y)) {
			velocity.x *= velocity_ratio;	velocity.y *= velocity_ratio; velocity_sum *= velocity_ratio;
			return false;
		}
		return true;
	}
	return false;
}

void Ball::move(float deltaTime) {
	if (move_state) {
		glColor3f(0.0, 0.0, 1.0);
		center.x += velocity.x * deltaTime;
		center.y += velocity.y * deltaTime;
	}
}

bool Ball::get_move() {
	return move_state;
}

void Ball::go() {
	move_state = true;
}

void Ball::stop() {
	move_state = false;
}

void Ball::reset(float vx, float vy, float cx, float cy) {
	velocity.x = vx;	velocity.y = vy;
	center.x = cx;		center.y = cy;
	ball_velocity_angle = 90.0F;
}

void Ball::adjust_direction(int d) {
	float theta = 2.0F;

	if (d == GLUT_KEY_LEFT) 
		ball_velocity_angle += theta;
	else 
		ball_velocity_angle -= theta;

	velocity.x = velocity_sum * cos(ball_velocity_angle * PI / 180.0);
	velocity.y = velocity_sum * sin(ball_velocity_angle * PI / 180.0);
}