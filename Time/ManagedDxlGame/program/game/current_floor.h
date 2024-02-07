#pragma once

class FpsCamera;

class CurrentWall {
public:
	CurrentWall();
	~CurrentWall();
	void update(float delta_time);
	void draw(std::shared_ptr<FpsCamera>camera);

	// ���b�V���v�[�����瓾����C���X�^���V���O���b�V��
	std::list<Shared<dxe::InstMesh>> inst_meshs;
	std::list<Shared<dxe::InstMesh>> inst_meshs2;
	std::list<Shared<dxe::InstMesh>> inst_meshs3;

	// �C���X�^���V���O���b�V���v�[��
	Shared<dxe::InstMeshPool> mesh_pool = nullptr;
	// �C���X�^���V���O���b�V���v�[��
	Shared<dxe::InstMeshPool> mesh_pool2 = nullptr;
	// �C���X�^���V���O���b�V���v�[��
	Shared<dxe::InstMeshPool> mesh_pool3 = nullptr;
	// �C���X�^���V���O���b�V���v�[��
	Shared<dxe::InstMeshPool> mesh_pool4 = nullptr;


	// �������ɂȂ郁�b�V��
	Shared<dxe::Mesh> origine_mesh = nullptr;

	//tnl::Vector3 before_mesh_pos;
	//tnl::Vector3 mesh_size = {MESH_SIZE,MESH_SIZE,MESH_SIZE};
private:

	const float MESH_SIZE = 50;
	//// �Ǘp�̕������ɂȂ郁�b�V��
	//Shared<dxe::Mesh> wall_mesh = nullptr;
	//// �Ǘp�̃O���[�v���b�V��
	//Shared<dxe::Mesh> wall_group_mesh = nullptr;
	//// ���p�̕������ɂȂ郁�b�V��
	//Shared<dxe::Mesh> floor_mesh = nullptr;
	//// ���p�̃O���[�v���b�V��
	//Shared<dxe::Mesh> floor_group_mesh = nullptr;

	//const float mesh_size = 0.1f;
};