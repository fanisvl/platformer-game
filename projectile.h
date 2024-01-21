#pragma once
#include "projectile_enemy.h"
#include "dynamic_object.h"
class Projectile : public DynamicObject {



public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	void handleCollision(CollisionType type) override;
	void chasePlayer();
	Projectile(float x, float y, float w, float h, const std::string& assetName);
};