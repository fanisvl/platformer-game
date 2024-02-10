#include "coin.h"
#include "player.h"

void Coin::init() {
	// η μεθοδος καλειται συνεχως 
	AnimatedObject:init();
	


}

void Coin::update(float dt) {

}

void Coin::draw() {
	AnimatedObject::animate(m_pos_x, m_pos_y, Rotation);
	graphics::drawRect(m_pos_x, m_pos_y, 2.0f, 2.0f, m_animation_brush);
}

void Coin::handleCollision(CollisionType type) {
	if (!hidden) {
		switch (type) {
		case SIDEWAYS:
			// hide coin
			hide();
			break;
		case DOWNWARDS:
			// hide coin
			hide();
			break;
		}
	}
}

float Coin::getPoint() { return m_point; }

Coin::Coin(float x, float y, float w, float h, const std::string& assetName) : DynamicObject(x, y, w, h, assetName) {};