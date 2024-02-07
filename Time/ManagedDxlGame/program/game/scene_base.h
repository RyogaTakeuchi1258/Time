#pragma once

class SceneBase {
public:
	virtual void update(float delta_time) {};
	virtual void updateOptionScreen(float delta_time) {};
	virtual void draw() = 0;
	virtual void InputTab() {};

	// 描画用変数
	const int draw_p_x = 600;
	const int draw_p_y = 690;

	// ジャンプ用の変数
	float jump_vel = 15.0f;
	float grand = 50;

	// ゲームが下賜されたかどうかのフラグ
	bool isGameStarted_ = false;
	// オプション画面が表示されているかのどうかのフラグ
	bool isOptionScreenVisible_ = false;
};