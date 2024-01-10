#include "enemy.h"

void Enemy::init() {
	DynamicObject::init();
	
	// Fix collision box
}

void Enemy::update(float dt) {

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
			
			break;
		case DOWNWARDS:
			// kill self
			hide();
			break;
		}
	}

}

Enemy::Enemy(float x, float y, float w, float h, const std::string& assetName) : DynamicObject(x, y, w, h, assetName) {}