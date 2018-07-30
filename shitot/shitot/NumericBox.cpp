#include "NumericBox.h"

NumericBox::NumericBox(short top, short left, int max, int min, int value)
{
	_top = top;
	_left = left;
	_max = max;
	_min = min;
	_value = value;
	_width = 2*3 + to_string(value).size() + 2;
	_height = 3;	
	initChildren(value);
	
	_focusable = false;
	setFrameType(SINGLE_SOLID);
}

NumericBox::~NumericBox()
{
}
void NumericBox::dec()
{
	if (_value - 1 >= _min) {
		numeric_label->setValue(to_string(--_value));
	}

}

void NumericBox::draw(Graphics& g)
{
	Control::draw(g);
}

void NumericBox::initChildren(int val)
{
	add(_min_button = new Button("-"));
	add(numeric_label = new Label(to_string(val)));
	add(_plus_button = new Button("+"));

	_min_button->setLeft(_left);
	_min_button->setTop(_top);
	_min_button->setColor(Color::Black, Color::White);

	numeric_label->setLeft(_left + 3);
	numeric_label->setTop(_top);
	numeric_label->setHeight(3);
	numeric_label->setColor(Color::Black, Color::White);

	_plus_button->setLeft(numeric_label->getLeft() + numeric_label->getWidth() + 2);
	_plus_button->setTop(_top);
	_plus_button->setColor(Color::Black, Color::White);
}

bool NumericBox::mousePressed(int x, int y, bool isLeft, Graphics& g)
{
	if (isInside(x, y, _min_button->getLeft(), _min_button->getTop(), _min_button->getWidth(), _min_button->getHeight())) {
		dec();
		return true;
	}
	else if (isInside(x, y, _plus_button->getLeft(), _plus_button->getTop(), _plus_button->getWidth(), _plus_button->getHeight())) {
		inc();
		return true;
	}
	return false;
}

void NumericBox::inc()
{
	if ( _value + 1 <= _max) {
		numeric_label->setValue(to_string(++_value));
	}
}

