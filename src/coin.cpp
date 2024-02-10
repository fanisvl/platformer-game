#include "coin.h"
#include "player.h"
#include "animated_object.h"
#include <sstream>

void Coin::init() {
	AnimatedObject::loadCoinAssets();
	AnimatedObject::init();

}

void Coin::update(float dt) {

}

void Coin::draw() {
	if (!hidden) {
		AnimatedObject::animate(m_pos_x, m_pos_y, Rotation);
		graphics::drawRect(m_pos_x, m_pos_y, 0.5f, 0.5f, m_animation_brush);
	}
}

void Coin::handleCollision(CollisionType type) {
	if (!hidden) {
		switch (type) {
		case SIDEWAYS:
		case DOWNWARDS:
			hide();
			GameObject::m_state->getPlayer()->gainPoint();
			std::cout << "Points: " << GameObject::m_state->getPlayer()->getPoints() << std::endl;
			break;
		}
	}
}

std::string Coin::to_string() const {
	std::ostringstream oss;
	oss << "\"Coin\"" << " " << m_pos_x << " " << m_pos_y << " " << m_width << " " << m_height << " " << m_asset_path;
	return oss.str();
}

Coin::Coin(float x, float y, float w, float h, const std::string& assetName) : DynamicObject(x, y, w, h, assetName) {};