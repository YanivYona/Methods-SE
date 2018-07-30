#include "Control.h"

Control* Control::_focused_control = NULL;

Control* Control::getFocus()
{
	return _focused_control;
}
void Control::setFocus(Control& control)
{
	_focused_control = &control;
}
static bool isValidPos(const int &size, const int &pos) {
	if (pos < 0 || pos > size) {
		return false;
	}
	return true;

}
Control::Control() : _focusable(true), _left(0), _top(0), _width(0), _height(0), _other(NULL), _is_flipped(false) {}
Control::~Control() {
	for each (Control* child in _children)
	{
		if (child)
			delete child;
	}
}

void Control::draw(Graphics& g) {
	g.setBackground(_background);
	g.setForeground(_foreground);
	drawBorder(g);
	drawChildren(g);
}
void Control::drawBorder(Graphics& g) {

	char top_left, top_right, btm_left, btm_right;
	char line_horiz, line_vert;

	g.moveTo(_left, _top);

	if (_frame_type == NONE) {

		return;
	}
	top_left = (_frame_type == SINGLE_SOLID 
		? SINGLE_TOP_LEFT_CORNER : DOUBLE_TOP_LEFT_CORNER);
	top_right = (_frame_type == SINGLE_SOLID 
		? SINGLE_TOP_RIGHT_CORNER : DOUBLE_TOP_RIGHT_CORNER);
	btm_left = (_frame_type == SINGLE_SOLID 
		? SINGLE_BTM_LEFT_CORNER : DOUBLE_BTM_LEFT_CORNER);
	btm_right = (_frame_type == SINGLE_SOLID 
		? SINGLE_BTM_RIGHT_CORNER : DOUBLE_BTM_RIGHT_CORNER);
	line_horiz = (_frame_type == SINGLE_SOLID 
		? SINGLE_LINE_HORIZONTAL : DOUBLE_LINE_HORIZONTAL);
	line_vert = (_frame_type == SINGLE_SOLID 
		? SINGLE_LINE_VERTICAL : DOUBLE_LINE_VERTICAL);

	drawLine(top_left, line_horiz, top_right);
	g.moveTo(_left, _top + 1);

	for (short i = 0; i < _height - 2; i++) {
		drawLine(line_vert, 32, line_vert);
		g.moveTo(_left, _top + (short)i + 2);
	}

	drawLine(btm_left, line_horiz, btm_right);
	g.moveTo(_left + 1, _top + 1);
	g.moveTo(_left, _top);
}
void Control::drawChildren(Graphics& g) {

	for each (Control* child in _children) {
		child->draw(g);
	}
}
void Control::drawLine(char open_sym, char mid_sym, char end_sym) {

	for (short i = 0; i < _width - 1; i++) {
		if (i == 0) {
			cout << open_sym;
		}
		else {
			cout << mid_sym;
		}
	}
	cout << end_sym;
}


vector<Control*> Control::getChildren() 
{
	return _children;
}

void Control::setFrameType(FrameType frame_type)  
{
	_frame_type = frame_type;
}

void Control::setColor(Color bg, Color fg) 
{
	_background = bg;
	_foreground = fg;
}

bool Control::canGetFocus() 
{ 
	return _focusable; 
}

bool Control::canBeClicked()
{
	return _clickable;
}


void Control::getAllControls(vector<Control*>* controls) 
{
	controls = &_children;
}

static bool isInValidRange(short val) {
	if (val >= 0) {
		return true;
	}
	return false;
}

void Control::flipColor()
{
	Color temp = _background;
	_background = _foreground;
	_foreground = temp;
}

void Control::setTop(short y)
{
	short child_base_y;
	short diff_y = abs(y - _top);

	_top = y;

	for each (Control* child in _children) {
		child_base_y = child->getTop();
		child->setTop(diff_y + child_base_y);
	}

}

void Control::setLeft(short x)
{
	//todo: validate range of value
	short child_base_x;
	short diff_x = abs(x - _left);

	_left = x;
	
	for each (Control* child in _children) {
		child_base_x = child->getLeft();
		child->setLeft(diff_x + child_base_x);
	}

}

void Control::setWidth(short x)
{
	if (isInValidRange(x))
		_width = x;
}

void Control::setHeight(short y)
{
	if (isInValidRange(y))
		_height = y;
}

void Control::setOtherComponent(Control * other)
{
	_other = other;
}


void Control::add(Control* child)
{
	if (child) {
		//fix (update) child's position in relation to this parent:
		child->setLeft(_left + child->getLeft());
		child->setTop(_top + child->getTop());

		_children.push_back(child);
	}
}

bool Control::mousePressed(int x, int y, bool isLeft, Graphics& g) {
	
	if (isLeft)
	{
		for each (Control* child in _children)
		{
			if (isInside(x, y, child->_left, child->_top, child->_width, child->_height))
			{
				//debug(PG_DBG_INFO, "%s: found the clicked child.", fn);
				setFocus(*child);
				return child->mousePressed(x, y, isLeft, g);
			}
		}
	}
	return false;
}

void Control::setClickable(bool clickable)
{
	_clickable = clickable;
}

void Control::setFocusable(bool focusable)
{
	_focusable = focusable;
}

FrameType Control::getFrameType()
{
	return _frame_type;
}