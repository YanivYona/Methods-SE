#include "TextBox.h"
#include <math.h>

TextBox::TextBox()
{
	setClickable(true);
	setFocusable(true);
	setFrameType(SINGLE_SOLID);
	setLastPos({ _left + BORDER_OFFSET, _top + BORDER_OFFSET });
}

TextBox::TextBox(short left = 0, short top = 0, short width = 5, short height = 5) : Control()
{
	setLeft(left);
	setTop(top);
	setWidth(width);
	setHeight(height);
	setClickable(true);
	setFocusable(true);
	setFrameType(SINGLE_SOLID);
	setLastPos({ _left + BORDER_OFFSET, _top + BORDER_OFFSET });
}

void TextBox::draw(Graphics& g) {
	Control::draw(g);
	drawValue(g);
}

COORD TextBox::valueEndPos()
{
	short exact_cols_size = getWidth() - (BORDER_OFFSET * 2);
	short max_x, max_y;

	if ((_value.size() % exact_cols_size) == 0 )
	{
		max_x = getLeft() + _value.size();
	}
	else
	{
		max_x = getLeft() + (_value.size() % exact_cols_size);
	}

	max_y = getTop() + BORDER_OFFSET + ceil(_value.size() / exact_cols_size);

	return { max_x, max_y };
}

bool TextBox::mousePressed(int x, int y, bool isLeft, Graphics& g)
{
	g.setCursorVisibility(true);
	g.setBackground(_background);
	g.setForeground(_foreground);
	
	if (_value.empty()) {
		g.moveTo(getLeft()+BORDER_OFFSET, getTop()+BORDER_OFFSET);
	}
	else
	{	
		COORD end_str_pos = valueEndPos();

		if (y >= end_str_pos.Y && x >= end_str_pos.X ||
			y > end_str_pos.Y)
		{
			if (end_str_pos.X == getLeft() + getWidth() - BORDER_OFFSET*2)
			{
				setLastPos({getLeft() + 1, end_str_pos.Y});
			}
			else
			{
				setLastPos({end_str_pos.X + 1, end_str_pos.Y });
			}
		}
		else
		{
			setLastPos({(short)x, (short)y});
		}
	}
	return true;
}

static bool isInTextBoundaries(COORD max_pos, COORD new_pos)
{
	if (new_pos.Y >= max_pos.Y && new_pos.X-1 > max_pos.X ||
		new_pos.Y > max_pos.Y)
	{
		return false;
	}
	return true;
}

bool TextBox::isValidMove(int key_code, Graphics& g)
{
	COORD cur_pos = g.GetConsoleCursorPosition();
	COORD end_str_pos = valueEndPos();
	COORD new_pos;

	switch (key_code)
	{
		case VK_LEFT:
			new_pos = { cur_pos.X - 1 , cur_pos.Y};
			return new_pos.X > getLeft() && isInTextBoundaries(end_str_pos, new_pos);

		case VK_RIGHT:
			new_pos = { cur_pos.X + 1 , cur_pos.Y };
			return new_pos.X < getLeft() + getWidth() - BORDER_OFFSET && isInTextBoundaries(end_str_pos, new_pos);

		case VK_UP:
			new_pos = { cur_pos.X, cur_pos.Y - 1 };
			return new_pos.Y > getTop() && isInTextBoundaries(end_str_pos, new_pos);

		case VK_DOWN:
			new_pos = { cur_pos.X, cur_pos.Y + 1 };
			return new_pos.Y < getTop() + getHeight() - BORDER_OFFSET && isInTextBoundaries(end_str_pos, new_pos);

		default:
			break;
	}

	return false;
}

void TextBox::handleBackspace(COORD curr_pos)
{
	int idx = posToIndex(curr_pos);

	if (idx != -1)
	{
		if (idx % (getWidth() - (BORDER_OFFSET * 2)) == 0)
		{
			if (idx == 0)
			{
				return;
			}
			else
			{
				setLastPos({ getLeft() + getWidth() - (BORDER_OFFSET * 2), getLastPos().Y - 1 });
			}
		}
		else
		{
			setLastPos({ getLastPos().X - 1, getLastPos().Y });
		}
		auto itr = _value.begin() + idx - 1;
		_value.erase(itr);
	}
	return;
}

