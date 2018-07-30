#pragma once
#include "Control.h"
class TextBox : public Control
{
	COORD _last_pos;
	string _value;

public:
	TextBox();
	TextBox(short left, short top, short width, short height);
	~TextBox() {}

	bool myPureFunction();
	void draw(Graphics& g);
	void drawValue(Graphics& g);
	bool mousePressed(int x, int y, bool isLeft, Graphics& g);
	void keyDown(int keyCode, char character, Graphics& g);
	COORD valueEndPos();
	COORD getLastPos();
	void setLastPos(COORD pos);
	bool isValidMove(int key_code, Graphics& g);
	int posToIndex(COORD pos);
	void handleBackspace(COORD current_pos);
	void handleDelete(COORD curr_pos);
	void setLeft(short x);
	void setTop(short y);
	string getStringValue();
};

