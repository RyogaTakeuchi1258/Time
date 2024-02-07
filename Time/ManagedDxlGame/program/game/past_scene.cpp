#include "../dxlib_ext/dxlib_ext.h"
#include "gm_manager.h"
#include "fps_camera.h"
#include "obj_box.h"
#include "UI_option.h"
#include "current_floor.h"
#include "past_scene.h"
#include "future_scene.h"
#include "current_scene.h"
#include "trl_player_command.h"

PastScene::PastScene(tnl::Vector3& pos, tnl::Vector3& obj_pos) {
	camera_ = std::make_shared<FpsCamera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
	camera_->pos_ = pos;

	box_b_ = std::make_shared<ObjBoxB>();
	box_b_->mesh->pos_ = obj_pos;

	wall = std::make_shared<CurrentWall>();

	option_ = std::make_shared<UIOption>();
	button_ = std::make_shared<UI_PastXbutton>();
}

void PastScene::update(float delta_time) {
	SetFogEnable(true);
	SetFogColor(32, 32, 32);
	SetFogStartEnd(500.0f, 1500.0f);
	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
	SetBackgroundColor(32, 32, 32);

	if (camera_)camera_->update();
	if (box_b_)box_b_->update(delta_time);

	trl::PlayerJamp(jump_vel, camera_->pos_, grand);

	if (tnl::IsIntersectAABB(camera_->pos_, camera_->camera_size, box_b_->mesh->pos_, box_b_->box_size_B)) {
		//----------------------------------------------------------------------------------------------
		// AABB ���m�̍��W�␳
		// arg1.2.		A, B �̈ړ��O�̍��W
		// arg3.4.		A, B �̃T�C�Y
		// arg5.6.		A, B �̈ړ���̍��W ( ���̊֐��ɂ���ĕ␳��̍��W�ɍX�V )
		// arg7.8.9.	��, �c, �� �����̕␳�^�C�v
		// .......		[ PWRFL_A : A �� ���� ] [ PWRFL_B : B �� ���� ] [ BOTH : A �� B �͉������� ]
		// arg10..		�␳��� A �� B �̊Ԃɐ݂����� ( �f�t�H���g 1.0f )
		// ret....		��` A �� B �ɑ΂��Ăǂ̕����֕␳���ꂽ��
		tnl::eCorrResAABB n = tnl::CorrectPositionAABB(
			camera_->camera_before_pos_
			, box_b_->before_posB
			, camera_->camera_size
			, box_b_->box_size_B
			, camera_->pos_
			, box_b_->mesh->pos_
			, tnl::eCorrTypeAABB::PWRFL_A
			, tnl::eCorrTypeAABB::PWRFL_B
			, tnl::eCorrTypeAABB::PWRFL_A, 0.1f);

		// ��ɕ␳���ꂽ��W�����v�̓��Z�b�g
		if (tnl::eCorrResAABB::UP == n) jump_vel = 0;
	}

	draw();

	DrawGridGround(camera_, 50, 20);
	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);

	// -------------------------------------------------------------------------------------------
	// �L�[�o�C���h
	// -------------------------------------------------------------------------------------------

	// TAB���[�������ꂽ�ꍇ�̏���
	InputTab();
	if (isOptionScreenVisible_) {
		updateOptionScreen(delta_time);
	}
	// X�L�[�������ꂽ�ꍇ�̏���
	InputX();
	if (isXbuttonVisible_) {
		updateXbuttonScreen(delta_time);
	}
}

void PastScene::draw() {
	SetFontSize(30);
	DrawStringEx(10, 10, -1, "�ߋ��V�[��");
	box_b_->draw(std::shared_ptr<FpsCamera>(camera_));
	wall->draw(std::shared_ptr<FpsCamera>(camera_));
}

//--------------------------------------------------------------------------------------------
// TAB�L�[�̏���
// �I�v�V������ʕ\��
void PastScene::InputTab() {
	// �Q�[�������ɊJ�n����Ă����珈�����Ȃ�
	if (isGameStarted_ || isOptionScreenVisible_) {
		return;
	}

	// TAB�L�[�������ꂽ�ꍇ
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB)) {
		isOptionScreenVisible_ = true;
	}
}

void PastScene::updateOptionScreen(float delta_time) {
	if (!option_->update()) {
		isOptionScreenVisible_ = false;
	}
	option_->draw();
}

// ------------------------------------------------------------------------------------------
// X�L�[�̏���
void PastScene::InputX() {
	// �Q�[�������ɊJ�n����Ă����珈�����Ȃ�
	if (isGameStarted_ || isXbuttonVisible_) {
		return;
	}

	// TAB�L�[�������ꂽ�ꍇ
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X)) {
		isXbuttonVisible_ = true;
	}
}


void PastScene::updateXbuttonScreen(float delta_time) {
	button_->draw();
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		int mouseX = tnl::Input::GetMousePosition().x;
		int mouseY = tnl::Input::GetMousePosition().y;
		// �N���b�N���ꂽ�͈͂̔���
		if (mouseX >= draw_p_x && mouseX <= draw_p_y && mouseY >= draw_p_x && mouseY <= draw_p_x + 30) {
			GameManager::GetInstance()->changeScene(new FutureScene({ camera_->pos_ },{ box_b_->mesh->pos_ }));
		}
		if (mouseX >= draw_p_x && mouseX <= draw_p_y && mouseY >= draw_p_x + 30 && mouseY <= draw_p_y - 30) {
			GameManager::GetInstance()->changeScene(new CurrentScene({ camera_->pos_ },{ box_b_->mesh->pos_ }));
		}
		if (mouseX >= draw_p_x && mouseX <= draw_p_y && mouseY >= draw_p_y - 30 && mouseY <= draw_p_y) {
			isXbuttonVisible_ = false;
		}

	}
}