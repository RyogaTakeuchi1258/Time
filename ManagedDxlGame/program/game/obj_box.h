#pragma once
#include "obj_base.h"

class ObjBoxB :public ObjBase {
private:
	const float BOX_SIZE = 50;
	// オブジェクトのメッシュとテクスチャー
	
public:
	ObjBoxB();
	// ~ObjBoxB();
	void update(float delta_time) override;
	void draw(std::shared_ptr<FpsCamera>camera) override;
	tnl::Vector3 box_size_B = { BOX_SIZE, BOX_SIZE, BOX_SIZE };
	tnl::Vector3 before_posB;
};
