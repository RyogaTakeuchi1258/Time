#include "../dxlib_ext/dxlib_ext.h"
#include "corrugatedboard.h"
//#include ""

CorrugatedBoard::CorrugatedBoard() {
	texture = dxe::Texture::CreateFromFile("graphics/Paper02.jpg");
	mesh = dxe::Mesh::CreateCubeMV(BOX_SIZE);
	mesh->setTexture(texture);
	mesh->pos_ = { 0,0,0 };
}

void CorrugatedBoard::update(float delta_time) {
	before_posB = mesh->pos_;

	
}

void CorrugatedBoard::draw(std::shared_ptr<FpsCamera>camera) {
	mesh->render(camera);
}