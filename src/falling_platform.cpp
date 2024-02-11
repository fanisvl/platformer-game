#include "falling_flatform.h"
#include <sstream>
#include <iostream>
void FallingPlatform::update(float dt) {
	if (isFalling()) {
		goDown();
	}
	checkHide();
		
}

void FallingPlatform::init() {
	DynamicObject::init();
	setFalling(false);
}

void FallingPlatform::draw() {
	DynamicObject::draw();
	
}

FallingPlatform::FallingPlatform(float x, float y, float w, float h, const std::string& assetName) : DynamicObject(x, y, w, h, assetName) {}

void FallingPlatform::reset() {
	DynamicObject::reset();
	setFalling(false);
}

void FallingPlatform::setFalling(bool b) {
	falling = b;

}

bool FallingPlatform::isFalling() {
	return falling;
}

void FallingPlatform::goDown() {
	m_pos_y += 0.02f;
}


void FallingPlatform::handleCollision(CollisionType type) {
	switch (type)
	{
	case SIDEWAYS:
		break;
	case DOWNWARDS:
		std::cout << "fall" << std::endl;
		setFalling(true);
		break;
	case UPWARDS:
		break;
	default:
		break;
	}
}

std::string FallingPlatform::to_string() const
{
	std::ostringstream oss;
	oss << "\"FallingPlatform\"" << " " << m_pos_x << " " << m_pos_y << " " << m_width << " " << m_height << " " << m_asset_path;
	return oss.str();
}

void FallingPlatform::checkHide() {
	if (m_pos_y == 7.0f){
		hide();
	}
}