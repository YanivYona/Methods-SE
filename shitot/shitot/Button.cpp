#include "Button.h"

Button::Button() : Label()
{
	_focusable = false;
	_clickable = true;
	setFrameType(SINGLE_SOLID);
	fixDimensions();
}

Button::Button(string& s) : Button()
{
	setValue(s);
	fixDimensions();
	setHeight(3);
}

Button::Button(const char* s) : Button(string(s))
{
}

Button::~Button()
{
}

void Button::fixDimensions(){
	_width = getValue().size() + BORDER_OFFSET + 1;
}

bool Button::mousePressed(int x, int y, bool isLeft, Graphics& g)
{
	bool result = false;
	if (isLeft) {
		if ( _other != NULL) {
			_other->mousePressed(x, y, true, g);
		}
		else {
			setColor(_foreground, _background);
		}
		result = true;
	}
	return result;
}

void Button::draw(Graphics& g) {
	Control::draw(g);
	g.moveTo(_left + 1, _top + 1);
	g.write(value);
	g.moveTo(_left, _top);
}

bool Button::myPureFunction()
{
	return false;
}

