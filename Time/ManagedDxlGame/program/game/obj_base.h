#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "fps_camera.h"

class ObjBase {
public:
	Shared<dxe::Mesh> mesh = nullptr;
	Shared<dxe::Texture> texture = nullptr;

	// オブジェクトの位置
	//tnl::Vector3 pos_;
	// 仮想関数
	virtual void update(float delta_time) {};
	virtual void draw(std::shared_ptr<FpsCamera>camera) {};
};