void TextBox::handleDelete(COORD curr_pos)
{
	int idx = posToIndex(curr_pos);
	if (idx != -1)
	{
		if (curr_pos.X + 1 == getLeft() + getWidth())
		{
			return;
			if (curr_pos.Y == (getTop() + getWidth() - BORDER_OFFSET))
			{
				return;
			}
		}
		setLastPos(curr_pos);
		auto itr = _value.begin() + idx;
		_value.erase(itr);
	}
	return;
}

void TextBox::keyDown(int keyCode, char character, Graphics& g)
{	
	COORD c_pos = g.GetConsoleCursorPosition();
	int idx = posToIndex(c_pos);
	
	switch (keyCode)
	{
	case VK_NUMPAD4:
	case VK_LEFT:
		if (isValidMove(VK_LEFT, g))
			setLastPos({ c_pos.X - 1, c_pos.Y });
		return;
	case VK_NUMPAD6:
	case VK_RIGHT:
		if (isValidMove(VK_RIGHT, g))
			setLastPos({ c_pos.X + 1, c_pos.Y });
			
		return;
	case VK_NUMPAD8:
	case VK_UP:
		if (isValidMove(VK_UP, g))
			setLastPos({ c_pos.X, c_pos.Y - 1 });
		return;
	case VK_NUMPAD2:
	case VK_DOWN:
		if (isValidMove(VK_DOWN, g))
			setLastPos({ c_pos.X, c_pos.Y + 1 });
		return;

	case VK_BACK:
		return handleBackspace(c_pos);
	case VK_DELETE:
		return handleDelete(c_pos);

	case VK_RETURN:
		return;

	default:
		break;
	} 

	int MAX_TEXT_LENGTH_IN_BOX = (getWidth() - BORDER_OFFSET * 2) * (getHeight() - BORDER_OFFSET * 2);

	if (character != NULL)
	{
		if (_value.size() < MAX_TEXT_LENGTH_IN_BOX)
		{

			if (idx != -1)
			{
				if (idx == _value.size())
				{
					_value.push_back(character);
				}
				else
				{
					auto itr = _value.begin() + idx;
					_value.insert(itr, character);

					return;
				}
			}
			else
			{
				return;
			}
			
			if (getLastPos().X + 1 == getLeft() + getWidth() - BORDER_OFFSET && getLastPos().Y < getTop() + getHeight() - BORDER_OFFSET )
			{
				setLastPos({ getLeft() + BORDER_OFFSET, getLastPos().Y + 1});
			}
			else
			{
				setLastPos({ getLastPos().X + 1 , getLastPos().Y});
			}
		}
	}
}

int TextBox::posToIndex(COORD pos)
{

	int exact_row_size = getWidth() - (BORDER_OFFSET * 2);
	int lines = pos.Y - getTop() - BORDER_OFFSET;
	int idx = pos.X - getLeft() - BORDER_OFFSET + (lines * exact_row_size);

	return (idx > _value.size() || idx < 0)  ?  -1 : idx;

}

void TextBox::drawValue(Graphics& g)
{
	short exact_row_size = getWidth() - (BORDER_OFFSET * 2);
	short exact_col_size = getHeight() - (BORDER_OFFSET * 2);;

	g.moveTo(getLeft() + BORDER_OFFSET, getTop() + BORDER_OFFSET);

	for (short i = 0, j = 0; i < _value.size(); i++)
	{ 
		if (i == exact_col_size * exact_row_size)
		{
			return;
		}

		if (((i != 0) && (i % exact_row_size)) == 0)
		{
			g.moveTo(_left + 1, (_top + BORDER_OFFSET) + (j++));	
		}

		string temp_str;
		temp_str.push_back(_value.at(i));
		g.write(temp_str);
	}

}

COORD TextBox::getLastPos()
{
	return _last_pos;
}

void TextBox::setLastPos(COORD pos)
{
	_last_pos = pos;
}

void TextBox::setTop(short y)
{
	Control::setTop(y);
	setLastPos({ _left + BORDER_OFFSET, _top + BORDER_OFFSET });
}

void TextBox::setLeft(short x)
{
	Control::setLeft(x);
	setLastPos({_left + BORDER_OFFSET, _top + BORDER_OFFSET });
}



bool  TextBox::myPureFunction()
{
	return true;
}

string TextBox::getStringValue() {
	return _value;
}