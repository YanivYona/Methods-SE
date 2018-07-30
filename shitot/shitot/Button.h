#pragma once
#include "Label.h"

class NumericBox;

typedef void (*OnButtonClicked) (NumericBox* , int, int);

class Button : public Label
{

public:
	OnButtonClicked clickFunc;
	Button();
	Button(string& s);
	Button(const char* s);
	virtual ~Button();
	virtual bool myPureFunction();
	void draw(Graphics& g);
	bool mousePressed(int x, int y, bool isLeft, Graphics& g);
	void fixDimensions();
};

