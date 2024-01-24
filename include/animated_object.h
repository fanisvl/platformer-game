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
	std::vector<std::string> walk_right;
	std::vector<std::string> walk_left;
	std::vector<std::string> idle_right;
	std::vector<std::string> idle_left;
	AnimationType current_animation = Right;
	graphics::Brush m_brush_object;
public:
	void draw(float pos_x,float pos_y,AnimationType current_animation);
	void init() override;
	void animate(std::vector<std::string> vector_name,float pos_x);
	void animateIdle(std::vector<std::string>& vector_name);
	void FillVector(std::vector<std::string>& vector, std::string asset);
	void LoadAssets(std::string assetName,float fill_opacity,float outline_opacity);
	AnimatedObject();
};