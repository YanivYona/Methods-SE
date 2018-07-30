#include "EventEngine.h"
#include "Graphics.h"
#include "Button.h"
#include "Panel.h"
#include "TextBox.h"
#include "NumericBox.h"
#include "ComboBox.h"
#include "RadioBox.h"
#include "NumericBox.h"

int main(int argc, char** argv)
{

	Panel _panel;
	Control& panel = _panel;
	_panel.setColor(Color::White, Color::Black);
	_panel.setLeft(25);
	_panel.setTop(10);
	_panel.setWidth(90);
	_panel.setHeight(30);
	_panel.setFrameType(DOUBLE_SOLID);

	TextBox text_box(8, 2, 16, 4);
	text_box.setColor(Color::Black, Color::White);
	_panel.add(&text_box);

	NumericBox boxi(22, 8, 100, 1, 50);
	panel.add(&boxi);

	Label label("LABEL");
	label.setColor(Color::Black, Color::White);
	label.setLeft(9);
	label.setTop(15);
	_panel.add(&label);

	RadioBox radio_box;
	radio_box.setLeft(30);
	radio_box.setTop(2);
	radio_box.setWidth(18);
	radio_box.setHeight(10);
	radio_box.setColor(Color::Black, Color::White);

	vector<string> options
		= { "1", "2", "3" , "4", "5" };
	for each (string item in options)
	{
		radio_box.addItem(item);
	}

	ComboBox cb(22, 30, options);
	_panel.add(&cb);

	Button button("BUTTON");
	button.setLeft(30);
	button.setTop(15);
	button.setColor(Color::Black, Color::White);
	_panel.add(&button);

	_panel.add(&radio_box);

	EventEngine engine;
	engine.run(_panel);

	return 0;
}