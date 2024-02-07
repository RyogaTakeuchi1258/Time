#pragma once
#include "scene_base.h"

class UIOption;

// タイトルシーン
class TitleScene :public SceneBase {
private:
	// タイトル画面用変数
	int title_gph_hdl_ = 0;
	std::string s;

	std::shared_ptr<UIOption> option_ = nullptr;

public:
	// コンストラクタ
	TitleScene();
	// デストラクタ
	~TitleScene();

	void update(float delta_time) override;

    // タイトルシーンの描画
    void draw()override;
	// 左クリックされた場合の関数
	void handleMouseClick();

	// オプション画面表示用の関数
    void updateOptionScreen(float delta_time) override;
};