#pragma once
#include "Button.h"

class ListComp : public Control
{
protected:
	bool multiple_choices;
	char select_sym;
	int focused_item_idx;
	vector<bool> selected_items;

public:
	ListComp();
	~ListComp();

	virtual void draw(Graphics& g);
	virtual bool mousePressed(int x, int y, bool isLeft, Graphics& g);
	virtual void keyDown(int keyCode, char character, Graphics& g) ;
	virtual bool addItem(string item);
	virtual bool removeSelectedItem(int idx);	virtual int getSelectedItemPos() { return -1; }	int clickedChildIndex(const short x, const short y);
	bool isValidIndex(int idx);
	Button* getChildAt(int pos);
	Button* initButton(string value);
	void setSelectedItem(const int pos, char symbol);	void clearSelection();
	void flipColorsAt(int item_pos);
	void setFocusedItem(const int item_idx);
	void resetFocusIdx();
	const int getFocusedIdx();
	void add(Control* child) {}
	bool myPureFunction() { return true; }
};