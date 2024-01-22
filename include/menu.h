#pragma once
#include "gameobject.h"
#include "background.h"
#include "sgg/graphics.h"

class Menu : public GameObject {
	Background* m_background;
	graphics::Brush m_brush;
public:
	void init() override;
	void update(float dt) override;
	void draw() override;
	void showTextMenu();
};