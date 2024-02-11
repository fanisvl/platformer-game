#include "danger_flatform.h"
#include <sstream>

void DangerPlatform::update(float dt) {
	
		
}

void DangerPlatform::init() {
	StaticObject::init();
}

void DangerPlatform::draw() {
	StaticObject::draw();
	if (isFalling()) {
		goDown();
	}
}

DangerPlatform::DangerPlatform(float x, float y, float w, float h, const std::string& assetName) : StaticObject(x, y, w, h, assetName) {}


void DangerPlatform::setFalling() {
	falling = true;

}

bool DangerPlatform::isFalling() {
	return falling;
}

void DangerPlatform::goDown() {
	m_pos_y += 0.02f;
}

#include <iostream>
void DangerPlatform::handleCollision(CollisionType type) {
	switch (type)
	{
	case SIDEWAYS:
		break;
	case DOWNWARDS:
		std::cout << "fall" << std::endl;
		setFalling();
		break;
	case UPWARDS:
		break;
	default:
		break;
	}
}

std::string DangerPlatform::to_string() const
{
	std::ostringstream oss;
	oss << "\"DangerPlatform\"" << " " << m_pos_x << " " << m_pos_y << " " << m_width << " " << m_height << " " << m_asset_path;
	return oss.str();
}