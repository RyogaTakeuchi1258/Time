#pragma once

class SceneBase {
public:
	virtual void update(float delta_time) {};
	virtual void updateOptionScreen(float delta_time) {};
	virtual void draw() = 0;
	virtual void InputTab() {};

	// �`��p�ϐ�
	const int draw_p_x = 600;
	const int draw_p_y = 690;

	// �W�����v�p�̕ϐ�
	float jump_vel = 15.0f;
	float grand = 50;

	// �Q�[�����������ꂽ���ǂ����̃t���O
	bool isGameStarted_ = false;
	// �I�v�V������ʂ��\������Ă��邩�̂ǂ����̃t���O
	bool isOptionScreenVisible_ = false;
};