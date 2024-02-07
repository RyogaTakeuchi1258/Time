#include "../dxlib_ext/dxlib_ext.h"
#include "option_UI.h"

OptionUI::OptionUI() {
	option_ui_gph_hdl_ = LoadGraph("graphics/flame.png");
}

OptionUI::~OptionUI() {
	DeleteGraph(option_ui_gph_hdl_ );
}

void OptionUI::draw(){
	DrawRotaGraph(100,100,1,0, option_ui_gph_hdl_,true);
}