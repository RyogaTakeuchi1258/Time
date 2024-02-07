#pragma once
#include "scene_base.h"

class UIOption;

// �^�C�g���V�[��
class TitleScene :public SceneBase {
private:
	// �^�C�g����ʗp�ϐ�
	int title_gph_hdl_ = 0;
	std::string s;

	std::shared_ptr<UIOption> option_ = nullptr;

public:
	// �R���X�g���N�^
	TitleScene();
	// �f�X�g���N�^
	~TitleScene();

	void update(float delta_time) override;

    // �^�C�g���V�[���̕`��
    void draw()override;
	// ���N���b�N���ꂽ�ꍇ�̊֐�
	void handleMouseClick();

	// �I�v�V������ʕ\���p�̊֐�
    void updateOptionScreen(float delta_time) override;
};