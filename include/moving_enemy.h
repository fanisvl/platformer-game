#pragma once
#include "dynamic_object.h"
#include "animated_object.h"

class MovingEnemy : public DynamicObject , public AnimatedObject{

	float m_left_boundary;
	float m_right_boundary;

public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	void handleCollision(CollisionType type) override;
	void chasePlayer();
	bool withinRightBoundary();
	bool withinLeftBoundary();
	std::string MovingEnemy::to_string() const override;
	MovingEnemy(float x, float y, float w, float h, const std::string& assetName);
	MovingEnemy(float x, float y, float w, float h, const std::string& assetName, float left_boundary, float right_boundary);
};