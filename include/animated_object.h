#pragma once
#include "gameobject.h" 
#include <iostream>
#include <vector>
#include <list>
#include <sgg/graphics.h>

enum AnimationType {
	WalkLeft,
	WalkRight, 
 	Jump,
	IdleRight,
	IdleLeft,
	Rotation,
};

class AnimatedObject : public GameObject {
protected:
	std::vector<std::string> walk;
	std::vector<std::string> idle;
	std::vector<std::string> m_rotation;
	AnimationType current_animation;
	graphics::Brush m_animation_brush;
	float timer;
	int frame_index;
public:
	void init() override;
	void animate(float pos_x, float pos_y, AnimationType current_animation);
	void animateAction(const std::vector<std::string>& vector, float pos_x);
	void animateIdle(const std::vector<std::string>& vector);
	void fillVector(std::vector<std::string>& vector, std::string asset_folder);
	void loadPlayerAssets();
	void loadMovingEnemyAssets();
	void loadCoinAssets();
	void loadProjectileEnemyAssets();
	AnimatedObject() {};
};