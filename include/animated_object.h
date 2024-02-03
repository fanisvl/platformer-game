#pragma once
#include "gameobject.h" 
#include <iostream>
#include <vector>
#include <list>
#include <sgg/graphics.h>
enum AnimationType {

	//enum used for each animation type
	Left, //move left animation
	Right, //move right animation
 	Jump, //jump animation
	IdleRight,//Idle right animation
	IdleLeft,//Idle left animation
};

class AnimatedObject : public GameObject {
protected:
	std::vector<std::string> walk;
	std::vector<std::string> idle;
	AnimationType current_animation = Right;
	graphics::Brush m_animation_brush;
public:
	void animate(float pos_x,float pos_y,AnimationType current_animation);
	void init() override;
	void animateWalk(std::vector<std::string> vector_name,float pos_x);
	void animateIdle(std::vector<std::string>& vector_name);
	void fillVector(std::vector<std::string>& vector, std::string asset_folder);
	void loadPlayerAssets();
	void loadMovingEnemyAssets();
	AnimatedObject();
};