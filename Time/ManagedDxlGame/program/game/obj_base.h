#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "fps_camera.h"

class ObjBase {
public:
	Shared<dxe::Mesh> mesh = nullptr;
	Shared<dxe::Texture> texture = nullptr;

	// �I�u�W�F�N�g�̈ʒu
	//tnl::Vector3 pos_;
	// ���z�֐�
	virtual void update(float delta_time) {};
	virtual void draw(std::shared_ptr<FpsCamera>camera) {};
};