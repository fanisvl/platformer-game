#pragma once
#include "dynamic_object.h"

class Enemy : public DynamicObject {
public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	void handleCollision(CollisionType type) override;
	Enemy(float x, float y, float w, float h, const std::string& assetName);
};