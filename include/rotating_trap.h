#pragma once
#include "static_object.h"

class RotatingTrap : public StaticObject {

	float radius;
	float center_x;
	float center_y;
	float current_rotation_angle;
	float max_left_rotation_angle;
	float max_right_rotation_angle;
	float rotation_speed;

public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	void handleCollision(CollisionType type) override;
	RotatingTrap(float x, float y, float w, float h, const std::string& asset);
	std::string RotatingTrap::to_string() const override;
	void rotate(float angle);

};