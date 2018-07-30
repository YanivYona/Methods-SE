#pragma once
#include "Control.h"
#include "Button.h"
class ComboBox :public Control
{
private:
	int _drop_down_menu_width, _drop_down_menu_height;
	int _options_list_size, _max_option_size;
	int _selected_item;
	bool _is_menu_open;
	vector<string> _options_list;
	Button* _menu_down_button;
	Label* _selected_val_label;

	void initChildren();
	int findMaxString(vector<string> options_list);
	void openDropDownMenu();
	void closeDropDownMenu();
	bool findClickedItem(int x, int y);
public:
	ComboBox(short top, short left, vector<string> options_list);
	~ComboBox();
	virtual bool mousePressed(int x, int y, bool isLeft, Graphics& g);
	virtual void keyDown(int keyCode, char character, Graphics& g);
	bool myPureFunction() { return false; }

};

