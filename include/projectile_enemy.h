#pragma once
#include "dynamic_object.h"
#include "moving_enemy.h"
#include <iostream>
#include <vector>
#include <list>
class ProjectileEnemy : public DynamicObject {

	float m_left_boundary;
	float m_right_boundary;
	int counter = 0;
public:
	std::list<Projectile*> m_projectiles;
	void update(float dt) override;
	void draw() override;
	void init()	override;
	void handleCollision(CollisionType type) override;
	void createProjectile();
	void checkPlayerpos();
	void checkcollision();
	ProjectileEnemy(float x, float y, float w, float h , const std::string& assetName);
	ProjectileEnemy(float x, float y, float w, float h, const std::string& assetName, float left_boundary, float right_boundary);
};
