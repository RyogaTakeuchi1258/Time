#include "../dxlib_ext/dxlib_ext.h"
#include "gm_manager.h"
#include "title_scene.h"
#include "current_scene.h"
#include "UI_option.h"

// コンストラクタ
TitleScene::TitleScene() {
    // タイトル用画像の読み込み
	title_gph_hdl_ = LoadGraph("graphics/titleclock.jpg");
    // オプション画面の作成
    option_ = std::make_shared<UIOption>();
}
// デストラクタ
TitleScene::~TitleScene() {
	DeleteGraph(title_gph_hdl_);  //  画像のデリートを実行（デリートしないとメモリ内にデータが残る）
}

// タイトルシーン内の処理
void TitleScene::update(float delta_time) {

    handleMouseClick();  // マウスクリックの処理を追加

    // ゲームが開始されていない場合に描画と更新を行う
    if (!isGameStarted_) {
        draw();
    }

    if (isOptionScreenVisible_) {
        updateOptionScreen(delta_time);
    }
}


// タイトルシーンの描画
void TitleScene::draw() {
	SetFontSize(100);
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 1.0f, 0, title_gph_hdl_, true);
    ChangeFont("../Font/Tropikal-Bold.otf");
	DrawStringEx(250, 200, -1, "CLOCK");
    //SetFontSize(40);
    //DrawStringEx(300, 400, -1, "～～時間を操り、記憶を取り戻せ～～");
	SetFontSize(30);
	DrawStringEx(570, 600, -1, "ゲーム開始\nオプション\nゲーム終了");
}


// 左クリックの処理
void TitleScene::handleMouseClick() {
    // ゲームが既に開始されていたら処理しない
    if (isGameStarted_ || isOptionScreenVisible_) {
        return;
    }

    // マウスの左ボタンがクリックされた場合
    if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
        int mouseX = tnl::Input::GetMousePosition().x;
        int mouseY = tnl::Input::GetMousePosition().y;

        // ゲーム開始ボタンの範囲 (例: 左上が (570, 600), 右下が (720, 630))
        if (mouseX >= 570 && mouseX <= 720 && mouseY >= 600 && mouseY <= 630) {
            auto mgr = GameManager::GetInstance();
            mgr->changeScene(new CurrentScene({ 0,50,0 },{0,50,100}));
            isGameStarted_ = true;                                                // ゲーム開始
        }
        // オプションボタンの範囲 (例: 左上が (570, 630), 右下が (720, 660))
        if (mouseX >= 570 && mouseX <= 720 && mouseY >= 630 && mouseY <= 660) {
            isOptionScreenVisible_ = true;                                        // オプション画面表示
        }
        // ゲーム終了ボタンの範囲 (例: 左上が (570, 660), 右下が (720, 690))
        if (mouseX >= 570 && mouseX <= 720 && mouseY >= 660 && mouseY <= 690) {
            exit(1);                                                              // ゲーム終了（DXライブラリ終了）
        }
    }
}

void TitleScene::updateOptionScreen(float delta_time) {
    if (!option_->update()) {
        isOptionScreenVisible_ = false;
    }
    option_->draw();
}
