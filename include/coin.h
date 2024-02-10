#pragma once
#include "dynamic_object.h"
#include "animated_object.h"

class Coin : public DynamicObject, public AnimatedObject
{
protected:
	int check_loader = 0;
	float m_point = 1.0f; // each of coin give a point

public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	void handleCollision(CollisionType type) override;
	float getPoint();
	Coin(float x, float y, float w, float h, const std::string& assetName);

};