#pragma once
#include "projectile_enemy.h"
#include "dynamic_object.h"
class Projectile : public DynamicObject {


	bool is_right = false;
	float playerpos_x = 0.0f;
public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	void handleCollision(CollisionType type) override;
	void chasePlayerRight();
	void chasePlayerLeft();
	float getPosx();
	Projectile(float x, float y, float w, float h, const std::string& assetName);
};