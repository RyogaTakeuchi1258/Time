#pragma once
#include "ui_base.h"

class OptionUI : public UI_Base {
public:
	OptionUI();
	~OptionUI();
	void draw() override;

private:
	int option_ui_gph_hdl_;
};