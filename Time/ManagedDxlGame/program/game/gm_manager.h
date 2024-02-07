#pragma once
#include"../library/tnl_sequence.h"

class SceneBase;

//  ゲームマネージャークラス
class GameManager {
public:
	static GameManager* GetInstance(SceneBase* start_scene = nullptr);

	void changeScene(SceneBase* next_scene, float trans_time = 0.5f);
	void update(float delta_time);

private:
	GameManager(SceneBase* start_scene);
	SceneBase* now_scene_ = nullptr;
	SceneBase* next_scene_ = nullptr;
	int tansition_graph_hdl_ = 0;
};