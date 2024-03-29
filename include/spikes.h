#pragma once
#include "static_object.h"

class Spikes : public StaticObject {
public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	void handleCollision(CollisionType type) override;
	Spikes(float x, float y, float w, float h, const std::string& asset);
	std::string Spikes::to_string() const override;

};