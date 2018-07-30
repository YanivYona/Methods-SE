#include "EventEngine.h"
#include "Button.h"
#include "Panel.h"
#include "TextBox.h"
#include "NumericBox.h"
#include "ComboBox.h"
#include "RadioBox.h"
#include "NumericBox.h"
#include <vector>
#include <algorithm>
using namespace std;

EventEngine::EventEngine(DWORD input, DWORD output)
	: _console(GetStdHandle(input)), _graphics(output)
{
	GetConsoleMode(_console, &_consoleMode);
	SetConsoleMode(_console, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
}

static void handleListFocus(Control* control)
{
	if (static_cast<ListComp*>(control)->getFocusedIdx() == control->getChildren().size() - 1){
		static_cast<ListComp*>(control)->flipColorsAt(control->getChildren().size() - 1);
		static_cast<ListComp*>(control)->resetFocusIdx();
	}
}

static bool canStillNavigate(Control* control)
{
	return (static_cast<ListComp*>(control)->getFocusedIdx() == control->getChildren().size() - 1) ? false : true;
}

static bool isAList(Control* control)
{
	if (dynamic_cast<RadioBox*>(control)!= NULL)
		return true;
	return false;
}

static bool isATextBox(Control* control) {
	if (dynamic_cast<TextBox*>(control) != NULL)
	{
		return true;
	}
	return false;
}

static void setFirstFocusableChild(Control& control)
{
	if (!control.getChildren().empty())
	{
		Control::setFocus(*(control.getChildren().at(0)));

		for (size_t i = 0; i < control.getChildren().size() ; i++)
		{
			if (control.getChildren().at(i)->canGetFocus())
			{
				Control::setFocus(*(control.getChildren().at(i)));
				return;
			}
		}
	}

	return;
	
}

void EventEngine::run(Control& control)
{
	bool redraw = true;
	setFirstFocusableChild(control);
	while (true)
	{
		_graphics.setCursorVisibility(false);

		if (redraw == true) {
			_graphics.clearScreen();
			control.draw(_graphics);
			redraw = false;
		}
		
		auto focused_control = Control::getFocus();

		if (isATextBox(focused_control))
		{
			_graphics.setCursorVisibility(true);
			_graphics.moveTo(
				static_cast<TextBox*>(Control::getFocus())->getLastPos().X,
				static_cast<TextBox*>(Control::getFocus())->getLastPos().Y);
		}
		else
		{
			_graphics.setCursorVisibility(false);
		}

		INPUT_RECORD record;
		DWORD count;
		ReadConsoleInput(_console, &record, 1, &count);
		switch (record.EventType)
		{
		case KEY_EVENT:
		{
			if (focused_control != nullptr && record.Event.KeyEvent.bKeyDown)
			{
				auto code = record.Event.KeyEvent.wVirtualKeyCode;
				auto chr = record.Event.KeyEvent.uChar.AsciiChar;
				if (code == VK_TAB)
				{
					if (isAList(focused_control)) {
						if (canStillNavigate(focused_control)) {
							focused_control->keyDown(code, chr, _graphics);
						}
						else {
							handleListFocus(focused_control);
							moveFocus(control, focused_control);
						}
						
					}
					else {
						moveFocus(control, focused_control);
					}
					
				}
				else
				{
					focused_control->keyDown(code, chr, _graphics);
				}
				redraw = true;
			}
			break;
		}
		case MOUSE_EVENT:
		{
			auto button = record.Event.MouseEvent.dwButtonState;
			auto coord = record.Event.MouseEvent.dwMousePosition;
			auto x = coord.X;
			auto y = coord.Y;

			if (button == FROM_LEFT_1ST_BUTTON_PRESSED || button == RIGHTMOST_BUTTON_PRESSED)
			{
				if (control.mousePressed(x, y, button == FROM_LEFT_1ST_BUTTON_PRESSED, _graphics))
				{
					redraw = true;
				}
			}
			break;
		}
		default:
			break;
		}
	}
}

EventEngine::~EventEngine()
{
	SetConsoleMode(_console, _consoleMode);
}

void EventEngine::moveFocus(Control &main, Control *focused) 
{
	vector<Control*> controls = main.getChildren();
	auto iter = find(controls.begin(), controls.end(), focused);

	do
		if (++iter == controls.end())
			iter = controls.begin();
	while (!(*iter)->canGetFocus());

	Control::setFocus(**iter);
}