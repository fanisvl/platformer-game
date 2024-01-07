#pragma once
#include "gameobject.h"
#include "box.h"

class Enemy : public GameObject, public Box {
	
	std::string asset_path;
	const float m_vx = 5.0f;
public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	Enemy(std::string name) : GameObject(name) {}
};