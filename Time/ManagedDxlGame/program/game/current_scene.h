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
	// �J��������
	Shared<FpsCamera> camera_ = nullptr;
	// �I�u�W�F�N�gB����
	Shared<ObjBoxB> box_b_ = nullptr;
	// �i�{�[���𐶐�
	Shared<CorrugatedBoard> c_board_ = nullptr;
	// �ǂ̐���
	Shared<CurrentWall> wall = nullptr;
	// �I�v�V������ʂ�UI�𐶐�
	Shared<UIOption> option_ = nullptr;
	// X�{�^���������ꂽ�Ƃ���UI�𐶐�
	Shared<UI_CurrentXbutton> button_ = nullptr;

	/*int tile_gph_x_;
	int tile_gph_y_;
	int wall_gph_;*/

public:
	CurrentScene(tnl::Vector3 pos,tnl::Vector3 obj_pos);

	void update(float delta_time) override;
	void draw()override;
	
	// TAB�L�[�������ꂽ�ꍇ�̏���
	void InputTab()override;
	// �I�v�V������ʂ�\������֐�
	void updateOptionScreen(float delta_time) override;


	// -------------------------------------------------------------
	// X�{�^���������ɉ�ʂ�\������֐�
	void updateXbuttonScreen(float delta_time);

	void InputX();
	bool isXbuttonVisible_ = false;

};