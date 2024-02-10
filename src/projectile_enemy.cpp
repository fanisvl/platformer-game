#include "projectile_enemy.h"
#include "projectile.h"
#include "player.h"
#include <utility>
#include <thread>
#include <chrono>
#include <sstream>

void ProjectileEnemy::init() {
	AnimatedObject::loadProjectileEnemyAssets();
	AnimatedObject::init();
	current_animation = IdleRight;
}

void ProjectileEnemy::draw() {

	// Animate and draw Projectile Enemy
	AnimatedObject::animate(m_pos_x, m_pos_y, current_animation);
	graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_animation_brush);

	// Debug draw
	m_brush_debug.fill_opacity = 0.5f;
	if (GameObject::m_state->m_debugging) {
		graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_brush_debug);
	}

	// Call draw for projectiles
	for (auto& p_gob : m_projectiles)
		if (p_gob) p_gob->draw();
}
void ProjectileEnemy::checkCollision() {
	for (auto it = m_projectiles.begin(); it != m_projectiles.end(); ++it) {
		float offset = 0.0f;
		if (offset = GameObject::m_state->getPlayer()->intersectSideways(**it)) {
			(*it)->handleCollision(SIDEWAYS);
			delete* it;
			m_projectiles.erase(it);
			break;
		}
	}

	// Intersect Down
	for (auto it = m_projectiles.begin(); it != m_projectiles.end(); ++it) {
		float offset = 0.0f;
		if (offset = GameObject::m_state->getPlayer()->intersectDown(**it)) {
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

void ProjectileEnemy::update(float dt) {
	for (auto& p_gob : m_projectiles)
		if (p_gob) p_gob->update(dt);
	if (!hidden) {
		checkPlayerPos();
		checkCollision();
	}
	checkProjectileBoundaries();
}
void ProjectileEnemy::checkPlayerPos() {
	std::pair<float, float> player_xy = { GameObject::m_state->getPlayer()->getPositionXY() };
	float player_y = player_xy.second;

	// Vertical threshold allows the projectile to keep chasing the player even if they're jumping over them.
	float verticalThreshold = 1.0f;

	// If the player is at the same horizontal level, a projectile is created.
	if (player_y >= (m_pos_y - verticalThreshold) && player_y <= (m_pos_y + verticalThreshold)) {
		createProjectile(attack_interval);
	}
}

bool ProjectileEnemy::secondsPassed(float seconds) {
	// Checks the difference between the intervalResetTime and the currentTime
	auto currentTime = std::chrono::system_clock::now();
	auto seconds_passed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - intervalResetTime).count();
	return seconds_passed >= seconds;
}

void ProjectileEnemy::createProjectile(float seconds) {
	// Creates a projectile every x seconds
	if (secondsPassed(seconds)) {
		newProjectileObject();
	}
}

void ProjectileEnemy::newProjectileObject() {
	std::string projectile_asset_path = "projectileEnemy/projectileSprites/tile000.png";
	m_projectile = new Projectile(m_pos_x, m_pos_y, 0.55f, 0.55f, projectile_asset_path);
	m_projectile->init();
	m_projectiles.push_back(m_projectile);

	// Reset timer
	intervalResetTime = std::chrono::system_clock::now();

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

ProjectileEnemy::ProjectileEnemy(float x, float y, float w, float h, const std::string& assetName) : DynamicObject(x, y, w, h, assetName) {}

std::string ProjectileEnemy::to_string() const {
	std::ostringstream oss;
	oss << "\"ProjectileEnemy\"" << " " << m_pos_x << " " << m_pos_y << " " << m_width << " " << m_height << " " << m_asset_path;
	return oss.str();
}

