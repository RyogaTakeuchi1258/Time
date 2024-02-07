#pragma once
#include "scene_base.h"
#include "UI_CurrentXbutton.h"

class FpsCamera;
class ObjBoxB;
class UIOption;
class CurrentWall;
class CorrugatedBoard;

class CurrentScene :public SceneBase {
private:
	// カメラ生成
	Shared<FpsCamera> camera_ = nullptr;
	// オブジェクトB生成
	Shared<ObjBoxB> box_b_ = nullptr;
	// 段ボールを生成
	Shared<CorrugatedBoard> c_board_ = nullptr;
	// 壁の生成
	Shared<CurrentWall> wall = nullptr;
	// オプション画面のUIを生成
	Shared<UIOption> option_ = nullptr;
	// Xボタンを押されたときのUIを生成
	Shared<UI_CurrentXbutton> button_ = nullptr;

	/*int tile_gph_x_;
	int tile_gph_y_;
	int wall_gph_;*/

public:
	CurrentScene(tnl::Vector3 pos,tnl::Vector3 obj_pos);

	void update(float delta_time) override;
	void draw()override;
	
	// TABキーを押された場合の処理
	void InputTab()override;
	// オプション画面を表示する関数
	void updateOptionScreen(float delta_time) override;


	// -------------------------------------------------------------
	// Xボタン押下時に画面を表示する関数
	void updateXbuttonScreen(float delta_time);

	void InputX();
	bool isXbuttonVisible_ = false;

};