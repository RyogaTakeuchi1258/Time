#pragma once
#include "UI_base.h"

class UI_PastXbutton : public UIBase {
public:
	UI_PastXbutton();
	~UI_PastXbutton() override;
	void draw() override;
private:
	// �ݒ��ʂ̕���
	const std::string setting_messege[4] = { "�ǂ̎��Ԃɍs���܂����H","���@��","���@��","��߂�" };
	// �ݒ��ʂ̔w�i
	int window_gph_hdl_ = 0;

};