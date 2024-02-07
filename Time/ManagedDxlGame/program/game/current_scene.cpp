#include "../dxlib_ext/dxlib_ext.h"
#include "gm_manager.h"
#include "fps_camera.h"
#include "obj_box.h"
#include "current_floor.h"
#include "corrugatedboard.h"
#include "UI_option.h"
#include "current_scene.h"
#include "future_scene.h"
#include "past_scene.h"
#include "trl_player_command.h"

CurrentScene::CurrentScene(tnl::Vector3 pos, tnl::Vector3 obj_pos) {
	camera_ = std::make_shared<FpsCamera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
	camera_->pos_ = pos;

	box_b_ = std::make_shared<ObjBoxB>();
	box_b_->mesh->pos_ = obj_pos;

	c_board_ = std::make_shared<CorrugatedBoard>();
	tnl::Vector3 c_pos = {100,0,0};
	c_board_->mesh->pos_ = c_pos;
	
	wall = std::make_shared<CurrentWall>();

	option_ = std::make_shared<UIOption>();
	button_ = std::make_shared<UI_CurrentXbutton>();

	//tile_gph_x_ = LoadGraph("graphics/tiles_x.jpg");
	//tile_gph_y_ = LoadGraph("graphics/tiles_y.jpg");
}

void CurrentScene::update(float delta_time) {
	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
	SetBackgroundColor(32, 32, 32);

	// アップデート
	if (camera_)camera_->update();
	if (box_b_)box_b_->update(delta_time);
	if (wall)wall->update(delta_time);
	if (c_board_)c_board_->update(delta_time);

	// ボックスとの当たり判定
	if (tnl::IsIntersectAABB(camera_->pos_, camera_->camera_size, box_b_->mesh->pos_, box_b_->box_size_B)) {
		//----------------------------------------------------------------------------------------------
		// AABB 同士の座標補正
		// arg1.2.		A, B の移動前の座標
		// arg3.4.		A, B のサイズ
		// arg5.6.		A, B の移動後の座標 ( この関数によって補正後の座標に更新 )
		// arg7.8.9.	横, 縦, 奥 方向の補正タイプ
		// .......		[ PWRFL_A : A が 強い ] [ PWRFL_B : B が 強い ] [ BOTH : A と B は押し合う ]
		// arg10..		補正後に A と B の間に設ける空間 ( デフォルト 1.0f )
		// ret....		矩形 A が B に対してどの方向へ補正されたか
		tnl::eCorrResAABB n = tnl::CorrectPositionAABB(
			camera_->camera_before_pos_
			, box_b_->before_posB
			, camera_->camera_size
			, box_b_->box_size_B
			, camera_->pos_
			, box_b_->mesh->pos_
			, tnl::eCorrTypeAABB::PWRFL_B
			, tnl::eCorrTypeAABB::PWRFL_B
			, tnl::eCorrTypeAABB::PWRFL_B, 0.1f);

		// 上に補正されたらジャンプ力リセット
		if (tnl::eCorrResAABB::UP == n) jump_vel = 0;
	}
	
	trl::WallCllision(camera_->pos_);

	draw();
	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);
	// -------------------------------------------------------------------------------------------
	// キーバインド
	// -------------------------------------------------------------------------------------------

	// TABきーを押された場合の処理
	InputTab();
	if (isOptionScreenVisible_) {
		updateOptionScreen(delta_time);
	}
	// Xキーを押された場合の処理
	InputX();
	if (isXbuttonVisible_) {
		updateXbuttonScreen(delta_time);
	}
}

