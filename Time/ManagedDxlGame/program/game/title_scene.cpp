#include "../dxlib_ext/dxlib_ext.h"
#include "gm_manager.h"
#include "title_scene.h"
#include "current_scene.h"
#include "UI_option.h"

// �R���X�g���N�^
TitleScene::TitleScene() {
    // �^�C�g���p�摜�̓ǂݍ���
	title_gph_hdl_ = LoadGraph("graphics/titleclock.jpg");
    // �I�v�V������ʂ̍쐬
    option_ = std::make_shared<UIOption>();
}
// �f�X�g���N�^
TitleScene::~TitleScene() {
	DeleteGraph(title_gph_hdl_);  //  �摜�̃f���[�g�����s�i�f���[�g���Ȃ��ƃ��������Ƀf�[�^���c��j
}

// �^�C�g���V�[�����̏���
void TitleScene::update(float delta_time) {

    handleMouseClick();  // �}�E�X�N���b�N�̏�����ǉ�

    // �Q�[�����J�n����Ă��Ȃ��ꍇ�ɕ`��ƍX�V���s��
    if (!isGameStarted_) {
        draw();
    }

    if (isOptionScreenVisible_) {
        updateOptionScreen(delta_time);
    }
}


// �^�C�g���V�[���̕`��
void TitleScene::draw() {
	SetFontSize(100);
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 1.0f, 0, title_gph_hdl_, true);
    ChangeFont("../Font/Tropikal-Bold.otf");
	DrawStringEx(250, 200, -1, "CLOCK");
    //SetFontSize(40);
    //DrawStringEx(300, 400, -1, "�`�`���Ԃ𑀂�A�L�������߂��`�`");
	SetFontSize(30);
	DrawStringEx(570, 600, -1, "�Q�[���J�n\n�I�v�V����\n�Q�[���I��");
}


// ���N���b�N�̏���
void TitleScene::handleMouseClick() {
    // �Q�[�������ɊJ�n����Ă����珈�����Ȃ�
    if (isGameStarted_ || isOptionScreenVisible_) {
        return;
    }

    // �}�E�X�̍��{�^�����N���b�N���ꂽ�ꍇ
    if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
        int mouseX = tnl::Input::GetMousePosition().x;
        int mouseY = tnl::Input::GetMousePosition().y;

        // �Q�[���J�n�{�^���͈̔� (��: ���オ (570, 600), �E���� (720, 630))
        if (mouseX >= 570 && mouseX <= 720 && mouseY >= 600 && mouseY <= 630) {
            auto mgr = GameManager::GetInstance();
            mgr->changeScene(new CurrentScene({ 0,50,0 },{0,50,100}));
            isGameStarted_ = true;                                                // �Q�[���J�n
        }
        // �I�v�V�����{�^���͈̔� (��: ���オ (570, 630), �E���� (720, 660))
        if (mouseX >= 570 && mouseX <= 720 && mouseY >= 630 && mouseY <= 660) {
            isOptionScreenVisible_ = true;                                        // �I�v�V������ʕ\��
        }
        // �Q�[���I���{�^���͈̔� (��: ���オ (570, 660), �E���� (720, 690))
        if (mouseX >= 570 && mouseX <= 720 && mouseY >= 660 && mouseY <= 690) {
            exit(1);                                                              // �Q�[���I���iDX���C�u�����I���j
        }
    }
}

void TitleScene::updateOptionScreen(float delta_time) {
    if (!option_->update()) {
        isOptionScreenVisible_ = false;
    }
    option_->draw();
}
