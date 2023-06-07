#include "HeaderCollect.h"
#include "Constant.h"
#include "Color.h"
#include "Point.h"
#include "Stick.h"
#include "Vector.h"
#include "Ball.h"
#include "Brick.h"
#include "UI.h"
#include "Function.h"

int		cur_brick_num = 20;
int		add_brick_num = 4;
int		Value = 20;
int		break_cnt;
int		main_page_tab_cnt;
int		escape_tab_cnt;
int     escape_cnt_of_game_start_page;

float	ax, bx, ay, by;
float	ball_velocity_sum = sqrtf(powf(velocity_x, 2) + powf(velocity_y, 2));

bool	game_over = false;
bool	game_clear = false;
bool	game_stop = false;
bool	main_page = true;
bool	game_start_page = false;
bool	game_description_page = false;
bool	escape_box = false;

static Point		ball_center(WIN_WIDTH / 2, stick_top + ball_radius);

static Color		ball_color(0.0F, GREEN, BLUE);
static Color		stick_color(RED, 0.0F, BLUE);
static Color		brick_color(0.58F, 0.29F, 0.0F);

static Vector		ball_velocity(velocity_x, velocity_y);

static Ball			ball(ball_center, ball_radius, ball_color, ball_velocity, ball_velocity_sum);

static Stick		stick(stick_left, stick_right, stick_bottom, stick_top, stick_color);

static Brick* brick[max_brick_num];

UI	ui;
TextBox* wave_box = new TextBox(50, WIN_HEIGHT, 150, 50);
Life* life = new Life(3);
Deadline* dead_line = new Deadline(150);
MainPage mp(0, 0, WIN_WIDTH, WIN_HEIGHT + UI_HEIGHT);
DescriptionPage dp(0, 0, WIN_WIDTH, WIN_HEIGHT + UI_HEIGHT);
EscapePage ep(WIN_WIDTH / 2 - 150, (WIN_HEIGHT + UI_HEIGHT) / 2 - 50, 300, 100);

void MyReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(win_left, win_right, win_bottom, win_top + UI_HEIGHT);
}

void set_brick() {
	int x = 30, y = 700;
	int delta_x = 100, delta_y = 100;

	for (int i = 0; i < cur_brick_num; i++) {
		x += delta_x; // 130 ~ 470 (윈도우 너비는 0 ~ 600)
		brick[i] = new Brick(x, x + brick_width, y, y + brick_height, brick_color, true);

		if ((i + 1) % add_brick_num == 0) { x = 30;	y -= delta_y; }
	}
}

void add_brick() {
	int x = 30, y = 700;
	int delta_x = 100, delta_y = 100;

	for (int i = 0; i < cur_brick_num; i++)
		brick[i]->push_brick(delta_y);

	for (int i = cur_brick_num; i < cur_brick_num + add_brick_num; i++) {
		x += delta_x; // 130 ~ 470 (윈도우 너비는 0 ~ 600)
		brick[i] = new Brick(x, x + brick_width, y, y + brick_height, brick_color, true);
	}
	cur_brick_num += add_brick_num;
}

void stop_game() {
	ball.stop();
	game_stop = true;
}

void clear_game() {
	ball.stop();
	game_stop = true;
}

void resume_game() {
	ball.go();
	game_stop = false;
}

