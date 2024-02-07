#include "../dxlib_ext/dxlib_ext.h"
#include "UI_FutureXbutton.h"

UI_FutureXbutton::UI_FutureXbutton() {
	window_gph_hdl_ = LoadGraph("graphics/messege_tile.png");
}

UI_FutureXbutton::~UI_FutureXbutton() {
	DeleteGraph(window_gph_hdl_);
}

bool UI_FutureXbutton::update() {
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		int mouseX = tnl::Input::GetMousePosition().x;
		int mouseY = tnl::Input::GetMousePosition().y;
		// ƒNƒŠƒbƒN‚³‚ê‚½”ÍˆÍ‚Ì”»’è
		if (mouseX >= 600 && mouseX <= 690 && mouseY >= 660 && mouseY <= 690) {

		}
		if (mouseX >= 600 && mouseX <= 690 && mouseY >= 690 && mouseY <= 720) {

		}
		if (mouseX >= 595 && mouseX <= 685 && mouseY >= 660 && mouseY <= 690) {
			return false;
		}
	}
	return true;
}

void UI_FutureXbutton::draw() {
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, 630, 0.3f, 0, window_gph_hdl_, true);
	for (int i = 0; i < 4; i++) {
		if (i == 0) {
			DrawStringEx(470, 570, -1, "%s", setting_messege[i].c_str());
		}
		else {
			DrawStringEx(595, 570 + i * 30, -1, "%s", setting_messege[i].c_str());
		}
	}
}