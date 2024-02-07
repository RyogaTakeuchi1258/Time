#include "../dxlib_ext/dxlib_ext.h"
#include "UI_CurrentXbutton.h"

UI_CurrentXbutton::UI_CurrentXbutton() {
	window_gph_hdl_ = LoadGraph("graphics/messege_tile.png");
}

UI_CurrentXbutton::~UI_CurrentXbutton() {
	DeleteGraph(window_gph_hdl_);
}

void UI_CurrentXbutton::draw() {
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, 630, 0.3f, 0, window_gph_hdl_, true);
	for (int i = 0; i < 4; i++) {
		if (i == 0) {
			DrawStringEx(470, 570, -1, "%s", setting_messege[i].c_str());
		}
		else {
			DrawStringEx(595, 570 + i*30, -1, "%s", setting_messege[i].c_str());
		}
	}
}