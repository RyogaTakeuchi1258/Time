#pragma once
#include "UI_base.h"

class UI_CurrentXbutton : public UIBase {
public:
	UI_CurrentXbutton();
	~UI_CurrentXbutton() override;
	void draw() override;
private:
	// �ݒ��ʂ̕���
	const std::string setting_messege[4] = { "�ǂ̎��Ԃɍs���܂����H","���@��","�߁@��","��߂�"};
	// �ݒ��ʂ̔w�i
	int window_gph_hdl_ = 0;
};