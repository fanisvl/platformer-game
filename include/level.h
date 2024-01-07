#pragma once

#include "gameobject.h"
#include <vector>
#include <list>
#include <string>
#include <sgg/graphics.h>
#include "player.h"
#include "static_block.h"
#include "background.h"

class Level : public GameObject
{
    Background* m_background = nullptr;
	std::vector<StaticBlock*> m_static_objects;
	std::list<GameObject*> m_dynamic_objects;

	void checkCollisions();
public:
	void update(float dt) override;
	void draw() override;
	void init() override;

	Level();
	~Level() override;
};