#include "Control.h"
#include <iostream>
#include <string>

using namespace std;

class Label: public Control
{   
	protected:
		string value;
  public:
		Label();
		Label(string);
		string getValue();
		virtual string getStringValue() { return value; }
		void setValue(string);
		virtual void draw(Graphics& g, int x, int y, size_t z);
		void draw(Graphics& g);
		bool myPureFunction();
};
