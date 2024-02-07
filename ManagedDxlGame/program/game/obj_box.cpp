#include "../dxlib_ext/dxlib_ext.h"
#include "obj_box.h"

ObjBoxB::ObjBoxB(){
	texture = dxe::Texture::CreateFromFile("graphics/test.jpg");
	mesh = dxe::Mesh::CreateCubeMV(BOX_SIZE);
	mesh->setTexture(texture);
	mesh->pos_ = { 0,0,0 };
}

void ObjBoxB::update(float delta_time) {
	before_posB = mesh->pos_;
}

void ObjBoxB::draw(std::shared_ptr<FpsCamera>camera) {
	mesh->render(camera);
}