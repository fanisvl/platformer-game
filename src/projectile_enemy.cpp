#include "projectile_enemy.h"
#include "projectile.h"
#include "player.h"
#include <utility>
#include <thread>
#include <chrono>

void ProjectileEnemy::init() {
	DynamicObject::init();
}

void ProjectileEnemy::draw() {
	DynamicObject::draw();
	for (auto& p_gob : m_projectiles)
		if (p_gob) p_gob->draw();
}
void ProjectileEnemy::checkcollision() {
	for (auto it = m_projectiles.begin(); it != m_projectiles.end(); ++it) {
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectSideways(**it)) {
			(*it)->handleCollision(SIDEWAYS);
			delete* it;
			m_projectiles.erase(it);
			break;
		}
	}

	// Intersect Down
	for (auto it = m_projectiles.begin(); it != m_projectiles.end(); ++it) {
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectDown(**it)) {
			(*it)->handleCollision(DOWNWARDS);
			delete* it;
			m_projectiles.erase(it);
			break;
		}
	}
}

void ProjectileEnemy::handleCollision(CollisionType type) {
	if (!hidden) {
		switch (type) {
		case SIDEWAYS:
			hide();
			break;
		case DOWNWARDS:
			hide();
			break;
		}
	}
}
void ProjectileEnemy::createProjectile() {
	m_projectile = new Projectile(m_pos_x, m_pos_y, 0.55f, 0.55f, "slime.png");
	m_projectile->init();
	m_projectiles.push_back(m_projectile);
}
void ProjectileEnemy::update(float dt) {
	for (auto& p_gob : m_projectiles)
		if (p_gob) p_gob->update(dt);
	checkPlayerpos();
	checkcollision();
}
void ProjectileEnemy::checkPlayerpos() {
	std::pair<float, float> player_xy = { m_state->getPlayer()->getPositionXY() };
	float player_x = player_xy.first;
	float player_y = player_xy.second;

	// Vertical threshold allows the enemy to keep chasing the player even if they're jumping over them.
	float verticalThreshold = 1.5f;

	// If the player is at the same horizontal level
	// The enemy will start moving towards the player's x position.
	if (player_y >= (m_pos_y - verticalThreshold) && player_y <= (m_pos_y + verticalThreshold)) {
		//delays the creation of projectiles to about every 3 seconds
		counter = counter + 1;
		if (counter != 1 && counter % 300 == 0) {
			std::cout << "Im in" << std::endl;
			createProjectile();
		}
		else if (counter == 1) {
			std::cout << "Im in" << std::endl;
			createProjectile();
		}
	}
}
ProjectileEnemy::ProjectileEnemy(float x, float y, float w, float h, const std::string& assetName) : DynamicObject(x, y, w, h, assetName) {
	
}

