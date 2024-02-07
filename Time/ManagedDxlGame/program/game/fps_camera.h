#pragma once

class FpsCamera : public dxe::Camera
{
public:

	FpsCamera(int screen_w, int screen_h) : dxe::Camera(screen_w, screen_h) {}

	void update();

	inline tnl::Vector3 up() {
		up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, rot_);
		return up_;
	}
	inline tnl::Vector3 down() { return -up(); }

	inline tnl::Vector3 forward() override {
		target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot_);
		return tnl::Vector3::Normalize(target_ - pos_);
	}
	inline tnl::Vector3 back() override { return -forward(); }
	inline tnl::Vector3 left() override { return tnl::Vector3::Cross(forward(), up()); }
	inline tnl::Vector3 right() override { return tnl::Vector3::Cross(up(), forward()); }

	tnl::Quaternion rot_;

	// プレイヤーの移動前の場所の変数
	tnl::Vector3 camera_before_pos_;
	// プレイヤーサイズ用の変数
	tnl::Vector3 camera_size;
private:
	const float CAMERA_SIZE = 100;
};