#pragma once

class FpsCamera;

class CurrentWall {
public:
	CurrentWall();
	~CurrentWall();
	void update(float delta_time);
	void draw(std::shared_ptr<FpsCamera>camera);

	// メッシュプールから得られるインスタンシングメッシュ
	std::list<Shared<dxe::InstMesh>> inst_meshs;
	std::list<Shared<dxe::InstMesh>> inst_meshs2;
	std::list<Shared<dxe::InstMesh>> inst_meshs3;

	// インスタンシングメッシュプール
	Shared<dxe::InstMeshPool> mesh_pool = nullptr;
	// インスタンシングメッシュプール
	Shared<dxe::InstMeshPool> mesh_pool2 = nullptr;
	// インスタンシングメッシュプール
	Shared<dxe::InstMeshPool> mesh_pool3 = nullptr;
	// インスタンシングメッシュプール
	Shared<dxe::InstMeshPool> mesh_pool4 = nullptr;


	// 複製元になるメッシュ
	Shared<dxe::Mesh> origine_mesh = nullptr;

	//tnl::Vector3 before_mesh_pos;
	//tnl::Vector3 mesh_size = {MESH_SIZE,MESH_SIZE,MESH_SIZE};
private:

	const float MESH_SIZE = 50;
	//// 壁用の複製元になるメッシュ
	//Shared<dxe::Mesh> wall_mesh = nullptr;
	//// 壁用のグループメッシュ
	//Shared<dxe::Mesh> wall_group_mesh = nullptr;
	//// 床用の複製元になるメッシュ
	//Shared<dxe::Mesh> floor_mesh = nullptr;
	//// 床用のグループメッシュ
	//Shared<dxe::Mesh> floor_group_mesh = nullptr;

	//const float mesh_size = 0.1f;
};