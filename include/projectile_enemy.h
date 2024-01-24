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
	std::chrono::time_point<std::chrono::system_clock> startTime;
public:
	std::list<Projectile*> m_projectiles;
	void startTimer();
	bool threeSecondsPassed();
	void update(float dt) override;
	void createProjectileEveryThreeSeconds();
	void draw() override;
	void init()	override;
	void handleCollision(CollisionType type) override;
	void createProjectile();
	void checkPlayerpos();
	void checkcollision();
	void checkProjectileBoundaries();
	ProjectileEnemy(float x, float y, float w, float h , const std::string& assetName);
	std::string ProjectileEnemy::to_string() const override;
};
