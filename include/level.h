#pragma once

#include "gameobject.h"
#include <vector>
#include <list>
#include <string>
#include <sgg/graphics.h>
#include "player.h"
#include "static_object.h"
#include "background.h"
#include "dynamic_object.h"


class Level : public GameObject
{
    Background* m_background = nullptr;
	std::vector<StaticObject*> m_static_objects;
	std::list<DynamicObject*> m_dynamic_objects;

	void checkCollisions();
public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	void LoadLevel(std::string filename);
	void resetLevel();
	Level();
	~Level() override;
};