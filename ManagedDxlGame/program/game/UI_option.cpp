#include "../dxlib_ext/dxlib_ext.h"
#include "UI_option.h"

UIOption::UIOption() {
	window_gph_hdl_ = LoadGraph("graphics/flame.png");
	bar_gph_hdl_ = LoadGraph("graphics/bar.png");
	cursor_gph_hdl_ = LoadGraph("graphics/cursor.png");
}

UIOption::~UIOption() {
	DeleteGraph(window_gph_hdl_);
	DeleteGraph(bar_gph_hdl_);
	DeleteGraph(cursor_gph_hdl_);
}

void UIOption::draw() {
    DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 1.0f, 0, window_gph_hdl_, true);
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, 270, 0.4f, 0, bar_gph_hdl_, true);
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, 270, 0.05f, tnl::ToRadian(90), cursor_gph_hdl_, true);
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, 370, 0.4f, 0, bar_gph_hdl_, true);
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, 370, 0.05f, tnl::ToRadian(90), cursor_gph_hdl_, true);

	for (int i = 0; i < 5; i++) {
		if (i == 0){
			SetFontSize(60);
			DrawStringEx(520, 100 + i * 100, -1, "%s", setting_messege[i].c_str());
			SetFontSize(30);
		}
		else if(i == 3 || i == 4){
			DrawStringEx(550, 150 + i * 100, -1, "%s", setting_messege[i].c_str());
		}
		else {
			DrawStringEx(300, 150 + i * 100, -1, "%s", setting_messege[i].c_str());
		}
	}
}

bool UIOption::update() {
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		int mouseX = tnl::Input::GetMousePosition().x;
		int mouseY = tnl::Input::GetMousePosition().y;

		// クリックされた範囲の判定
		if (mouseX >= 550 && mouseX <= 700 && mouseY >= 450 && mouseY <= 480) {


		}
		if (mouseX >= 550 && mouseX <= 700 && mouseY >= 550 && mouseY <= 580) {
			// オプション画面を閉じる処理
			return false;
		}
	}
	return true;
}
