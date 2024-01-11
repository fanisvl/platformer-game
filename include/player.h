#pragma once

#include "gameobject.h"
#include <sgg/graphics.h>
#include "box.h"
#include <utility>
#include "dynamic_object.h"

class Player : public Box, public GameObject
{
	// animated player
	std::vector<std::string> m_sprites;
	graphics::Brush m_brush_player;

	float m_init_x;
	float m_init_y;

	const float m_accel_horizontal = 20.0f;
	const float m_accel_vertical = 300.1f;
	const float m_max_velocity = 5.0f;
	const float m_gravity = 10.0f;
public:
	float m_vx = 0.0f;
	float m_vy = 0.0f;


public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	void setPosition(float x, float y);
	void setInitialPosition(float x, float y);
	void goToInitialPosition();
	void handleCollision(CollisionType type, float offset);
	std::pair<float, float> getPositionXY();
protected:
	void debugDraw();
	void movePlayer(float dt);
};
