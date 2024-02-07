#pragma once
#include "scene_base.h"
#include "UI_PastXbutton.h"

class FpsCamera;
class ObjBoxB;
class UIOption;
class CurrentWall;

class PastScene :public SceneBase {
private:
	// カメラ生成
	Shared<FpsCamera> camera_ = nullptr;
	// オブジェクトB生成
	Shared<ObjBoxB> box_b_ = nullptr;
	// 壁の生成
	Shared<CurrentWall> wall = nullptr;
	// オプション画面のUIを生成
	Shared<UIOption> option_ = nullptr;
	// Xボタンを押されたときのUIを生成
	Shared<UI_PastXbutton> button_ = nullptr;
public:
	PastScene(tnl::Vector3& pos, tnl::Vector3& obj_pos);

	void update(float delta_time) override;
	void draw()override;

	// TABキーを押された場合の処理
	void InputTab();
	// オプション画面を表示する関数
	void updateOptionScreen(float delta_time) override;

	void InputX();
	void updateXbuttonScreen(float delta_time);
	bool isXbuttonVisible_ = false;
};