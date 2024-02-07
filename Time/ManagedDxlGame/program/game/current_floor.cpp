#include "../dxlib_ext/dxlib_ext.h"
#include "current_floor.h"
#include "fps_camera.h"

CurrentWall::CurrentWall() {

    SetLightDirection(VGet(0,-1, 1));
//    origine_mesh = dxe::Mesh::CreateFromFileMV("mesh/x_file/plane/temp.x");
    origine_mesh = dxe::Mesh::CreatePlaneMV({MESH_SIZE, MESH_SIZE, 0});
    std::vector<Shared<dxe::Texture>> textures;
    textures.emplace_back(dxe::Texture::CreateFromFile("graphics/1437947.jpg"));
    mesh_pool = dxe::InstMeshPool::Create(origine_mesh, 120, &textures);
    mesh_pool->setMtrlSpecular({ 0, 0, 0 });
    mesh_pool2 = dxe::InstMeshPool::Create(origine_mesh, 120, &textures);
    mesh_pool2->setMtrlSpecular({ 0, 0, 0 });
    // インスタンシングプールから個別のメッシュを取得
    for (int i = 0; i < 2; i++) {
        if (i == 1) {
            for (int z = 0; z < mesh_pool->getMaxInstanceNum() / 6; ++z) {
                for (int y = 0; y < 3; y++) {
                    auto inst = mesh_pool->CreateInstMesh();
                    inst->setPosition({ float(i * 500), float(y * 50) + 25 , float(z * 50) - 475 });
                    inst->setRotation(tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(90)));
                    // 使用するテクスチャ番号を設定
                    // MeshPool の Create 関数に渡されたテクスチャ配列番号で指定します
                    inst->setUseTextureIndex(z % textures.size());
                    inst_meshs.emplace_back(inst);
                }
            }
        }
        else {
            for (int z = 0; z < mesh_pool->getMaxInstanceNum() / 6; ++z) {
                for (int y = 0; y < 3; y++) {
                    auto inst = mesh_pool->CreateInstMesh();
                    inst->setPosition({ -500, float(y * 50) + 25 , float(z * 50) - 475 });
                    inst->setRotation(tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(270)));
                    // 使用するテクスチャ番号を設定
                    // MeshPool の Create 関数に渡されたテクスチャ配列番号で指定します
                    inst->setUseTextureIndex(z % textures.size());
                    inst_meshs.emplace_back(inst);
                }
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        if (i == 1) {
            for (int z = 0; z < mesh_pool2->getMaxInstanceNum() / 6; ++z) {
                for (int y = 0; y < 3; y++) {
                    auto inst = mesh_pool2->CreateInstMesh();
                    inst->setPosition({ float(z * 50) - 475, float(y * 50) + 25 ,float(i * 500) });
                    //inst->setRotation(tnl::Quaternion::RotationAxis({ 0, 0, 0 }, tnl::ToRadian(90)));
                    // 使用するテクスチャ番号を設定
                    // MeshPool の Create 関数に渡されたテクスチャ配列番号で指定します
                    inst->setUseTextureIndex(z % textures.size());
                    inst_meshs2.emplace_back(inst);
                }
            }
        }
        else {
            for (int z = 0; z < mesh_pool2->getMaxInstanceNum() / 6; ++z) {
                for (int y = 0; y < 3; y++) {
                    auto inst = mesh_pool2->CreateInstMesh();
                    inst->setPosition({ float(z * 50) - 475, float(y * 50) + 25 , -500 });
                    inst->setRotation(tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(180)));
                    // 使用するテクスチャ番号を設定
                    // MeshPool の Create 関数に渡されたテクスチャ配列番号で指定します
                    inst->setUseTextureIndex(z % textures.size());
                    inst_meshs2.emplace_back(inst);
                }
            }
        }
    }

    //origine_mesh3 = dxe::Mesh::CreatePlaneMV({ 50, 50, 0 });
    //origine_mesh4 = dxe::Mesh::CreatePlaneMV({ 50, 50, 0 });
    std::vector<Shared<dxe::Texture>> textures2;
    textures2.emplace_back(dxe::Texture::CreateFromFile("graphics/tiles_x.jpg"));
    std::vector<Shared<dxe::Texture>> textures3;
    textures3.emplace_back(dxe::Texture::CreateFromFile("graphics/canvas-background-sozai5.png"));
    //textures2.emplace_back(dxe::Texture::CreateFromFile("graphics/tiles_y.jpg"));
    mesh_pool3 = dxe::InstMeshPool::Create(origine_mesh, 400, &textures2);
    mesh_pool3->setMtrlSpecular({ 0, 0, 0 });
    mesh_pool4 = dxe::InstMeshPool::Create(origine_mesh, 400, &textures3);
    mesh_pool4->setMtrlSpecular({ 0, 0, 0 });
    for (int i = 0; i < 2; i++) {
        if (i == 0) {
            for (int x = 0; x < mesh_pool3->getMaxInstanceNum() / 20; ++x) {
                for (int z = 0; z < mesh_pool3->getMaxInstanceNum() / 20; z++) {
                    auto inst = mesh_pool3->CreateInstMesh();
                    inst->setPosition({ float(x * 50) - 475, 0 , float(z * 50) - 475 });
                    //inst->setRotation(tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90)));
                    // 使用するテクスチャ番号を設定
                    // MeshPool の Create 関数に渡されたテクスチャ配列番号で指定します
                    inst->setRotation(tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90)));
                    inst->setUseTextureIndex(x % textures2.size());
                    inst_meshs3.emplace_back(inst);
                }
            }
        }
        else{
            for (int x = 0; x < mesh_pool4->getMaxInstanceNum() / 20; ++x) {
                for (int z = 0; z < mesh_pool4->getMaxInstanceNum() / 20; z++) {
                    auto inst = mesh_pool4->CreateInstMesh();
                    inst->setPosition({ float(x * 50) - 475, 150 , float(z * 50) - 475 });
                    //inst->setRotation(tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90)));
                    // 使用するテクスチャ番号を設定
                    // MeshPool の Create 関数に渡されたテクスチャ配列番号で指定します
                    inst->setRotation(tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90)));
                    inst->setUseTextureIndex(x % textures3.size());
                    inst_meshs3.emplace_back(inst);
                }
            }
        }
        
    }
    
}

CurrentWall::~CurrentWall() {
    mesh_pool.reset();
    mesh_pool2.reset();
    mesh_pool3.reset();
    mesh_pool4.reset();
}

void CurrentWall::update(float delta_time) {
    //before_mesh_pos = origine_mesh->pos_;
}

void CurrentWall::draw(std::shared_ptr<FpsCamera>camera) {
    /*wall_group_mesh->render(camera);
    floor_group_mesh->render(camera);*/
    // インスタンシングプールの描画( DirectXRenderBegin, DirectXRenderEnd で囲う )
    dxe::DirectXRenderBegin();

    mesh_pool->render(camera);
    mesh_pool2->render(camera);
    mesh_pool3->render(camera);
    mesh_pool4->render(camera);

    dxe::DirectXRenderEnd();
}