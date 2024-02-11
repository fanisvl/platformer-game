#pragma once
#include "dynamic_object.h"
#include "moving_enemy.h"
#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <ctime>
#include "animated_object.h"
#include <projectile.h>
class ProjectileEnemy : public DynamicObject , public AnimatedObject {
	std::chrono::time_point<std::chrono::system_clock> intervalResetTime;
	float attack_interval = 2.0f;
public:
	std::list<Projectile*> m_projectiles;
	bool secondsPassed(float seconds);
	void update(float dt) override;
	void createProjectile(float seconds);
	void newProjectileObject();
	void draw() override;
	void init()	override;
	void handleCollision(CollisionType type) override;
	void checkPlayerPos();
	void checkCollision();
	void checkProjectileBoundaries();
	ProjectileEnemy(float x, float y, float w, float h , const std::string& assetName);
	std::string ProjectileEnemy::to_string() const override;
};
