#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "fps_camera.h"

void FpsCamera::update() {
	// 移動前のポジションにプレイヤーポジションを代入
	camera_before_pos_ = pos_;
	// プレイヤーサイズを固定
	camera_size = { CAMERA_SIZE, CAMERA_SIZE, CAMERA_SIZE };

	tnl::Input::RunIndexKeyDown(
		[&](uint32_t index) {
			tnl::Vector3 v[4] = {
				left(),
				right(),
				forward().xz(),
				back().xz()
			};
			pos_ += v[index] * 3.0f;

		}, eKeys::KB_A, eKeys::KB_D, eKeys::KB_W, eKeys::KB_S);

	tnl::Vector3 mvel = tnl::Input::GetMouseVelocity();
	rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(mvel.x * 0.1f));
	rot_ *= tnl::Quaternion::RotationAxis(right(), tnl::ToRadian(mvel.y * 0.1f));


	target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot_);
	up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, rot_);
	dxe::Camera::update();

}
