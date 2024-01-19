#pragma once
#include "gameobject.h"
#include "sgg/graphics.h"

class LevelMaker : public GameObject {
	graphics::MouseState mouse;
	graphics::Brush mouse_brush;
	float mouse_canvas_x;
	float mouse_canvas_y;

public:
	void update(float ms) override;
	void draw() override;
	void init() override;
	LevelMaker() {};
};