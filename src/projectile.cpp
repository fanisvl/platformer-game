#include "projectile.h"
#include "player.h"
#include <iostream>

void Projectile::init() {
	DynamicObject::init();
	std::pair<float, float> player_xy = { GameObject::m_state->getPlayer()->getPositionXY() };
	playerpos_x = player_xy.first;
	if (playerpos_x > m_pos_x) {
		is_right = true;
	}
	m_width /= 2.0f;
	m_height /= 2.0f;
}

void Projectile::update(float dt) {
	if (!is_right) {
		chasePlayerLeft();
	}
	else {
		chasePlayerRight();
	}
}

void Projectile::draw() {
	DynamicObject::draw();
}

void Projectile::handleCollision(CollisionType type) {
	switch (type) {
		case SIDEWAYS:
			m_state->playerDeath();
			break;
		case DOWNWARDS:
			m_state->playerDeath();
			break;
	}
}
float Projectile::getPosx() {
	return m_pos_x;
}
void Projectile::chasePlayerRight() {
	 m_pos_x += 0.05f;
}
void Projectile::chasePlayerLeft() {
	m_pos_x -= 0.05f;
}

Projectile::Projectile(float x, float y, float w, float h, const std::string& assetName) : DynamicObject(x, y, w, h, assetName) {
	
}