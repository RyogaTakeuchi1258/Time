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

	// �A�b�v�f�[�g
	if (camera_)camera_->update();
	if (box_b_)box_b_->update(delta_time);
	if (wall)wall->update(delta_time);
	if (c_board_)c_board_->update(delta_time);

	// �{�b�N�X�Ƃ̓����蔻��
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
			, tnl::eCorrTypeAABB::PWRFL_B
			, tnl::eCorrTypeAABB::PWRFL_B
			, tnl::eCorrTypeAABB::PWRFL_B, 0.1f);

		// ��ɕ␳���ꂽ��W�����v�̓��Z�b�g
		if (tnl::eCorrResAABB::UP == n) jump_vel = 0;
	}
	
	trl::WallCllision(camera_->pos_);

	draw();
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

void CurrentScene::draw() {
	/*for (int x; x < 2; x++) {
		for (int y; y < 2; y++) {
			DrawRotaGraph3D(20, 0, 20, 0, 0, tile_gph_x_, true);
		}
	}*/
	SetFontSize(30);
	DrawStringEx(10, 10, -1, "���݃V�[��");
	box_b_->draw(std::shared_ptr<FpsCamera>(camera_));
	wall->draw(std::shared_ptr<FpsCamera>(camera_));
	c_board_->draw(std::shared_ptr<FpsCamera>(camera_));
	DrawGridGround(camera_, 50, 20);


	if (camera_->pos_.x >= box_b_->mesh->pos_.x - 100 && camera_->pos_.z >= box_b_->mesh->pos_.z - 100
		&& camera_->pos_.x <= box_b_->mesh->pos_.x + 100 && camera_->pos_.z <= box_b_->mesh->pos_.z + 100) {
		// �}�E�X�J�[�\���ƃI�u�W�F�N�g�̓����蔻��
        // �I�u�W�F�N�g�ɃJ�[�\�������������狭���\�������
		tnl::Vector3 ms = tnl::Input::GetMousePosition();                                                                                       // �}�E�X�|�W�V�����̎擾
		tnl::Vector3 ray_nml = tnl::Vector3::CreateScreenRay(ms.x, ms.y, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, camera_->view_, camera_->proj_);  // ��ʓ��̃}�E�X�J�[�\������^���I�Ȍ������o��
		// �J�[�\���ƃI�u�W�F�N�g�̓����蔻��
		if (tnl::IsIntersectRayAABB(
			camera_->pos_
			, ray_nml
			, tnl::ToMaxAABB(box_b_->mesh->pos_, { box_b_->box_size_B })   // �I�u�W�F�N�g�̍���̃|�X�ƃT�C�Y
			, tnl::ToMinAABB(box_b_->mesh->pos_, { box_b_->box_size_B }))) // �I�u�W�F�N�g�̉E���̃|�X�ƃT�C�Y
		{
			box_b_->mesh->setMtrlEmissive({ 1,1,1 });                      // �G�~�b�V�u�J���[�̕ύX�ɂ��A�����\��������
			if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
				DrawStringEx(0,0,-1,"OK");
		    }
		}
		else box_b_->mesh->setMtrlEmissive({ 0.4,0.4,0.4 });    // �J�[�\�������킹�Ă��Ȃ��ꍇ�́A���̃G�~�b�V�u�J���[�ɖ߂�
	}
	else box_b_->mesh->setMtrlEmissive({ 0.4,0.4,0.4 });    // �J�[�\�������킹�Ă��Ȃ��ꍇ�́A���̃G�~�b�V�u�J���[�ɖ߂�
}


//  -----------------------------------------------------------------------------------------
// TAB�L�[�̏���
// �I�v�V������ʕ\��
void CurrentScene::InputTab() {
	// �Q�[�������ɊJ�n����Ă����珈�����Ȃ�
	if (isGameStarted_ || isOptionScreenVisible_) {
		return;
	}

	// TAB�L�[�������ꂽ�ꍇ
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
// X�L�[�̏���
void CurrentScene::InputX() {
	// �Q�[�������ɊJ�n����Ă����珈�����Ȃ�
	if (isGameStarted_ || isXbuttonVisible_) {
		return;
	}

	// TAB�L�[�������ꂽ�ꍇ
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X)) {
		isXbuttonVisible_ = true;
	}
}

void CurrentScene::updateXbuttonScreen(float delta_time) {
	button_->draw();
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		int mouseX = tnl::Input::GetMousePosition().x;
		int mouseY = tnl::Input::GetMousePosition().y;
		// �N���b�N���ꂽ�͈͂̔���
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

