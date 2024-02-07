#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class UIBase {
public:
	virtual ~UIBase() {};
	virtual void draw() = 0;
};