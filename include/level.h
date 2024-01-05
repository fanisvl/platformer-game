#pragma once

#include "gameobject.h"
#include <vector>
#include <list>
#include <string>
#include <graphics.h>
#include "player.h"
#include "block.h"
#include "background.h"

class Level : public GameObject
{
	graphics::Brush m_brush_background;
    Background* m_background = nullptr;
	std::vector<Block*> m_static_objects;
	std::list<GameObject*> m_dynamic_objects;

	void checkCollisions();
public:
	void update(float dt) override;
	void draw() override;
	void init() override;

	Level(const std::string & name = "Level0");
	~Level() override;
};