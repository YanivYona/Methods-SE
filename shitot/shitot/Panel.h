#pragma once

#include "Control.h"

class Panel :	public Control
{
public:
	Panel();
	virtual ~Panel();
	bool myPureFunction();
};