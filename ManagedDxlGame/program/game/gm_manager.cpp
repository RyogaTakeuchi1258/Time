#include "../dxlib_ext/dxlib_ext.h"
#include "gm_manager.h"
#include "scene_base.h"

GameManager::GameManager(SceneBase* start_scene) : now_scene_(start_scene) {

}

// シングルトンのアドレスを取得
GameManager* GameManager::GetInstance(SceneBase* start_scene) {
	static GameManager* instance = nullptr;
	if (!instance) {
		instance = new GameManager(start_scene);
	}
	return instance;
}

//  ゲームマネージャー内の処理
void GameManager::update(float delta_time) {
	if (next_scene_) {
		delete now_scene_; 
		now_scene_ = next_scene_;
		next_scene_ = nullptr;
	}

	if (now_scene_) now_scene_->update(delta_time);
	//if (now_scene_) now_scene_->draw();
}

void GameManager::changeScene(SceneBase* next_scene, float trans_time) {
	next_scene_ = next_scene;

}