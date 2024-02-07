#pragma once
#include "UI_base.h"

class UI_PastXbutton : public UIBase {
public:
	UI_PastXbutton();
	~UI_PastXbutton() override;
	void draw() override;
private:
	// 設定画面の文字
	const std::string setting_messege[4] = { "どの時間に行きますか？","未　来","現　在","やめる" };
	// 設定画面の背景
	int window_gph_hdl_ = 0;

};