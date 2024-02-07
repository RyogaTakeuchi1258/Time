#pragma once
#include "UI_base.h"

// オプション画面クラス
class UIOption : public UIBase {
public:
	UIOption();
	~UIOption() override;
	void draw() override;
	bool update();

private:
	// 設定画面の文字
	const std::string setting_messege[5] = { "設定画面","音量","明るさ","セーブをする","ゲームに戻る" };
	// 設定画面の背景
	int window_gph_hdl_ = 0;
	// 設定画面の調整用ゲージ
	int bar_gph_hdl_ = 0;
	// 設定画面の調整用アイコン
	int cursor_gph_hdl_ = 0;
};