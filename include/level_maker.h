#pragma once
#include "gameobject.h"
#include "sgg/graphics.h"
#include "level.h"

class LevelMaker : public GameObject {
	graphics::MouseState mouse;
	graphics::Brush mouse_brush;
	Level* m_level = nullptr;
	float mouse_canvas_x;
	float mouse_canvas_y;

public:
	void update(float ms) override;
	void draw() override;
	void init() override;
	void createObject();
	LevelMaker();
	~LevelMaker();
};