static steady_clock::time_point currentTime = steady_clock::now(); // 프로그램 시작 시 현재 시간
void RenderScene(void) {
	auto renderTime = steady_clock::now() - currentTime;
	float deltaTime = renderTime.count() / 1000.0 / 1000.0 / 1000.0; // ns -> m(icro)s ->m(illi)s -> second
	glClearColor(0.7, 0.7, 0.7, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	if (main_page) {
		mp.display_main();
		mp.display_game_description();
		mp.display_game_start();
		mp.display_game_title();
		if (main_page_tab_cnt % 2)
			mp.display_toggle_circle(375);
		else
			mp.display_toggle_circle(475);
	}	
	else if(game_start_page) {
		if (game_over) 
			stop_game();	
		if (game_clear) 
			clear_game();

		// ui 그리기
		ui.display();
		life->display();
		dead_line->display();
		wave_box->display();

		string text = "next_wave : " + to_string(Value);
		draw_text(text, 72, WIN_HEIGHT + 22);

		// 공 그리기
		ball.draw_ball(ball.radius, ball.center, ball_color);

		// 충돌 처리 부분
		bool not_catched_ball = ball.check_collision_window();
		if (not_catched_ball) {
			ball.reset(0, fabs(ball.velocity_sum), (stick.left + stick.right) / 2, stick.top + ball.radius);
			ball.stop();
			life->life--;
			if (life->life < 0) { game_over = true; life->life = 0; }
		}

		if (ball.check_collision_stick(stick)) {
			ball.reset(0, fabs(ball.velocity_sum), ball.center.x, ball.center.y);
			ball.stop();
		}

		if (!ball.get_move()) {
			ax = ball.center.x;				ay = ball.center.y;
			bx = ax + ball.velocity.x * 4;	by = ay + ball.velocity.y * 4;
		}

		Line* line = new Line(ax, ay, bx, by);

		if (!ball.move_state)
			if (!game_stop)
				line->display();

		for (int i = 0; i < cur_brick_num; i++)
			brick[i]->visible = ball.check_collision_brick(brick[i]);

		// 바 그리기
		stick.draw_stick(stick.color);

		// 벽돌 그리기
		break_cnt = 0;
		for (int i = 0; i < cur_brick_num; i++) {
			if (brick[i]->visible) {
				if (brick[i]->bottom < dead_line->height)
					game_over = true;
				brick[i]->draw_brick(brick[i]->color);
			}	else {
				brick[i]->destory_brick(brick[i]);
				break_cnt++;
			}
		}

		if (break_cnt == cur_brick_num)
			game_clear = true;

		// 공 움직이기
		ball.move(deltaTime);

		if (game_over) {
			TextBox game_over_box(WIN_WIDTH / 2 - 100, (WIN_HEIGHT + UI_HEIGHT) / 2 - 50, 200, 100);
			game_over_box.display();
			draw_text("GAME OVER", WIN_WIDTH / 2 - 37, (WIN_HEIGHT + UI_HEIGHT) / 2);
		}

		if (game_clear) {
			TextBox game_clear_box(WIN_WIDTH / 2 - 100, (WIN_HEIGHT + UI_HEIGHT) / 2 - 50, 200, 100);
			game_clear_box.display();
			draw_text("GAME CLEAR", WIN_WIDTH / 2 - 37, (WIN_HEIGHT + UI_HEIGHT) / 2);
		}
	}	else if (game_description_page) {
		dp.display_text_box();
	}

	if (escape_box) {
		if (main_page)
			ep.display_escape_box("exit main page");
		if (game_start_page) {
			ep.display_escape_box("exit game page");	stop_game();
		}
		if (game_description_page)
			ep.display_escape_box("exit description page");

		if (escape_tab_cnt % 2)
			ep.display_toggle_circle(225);
		else
			ep.display_toggle_circle(375);
	}

	glutSwapBuffers();
	glFlush();

	currentTime += renderTime; // 랜더링 로직이 걸린 시간을 구한다
}

void MySpecial(int Key, int x, int y) {
	//auto renderTime = (steady_clock::now() - currentTime);
	float correct_velocity = powf(velocity_ratio, break_cnt);

	switch (Key) {
	case GLUT_KEY_LEFT:
		if (ball.get_move()) {
			stick.left -= delta_stick_x * correct_velocity;
			stick.right -= delta_stick_x * correct_velocity;
			if (stick.left < win_left) { stick.left = win_left; stick.right = stick_size; }
		}	else {	ball.adjust_direction(GLUT_KEY_LEFT); }
		break;
	case GLUT_KEY_RIGHT:
		if (ball.get_move()) {
			stick.left += delta_stick_x * correct_velocity;
			stick.right += delta_stick_x * correct_velocity;
			if (stick.right > win_right) { stick.left = win_right - stick_size; stick.right = win_right; }
		}	else {	ball.adjust_direction(GLUT_KEY_RIGHT); }
		break;		
	}

	//currentTime += renderTime;
	glutPostRedisplay();
}

void MyKey(unsigned char key, int x, int y) {
	switch (key) {
	case VK_SPACE:
		if (!ball.get_move())
			ball.go();
		break;
	
	case VK_TAB:
		if (escape_box)
			escape_tab_cnt++;

		else if (main_page)
			main_page_tab_cnt++;	
		break;

	case VK_ESCAPE:
		escape_box = !escape_box;
		if (!escape_box)
			resume_game();
		break;

	case VK_RETURN:
		if (escape_box) {	
			if (escape_tab_cnt % 2) {
				if (main_page)
					exit(0);
				if (game_start_page || game_description_page) {
					main_page = true;	game_start_page = false;
					game_description_page = false;
				}
			}
			if (main_page)
				resume_game();
			escape_box = false;
		}

		else if (main_page) {	
			if (main_page_tab_cnt % 2) {
				main_page = false;	game_start_page = false;
				game_description_page = true;
			}
			else {
				main_page = false;	game_start_page = true;
				game_description_page = false;
			}
		}
		break;
	}
}

void MyTimer(int value) {
	if (value == 0) {
		Value = 21;
		add_brick();
	}

	if(game_start_page)
		if(!game_stop)
			Value -= 1;

	glutTimerFunc(1000, MyTimer, Value);
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(500, 100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT + UI_HEIGHT);
	glutCreateWindow("Shooting Brick Breaking Game of 20183198");
	set_brick();
	glutSpecialFunc(MySpecial);
	glutKeyboardFunc(MyKey);
	glutReshapeFunc(MyReshape);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(1000, MyTimer, Value);
	glutIdleFunc(RenderScene);
	glutMainLoop();
}