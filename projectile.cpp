#include "projectile.h"
#include "player.h"
#include <iostream>

void Projectile::init() {
	DynamicObject::init();
}

void Projectile::update(float dt) {
	chasePlayer();
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

void Projectile::chasePlayer() {
	std::pair<float, float> player_xy = { GameObject::m_state->getPlayer()->getPositionXY() };
	float playerpos_x = player_xy.first;
	if (m_pos_x < playerpos_x) m_pos_x += 0.05f;
	if (m_pos_x > playerpos_x) m_pos_x -= 0.05f;
}

Projectile::Projectile(float x, float y, float w, float h, const std::string& assetName) : DynamicObject(x, y, w, h, assetName) {
	
}