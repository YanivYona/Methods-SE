#include "ListComp.h"

ListComp::ListComp() : Control(), multiple_choices(true), select_sym('X'), focused_item_idx(-1)
{
	setFocusable(true);
	setClickable(true);
	setFrameType(SINGLE_SOLID);
	_focusable = true;
	_clickable = true;
}

ListComp::~ListComp() {}

Button* ListComp::initButton(string value)
{
	Button* btn = new Button(value);
	btn->setFocusable(true);
	btn->setClickable(false);
	btn->setFrameType(NONE);
	btn->setWidth(getWidth() - (BORDER_OFFSET * 2));
	btn->setHeight(1);
	btn->setColor(_background, _foreground);
	btn->setTop(getTop() + BORDER_OFFSET + getChildren().size());
	btn->setLeft(getLeft() + BORDER_OFFSET * 2);
	return btn;
}

bool ListComp::addItem(string item)
{
	if (getHeight() - (BORDER_OFFSET * 2) - 2 == _children.size())
	{
		return false;
	}

	string fixed_item;
	fixed_item.append(SYM_BULLET).append(SYM_SPACE).append(item);
	_children.push_back(initButton(fixed_item));
	selected_items.push_back(false);
	return true;
}

void ListComp::draw(Graphics& g)
{
	Control::draw(g);
	g.setBackground(Color::Black);
}

bool ListComp::removeSelectedItem(int idx)
{	
	if (!_children.empty()) {
		if (isValidIndex(idx)) {
			selected_items.at(idx) = false;
			string unselect = static_cast<Button*>(_children.at(idx))->getValue();
			unselect[1] = ' ';
			static_cast<Button*>(_children.at(idx))->setValue(unselect);
		}
	}
	else {
		return false;
	}
	return true;
}

void ListComp::setFocusedItem(const int item_idx)
{
	flipColorsAt(focused_item_idx);
	focused_item_idx = item_idx;
	flipColorsAt(focused_item_idx);
}

void ListComp::resetFocusIdx()
{
	focused_item_idx = -1;
}

bool ListComp::mousePressed(int x, int y, bool isLeft, Graphics& g)
{

	if (!isLeft) {
		return false;
	}

	int item_idx = clickedChildIndex(x, y);
	if (item_idx != -1)
	{
		if(focused_item_idx != item_idx)
			setFocusedItem(item_idx);
		setSelectedItem(item_idx, select_sym);
	}

	return true;
}

void ListComp::keyDown(int keyCode, char character, Graphics& g)
{
	switch (keyCode)
	{
	case VK_TAB:
		if (focused_item_idx == -1) {
			setFocusedItem(0);
			break;
		}

	case VK_NUMPAD2:
	case VK_DOWN:
		if (focused_item_idx == _children.size() - 1)
			setFocusedItem(0);
		else
			setFocusedItem(focused_item_idx + 1);
		return;

	case VK_NUMPAD8:
	case VK_UP:
		if (focused_item_idx == 0)
			setFocusedItem(_children.size() - 1);
		else
			setFocusedItem(focused_item_idx - 1);
		return;

	case VK_RETURN:
	case VK_SPACE:
		setSelectedItem(focused_item_idx, select_sym);
		return;
	default:
		break;
	}
}

void ListComp::clearSelection()
{
	for each (Button* child in _children)
	{
		string selected = child->getValue();
		selected[1] = ' ';
		child->setValue(selected);
	}
	return;
}

bool ListComp::isValidIndex(int idx)
{
	return (idx < 0 || idx > _children.size() - 1) ? false : true;
}

void ListComp::setSelectedItem(const int pos, char symbol)
{

	if (isValidIndex(pos))
	{
		if (multiple_choices == FALSE)
		{
			clearSelection();
		}
		
		string selected = getChildAt(pos)->getValue();
		if (selected[1] == symbol) {
			selected[1] = ' ';
			selected_items.at(pos) = false;
		}
		else {
			selected[1] = symbol;
			selected_items.at(pos) = true;
		}
		getChildAt(pos)->setValue(selected);
	}
}

int ListComp::clickedChildIndex(const short x, const short y)
{
	int child_idx;
	if (isInside(x, y, 
		getLeft() + BORDER_OFFSET, 
		getTop() + BORDER_OFFSET,
		getWidth() - (BORDER_OFFSET * 2), 
		getTop() - (BORDER_OFFSET * 2) - 2 ))
	{
		child_idx = y - getTop() - (BORDER_OFFSET*2);
		if (child_idx < 0 || child_idx > _children.size() - 1)
		{
			child_idx = -1;
		}
	}

	return child_idx;
}

Button* ListComp::getChildAt(int pos)
{
	if (isValidIndex(pos) == true)
	{
		return static_cast<Button*>(_children.at(pos));
	}
	return NULL;
}

void ListComp::flipColorsAt(int item_pos)
{
	if (isValidIndex(item_pos) == true)
	{

		_children.at(item_pos)->flipColor();
	}
}

const int ListComp::getFocusedIdx() 
{
	return focused_item_idx;
}