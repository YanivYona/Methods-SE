#include "Label.h"

Label::Label() : Control()
{
	setValue("Label");
	_frame_type = NONE;
	setFocusable(false);
}

Label::Label(string value) : 
	Control()
{
	Label::Label();
	setValue(value);
}

string Label::getValue()
{
    return this->value;
}

void Label::setValue(string value)
{
	_width = value.size();
	_height = 1;

  this->value = value;
}


void Label::draw(Graphics& g, int x, int y, size_t z)
{
    if (!z)
        g.write(value);

}

void Label::draw(Graphics& g) {
	g.setBackground(_background);
	g.setForeground(_foreground);
	g.moveTo(_left+1, _top+1);
	g.write(value);
	g.moveTo(_left, _top);
}

bool Label::myPureFunction() {
	return false;
}
