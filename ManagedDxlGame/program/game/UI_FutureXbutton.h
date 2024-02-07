#pragma once
#include "UI_base.h"

class UI_FutureXbutton : public UIBase {
public:
	UI_FutureXbutton();
	~UI_FutureXbutton() override;
	void draw() override;
	bool update();
private:
	// 設定画面の文字
	const std::string setting_messege[4] = { "どの時間に行きますか？","現　在","過　去","やめる" };
	// 設定画面の背景
	int window_gph_hdl_ = 0;
};