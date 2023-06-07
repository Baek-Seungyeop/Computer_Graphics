#include"HeaderCollect.h"

#pragma once
class UI {
public:
	void display();
};

#pragma once
class TextBox{
public:
	int x;
	int y;
	int width;
	int height;

	TextBox(int xx, int yy, int w, int h);
	void display();
};

#pragma once
class Life{
public:
	int	life;

	Life(int l);
	void display();
};

#pragma once
class Deadline{
public:
	int height;

	Deadline(int h);
	void display();
};

#pragma once
class Line{
public:
	float start_x;
	float start_y;
	float end_x;
	float end_y;

	Line(float x1, float y1, float x2, float y2);
	void display();
};

#pragma once
class MainPage {
public:
	int x;
	int y;
	int width;
	int height;

	MainPage(int xx, int yy, int w, int h);
	void display_main();
	void display_game_description();
	void display_game_start();
	void display_game_title();
	void display_toggle_circle(float dy);
};

#pragma once
class DescriptionPage {
public:
	int x;
	int y;
	int width;
	int height;

	string script[10];

	DescriptionPage(int xx, int yy, int w, int h);
	void display_text_box();
};

class EscapePage {
public:
	int x;
	int y;
	int width;
	int height;


	EscapePage(int xx, int yy, int w, int h);
	void display_escape_box(string title);
	void display_toggle_circle(float dx);
};