#pragma once
#include "UI_base.h"

class UI_FutureXbutton : public UIBase {
public:
	UI_FutureXbutton();
	~UI_FutureXbutton() override;
	void draw() override;
	bool update();
private:
	// �ݒ��ʂ̕���
	const std::string setting_messege[4] = { "�ǂ̎��Ԃɍs���܂����H","���@��","�߁@��","��߂�" };
	// �ݒ��ʂ̔w�i
	int window_gph_hdl_ = 0;
};