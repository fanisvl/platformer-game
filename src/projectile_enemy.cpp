#include "projectile_enemy.h"
#include "player.h"
#include <utility>

void ProjectileEnemy::init() {
	DynamicObject::init();
}

void ProjectileEnemy::draw() {
	DynamicObject::draw();
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

}
void ProjectileEnemy::update(float dt) {
	createProjectile();
}

ProjectileEnemy::ProjectileEnemy(float x, float y, float w, float h, const std::string& assetName) : DynamicObject(x, y, w, h, assetName) {

	m_left_boundary = init_x;
	m_right_boundary = init_x;
}

ProjectileEnemy::ProjectileEnemy(float x, float y, float w, float h, const std::string& assetName, float left_boundary, float right_boundary) : DynamicObject(x, y, w, h, assetName) {

	m_left_boundary = left_boundary;
	m_right_boundary = right_boundary;
}