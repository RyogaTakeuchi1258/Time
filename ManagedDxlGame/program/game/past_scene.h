#pragma once
#include "scene_base.h"
#include "UI_PastXbutton.h"

class FpsCamera;
class ObjBoxB;
class UIOption;
class CurrentWall;

class PastScene :public SceneBase {
private:
	// �J��������
	Shared<FpsCamera> camera_ = nullptr;
	// �I�u�W�F�N�gB����
	Shared<ObjBoxB> box_b_ = nullptr;
	// �ǂ̐���
	Shared<CurrentWall> wall = nullptr;
	// �I�v�V������ʂ�UI�𐶐�
	Shared<UIOption> option_ = nullptr;
	// X�{�^���������ꂽ�Ƃ���UI�𐶐�
	Shared<UI_PastXbutton> button_ = nullptr;
public:
	PastScene(tnl::Vector3& pos, tnl::Vector3& obj_pos);

	void update(float delta_time) override;
	void draw()override;

	// TAB�L�[�������ꂽ�ꍇ�̏���
	void InputTab();
	// �I�v�V������ʂ�\������֐�
	void updateOptionScreen(float delta_time) override;

	void InputX();
	void updateXbuttonScreen(float delta_time);
	bool isXbuttonVisible_ = false;
};