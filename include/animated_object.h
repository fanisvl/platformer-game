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
};

class AnimatedObject : public GameObject {
protected:
	std::vector<std::string> m_sprites;
	std::vector<std::string> b_sprites;
	AnimationType current_animation = Right;
	graphics::Brush m_brush_object;
public:
	void draw(float pos_x,float pos_y,AnimationType current_animation);
	void init() override;
	void LoadAssets(std::string assetName,float fill_opacity,float outline_opacity);
	AnimatedObject();
};