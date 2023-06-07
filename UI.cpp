#include "UI.h"
#include "HeaderCollect.h"
#include "Constant.h"
#include "Function.h"

void UI::display() {
	glColor3f(0.0, 1.0, 1.0);

	glBegin(GL_POLYGON);
		glVertex2f(0, WIN_HEIGHT);
		glVertex2f(0, WIN_HEIGHT+UI_HEIGHT);
		glVertex2f(WIN_WIDTH, WIN_HEIGHT + UI_HEIGHT);
		glVertex2f(WIN_WIDTH, WIN_HEIGHT);
	glEnd();
}

TextBox::TextBox(int xx, int yy, int w, int h) : x(xx), y(yy), width(w), height(h) {}

void TextBox::display() {
	glColor3f(1.0, 1.0, 1.0);
	
	glBegin(GL_POLYGON);
		glVertex2i(x, y);
		glVertex2i(x, y + height);
		glVertex2i(x + width, y + height);
		glVertex2i(x + width, y);
	glEnd();
}

Life::Life(int l) : life(l) {}

void Life::display() {
	glColor3f(1.0, 0.0, 0.0);

	float delta = 2 * PI / 36;
	float delta_x = 50.0F;

	for (int i = 0; i < 3 - life; i++)
		draw_circle(GL_POINTS, 450 + delta_x * i, 825, 10);

	for (int i = 3 - life; i < 3; i++)
		draw_circle(GL_POLYGON, 450 + delta_x * i, 825, 10);
}

Deadline::Deadline(int h) : height(h) {}

void Deadline::display() {
	glColor3f(0.5, 0.5, 0.5);

	glLineWidth(3.0F);
	glBegin(GL_LINE_LOOP);
		glVertex2i(0, height);
		glVertex2i(WIN_WIDTH, height);
	glEnd();
}

Line::Line(float x1, float y1, float x2, float y2) : start_x(x1), start_y(y1), end_x(x2), end_y(y2) {}

void Line::display() {
	glColor3f(0.5, 0.5, 0.5);

	glLineWidth(ball_radius);
	glBegin(GL_LINE_LOOP);
		glVertex2f(start_x, start_y);
		glVertex2f(end_x, end_y);
	glEnd();
}

MainPage::MainPage(int xx, int yy, int w, int h) : x(xx), y(yy), width(w), height(h) {}

void MainPage::display_main() {
	glColor3f(0.7, 0.7, 0.7);

	glBegin(GL_POLYGON);
		glVertex2f(x, y);
		glVertex2f(x + width, y);
		glVertex2f(x + width, y + height);
		glVertex2f(x, y + height);
	glEnd();
}

void MainPage::display_game_description() {
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_POLYGON);
		glVertex2f(350, 350);
		glVertex2f(350, 400);
		glVertex2f(550, 400);
		glVertex2f(550, 350);
	glEnd();
	draw_text("Game Description", 390, 370);
}

void MainPage::display_game_start() {
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_POLYGON);
		glVertex2f(350, 450);
		glVertex2f(350, 500);
		glVertex2f(550, 500);
		glVertex2f(550, 450);
	glEnd();
	draw_text("Game Start", 410, 470);
}

void MainPage::display_game_title() {
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_POLYGON);
	glVertex2f(100, 600);
	glVertex2f(100, 800);
	glVertex2f(500, 800);
	glVertex2f(500, 600);
	glEnd();
	draw_text("Brick breaking game of 20183198", 180, 690);
}

void MainPage::display_toggle_circle(float dy) {
	glColor3f(1.0, 0.0, 0.0);

	draw_circle(GL_POLYGON, 370, dy, 5);
}

DescriptionPage::DescriptionPage(int xx, int yy, int w, int h) : x(xx), y(yy), width(w), height(h) {
	script[0] = "1. Left, Right arrow key - ";
	script[1] = "   Ball moveing -> Left, Right control of the Stick";
	script[2] = "   Ball on Stick : Left, Right control of Ball direction";
	script[3] = "2. Tab key - ";
	script[4] = "   Main Page : Choosing between Start and Description";
	script[5] = "   Message Box : Choosing between Yes and No";
	script[6] = "3. Esc key - Show Message Box";
	script[7] = "4. Enter key - ";
	script[8] = "   Main Page : Enter the page";
	script[9] = "   Message Box : Exit or Stay this page";
}

void DescriptionPage::display_text_box() {
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_POLYGON);
		glVertex2f(50, 100);
		glVertex2f(50, 800);
		glVertex2f(550, 800);
		glVertex2f(550, 100);
	glEnd();

	for (int i = 0; i < 10; i++) {
		draw_text(script[i], 75, 770 - 70 * i);
	}
	
}

EscapePage::EscapePage(int xx, int yy, int w, int h) : x(xx), y(yy), width(w), height(h) {}

void EscapePage::display_escape_box(string title) {
	glColor3f(0.9, 0.9, 0.9);

	glBegin(GL_POLYGON);
		glVertex2f(x, y);
		glVertex2f(x + width, y);
		glVertex2f(x + width, y + height);
		glVertex2f(x, y + height);
	glEnd();

	int len = title.length();
	draw_text(title, x + width / 2 - len * 4, y + height - 20);
	draw_text("Yes", x + width / 4, y + 20);
	draw_text("No", x + 3 * width / 4, y + 20);
}

void EscapePage::display_toggle_circle(float dx) {
	glColor3f(1.0, 0.0, 0.0);

	draw_circle(GL_POLYGON, dx - 20, y + 25, 5);
}