#include "Panel.h"
#include "Graphics.h"

Panel::Panel() : Control()
{
}

Panel::~Panel()
{
	for each (Control* child in _children)
	{
		if(child)
			delete child;
	}
}

bool
Panel::myPureFunction() 
{ 
	return true; 
}