void CurrentScene::draw() {
	/*for (int x; x < 2; x++) {
		for (int y; y < 2; y++) {
			DrawRotaGraph3D(20, 0, 20, 0, 0, tile_gph_x_, true);
		}
	}*/
	SetFontSize(30);
	DrawStringEx(10, 10, -1, "現在シーン");
	box_b_->draw(std::shared_ptr<FpsCamera>(camera_));
	wall->draw(std::shared_ptr<FpsCamera>(camera_));
	c_board_->draw(std::shared_ptr<FpsCamera>(camera_));
	DrawGridGround(camera_, 50, 20);


	if (camera_->pos_.x >= box_b_->mesh->pos_.x - 100 && camera_->pos_.z >= box_b_->mesh->pos_.z - 100
		&& camera_->pos_.x <= box_b_->mesh->pos_.x + 100 && camera_->pos_.z <= box_b_->mesh->pos_.z + 100) {
		// マウスカーソルとオブジェクトの当たり判定
        // オブジェクトにカーソルが当たったら強調表示される
		tnl::Vector3 ms = tnl::Input::GetMousePosition();                                                                                       // マウスポジションの取得
		tnl::Vector3 ray_nml = tnl::Vector3::CreateScreenRay(ms.x, ms.y, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, camera_->view_, camera_->proj_);  // 画面内のマウスカーソルから疑似的な光線を出す
		// カーソルとオブジェクトの当たり判定
		if (tnl::IsIntersectRayAABB(
			camera_->pos_
			, ray_nml
			, tnl::ToMaxAABB(box_b_->mesh->pos_, { box_b_->box_size_B })   // オブジェクトの左上のポスとサイズ
			, tnl::ToMinAABB(box_b_->mesh->pos_, { box_b_->box_size_B }))) // オブジェクトの右下のポスとサイズ
		{
			box_b_->mesh->setMtrlEmissive({ 1,1,1 });                      // エミッシブカラーの変更により、強調表示させる
			if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
				DrawStringEx(0,0,-1,"OK");
		    }
		}
		else box_b_->mesh->setMtrlEmissive({ 0.4,0.4,0.4 });    // カーソルを合わせていない場合は、元のエミッシブカラーに戻す
	}
	else box_b_->mesh->setMtrlEmissive({ 0.4,0.4,0.4 });    // カーソルを合わせていない場合は、元のエミッシブカラーに戻す
}


//  -----------------------------------------------------------------------------------------
// TABキーの処理
// オプション画面表示
void CurrentScene::InputTab() {
	// ゲームが既に開始されていたら処理しない
	if (isGameStarted_ || isOptionScreenVisible_) {
		return;
	}

	// TABキーが押された場合
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB)) {
		isOptionScreenVisible_ = true;
	}
}


void CurrentScene::updateOptionScreen(float delta_time) {
	if (!option_->update()) {
		isOptionScreenVisible_ = false;
	}
	option_->draw();
}

// ---------------------------------------------------------------------------------
// Xキーの処理
void CurrentScene::InputX() {
	// ゲームが既に開始されていたら処理しない
	if (isGameStarted_ || isXbuttonVisible_) {
		return;
	}

	// TABキーが押された場合
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X)) {
		isXbuttonVisible_ = true;
	}
}

void CurrentScene::updateXbuttonScreen(float delta_time) {
	button_->draw();
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		int mouseX = tnl::Input::GetMousePosition().x;
		int mouseY = tnl::Input::GetMousePosition().y;
		// クリックされた範囲の判定
		if (mouseX >= draw_p_x && mouseX <= draw_p_y && mouseY >= draw_p_x && mouseY <= draw_p_x + 30) {
			GameManager::GetInstance()->changeScene(new FutureScene({ camera_->pos_ },{ box_b_->mesh->pos_ }));
		}
		if (mouseX >= draw_p_x && mouseX <= draw_p_y && mouseY >= draw_p_x + 30 && mouseY <= draw_p_y - 30) {
			GameManager::GetInstance()->changeScene(new PastScene({ camera_->pos_ },{ box_b_->mesh->pos_ }));
		}
		if (mouseX >= draw_p_x && mouseX <= draw_p_y && mouseY >= draw_p_y - 30 && mouseY <= draw_p_y) {
			isXbuttonVisible_ = false;
		}
	}
	
}

