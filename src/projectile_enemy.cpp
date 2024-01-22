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
	if (!hidden) {
		checkPlayerpos();
		checkcollision();
	}
	checkProjectileBoundaries();
}
void ProjectileEnemy::checkPlayerpos() {
	std::pair<float, float> player_xy = { m_state->getPlayer()->getPositionXY() };
	float player_y = player_xy.second;

	// Vertical threshold allows the enemy to keep chasing the player even if they're jumping over them.
	float verticalThreshold = 1.0f;

	// If the player is at the same horizontal level
	// The enemy will start moving towards the player's x position.
	if (player_y >= (m_pos_y - verticalThreshold) && player_y <= (m_pos_y + verticalThreshold)) {
		//calls a function that checks if 3 seconds have passed since last projectiles creation
		createProjectileEveryThreeSeconds();
	}
}
void ProjectileEnemy::startTimer() {
	startTime = std::chrono::system_clock::now();
}
bool ProjectileEnemy::threeSecondsPassed() {

	// Checks the difference between the start time and the current time and converts it to seconds

	auto currentTime = std::chrono::system_clock::now();
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
	return seconds >= 3;
}

void ProjectileEnemy::createProjectileEveryThreeSeconds() {
	//checks if 3 seconds have passed since last projectiles creation
	if (!threeSecondsPassed()) {
		return;
	}

	// creates a new one if three seconds have passed
	createProjectile();
	startTimer();
}

void ProjectileEnemy::checkProjectileBoundaries() {
	for (auto it = m_projectiles.begin(); it != m_projectiles.end(); ++it) {
		if ((*it)->getPosx() < 0.5f || (*it)->getPosx() > 16.0f) {
			delete* it;
			m_projectiles.erase(it);
			break;
		}
	}	
}
ProjectileEnemy::ProjectileEnemy(float x, float y, float w, float h, const std::string& assetName) : DynamicObject(x, y, w, h, assetName) {
	
}

