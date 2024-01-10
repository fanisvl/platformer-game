#include "enemy.h"
#include "player.h"
#include <utility>

void Enemy::init() {
	DynamicObject::init();	
}

void Enemy::update(float dt) {
	chasePlayer();
}

void Enemy::draw() {
	DynamicObject::draw();
}

#include <iostream>
void Enemy::handleCollision(CollisionType type) {
	if (!hidden) {
		switch (type) {
		case SIDEWAYS:
			// kill player
			std::cout << "kill player" << std::endl;
			m_state->playerDeath();
			break;
		case DOWNWARDS:
			// kill self
			hide();
			break;
		}
	}
}

void Enemy::chasePlayer() {
	// If the player is at the same horizontal level
	// The enemy will start moving towards the player's x position.
	std::pair<float, float> player_xy = { m_state->getPlayer()->getPositionXY() };
	float player_x = player_xy.first;
	float player_y = player_xy.second;

	if ((m_pos_y - 2.0f) < player_y) {
		if (m_pos_x < player_x) m_pos_x += 0.05f;
		if (m_pos_x > player_x) m_pos_x -= 0.05f;
	}
}	

Enemy::Enemy(float x, float y, float w, float h, const std::string& assetName) : DynamicObject(x, y, w, h, assetName) {}