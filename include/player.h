#pragma once

#include "gameobject.h"
#include <sgg/graphics.h>
#include "box.h"
#include <utility>
#include "dynamic_object.h"
#include "animated_object.h"
#include "coin.h"

class Player : public Box, public GameObject , public AnimatedObject
{
	// Test next level logic
	int m_points;

	const float m_accel_horizontal = 50.0f;
	const float m_accel_vertical = 300.0f;
	const float m_max_velocity = 4.5f;
	const float m_gravity = 12.0f;
public: 
	float m_vx = 0.0f;
	float m_vy = 0.0f;

public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	void setPosition(float x, float y);
	void goToPosition(float x, float y) { m_pos_x = x; m_pos_y = y; }
	void handleCollision(CollisionType type, float offset);
	std::pair<float, float> getPositionXY();
	void gainPoint();
	int getPoints() { return m_points; }
	void resetPoints() { m_points = 0; }

protected:
	void debugDraw();
	void movePlayer(float dt);
};
