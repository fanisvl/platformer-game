#pragma once
#include "dynamic_object.h"
#include "animated_object.h"

class Coin : public DynamicObject, public AnimatedObject
{
public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	void handleCollision(CollisionType type) override;
	Coin(float x, float y, float w, float h, const std::string& assetName);

};