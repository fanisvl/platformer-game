#include "danger_flatform.h"

void DangerPlatform::update(float dt) {
	if (isFalling()) {
		goDown();
	}

}

void DangerPlatform::init() {
	StaticObject::init();
}

void DangerPlatform::draw() {
	StaticObject::draw();
}

DangerPlatform::DangerPlatform(float x, float y, float w, float h, const std::string& assetName) : StaticObject(x, y, w, h, assetName) {}


void DangerPlatform::setFalling() {
	falling = true;

}

bool DangerPlatform::isFalling() {
	return falling;
}

void DangerPlatform::goDown() {
	m_pos_y -= 1.0f;
}

void DangerPlatform::handleCollision(CollisionType type) {
	switch (type)
	{
	case SIDEWAYS:
		break;
	case DOWNWARDS:
		isFalling();
		break;
	case UPWARDS:
		break;
	default:
		break;
	}
}