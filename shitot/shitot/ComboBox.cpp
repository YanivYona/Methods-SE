#include "ComboBox.h"

ComboBox::ComboBox(short top, short left,vector<string> options_list)
{
	_selected_item = 1;	
	_is_menu_open = false;
	_top = top;
	_left = left;
	_options_list = options_list;
	_options_list_size = _options_list.size();
	_max_option_size = findMaxString(_options_list);
	_width = 3 + _max_option_size + 2;	
	_height = 3;
	initChildren();

	setFrameType(SINGLE_SOLID);
}

ComboBox::~ComboBox()
{
}

int ComboBox::findMaxString(vector<string> options_list)
{
	int max_string_size = 0;
	for each(string str in options_list) {
		if (str.size() > max_string_size)
			max_string_size = str.size();
	}
	return max_string_size;
}

void ComboBox::closeDropDownMenu()
{
	_children.erase(_children.begin() + 2, _children.end());
	_height -= 3 * _options_list.size();
	_is_menu_open = false;
}

void ComboBox::openDropDownMenu()
{
	Button *btn_ptr = 0;
	for (int i = 0, j=1 ; i < _options_list.size(); ++i, ++j) {
		add(btn_ptr = new Button(_options_list[i]));
		btn_ptr->setLeft(_left);
		btn_ptr->setTop(_children[j]->getTop() + 3);
		btn_ptr->setWidth(_width);
		btn_ptr->setColor(Color::Black, Color::White);
	}
	if (_selected_item > 1 && _selected_item < _children.size()) {
		_children[_selected_item]->flipColor();
	}
	_height +=  3 * _options_list.size();
	_is_menu_open = true;
}

void ComboBox::initChildren()
{
	add(_menu_down_button = new Button("v"));
	_menu_down_button->setTop(_top);
	_menu_down_button->setLeft(_left);
	_menu_down_button->setColor(Color::Black, Color::White);

	add(_selected_val_label = new Label("COMBO-BOX"));
	_selected_val_label->setTop(_top);
	_selected_val_label->setLeft(_left + 3);
	_selected_val_label->setHeight(5);
	_selected_val_label->setColor(Color::Black, Color::White);

	Label *ptr = _selected_val_label;
}


bool ComboBox::findClickedItem(int x, int y)
{
	for (int i = 2; i < _children.size(); ++i) {
		if (isInside(x, y, _children[i]->getLeft(), _children[i]->getTop(), _children[i]->getWidth(), _children[i]->getHeight())) {
			_selected_item = i;
			_selected_val_label->setValue(_children[i]->getStringValue());
			return true;
		}
	}
	return false;
}

bool ComboBox::mousePressed(int x, int y, bool isLeft, Graphics& g)
{
	Button *item_button_ptr;
	bool item_clicked = false;

	if (!_is_menu_open) {
		if (isInside(x, y, _menu_down_button->getLeft(), _menu_down_button->getTop(), _menu_down_button->getWidth(), _menu_down_button->getHeight())) {
			openDropDownMenu();
			return true;
		}
	}
	if (_is_menu_open) {
		if (isInside(x, y, _menu_down_button->getLeft(), _menu_down_button->getTop(), _menu_down_button->getWidth(), _menu_down_button->getHeight())) {
			closeDropDownMenu();
			return true;
		}
		item_clicked = findClickedItem(x,y);
		if (item_clicked) closeDropDownMenu();
		return item_clicked;
	}
	return false;
}

void ComboBox::keyDown(int keyCode, char character, Graphics & g)
{
	if (!_is_menu_open) return;
	switch (keyCode)
	{
	case VK_TAB:
		break;
	case VK_NUMPAD8:
	case VK_UP:
		if (_selected_item - 1 > 1) {
			_children[_selected_item]->flipColor();
			_children[--_selected_item]->flipColor();
		}
		return;
	case VK_NUMPAD2:
	case VK_DOWN:
		if (_selected_item == 1 && _children.size() > 2) {
			_children[++_selected_item]->flipColor();
		}
		else if (_selected_item + 1 < _children.size()) {
			_children[_selected_item]->flipColor();
			_children[++_selected_item]->flipColor();
		}
		return;
	case VK_RETURN:
		if (_selected_item > 1) {
			_selected_val_label->setValue(_children[_selected_item]->getStringValue());
			closeDropDownMenu();
			return;
		}
		break;
	case VK_SPACE:
		return;

	default:
		break;
	}
}