#pragma once
#include "UI_base.h"

// �I�v�V������ʃN���X
class UIOption : public UIBase {
public:
	UIOption();
	~UIOption() override;
	void draw() override;
	bool update();

private:
	// �ݒ��ʂ̕���
	const std::string setting_messege[5] = { "�ݒ���","����","���邳","�Z�[�u������","�Q�[���ɖ߂�" };
	// �ݒ��ʂ̔w�i
	int window_gph_hdl_ = 0;
	// �ݒ��ʂ̒����p�Q�[�W
	int bar_gph_hdl_ = 0;
	// �ݒ��ʂ̒����p�A�C�R��
	int cursor_gph_hdl_ = 0;
};