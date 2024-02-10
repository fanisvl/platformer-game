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
	std::list<StaticObject*> m_static_objects;
	std::list<DynamicObject*> m_dynamic_objects;
	std::string m_level_path;
	float player_spawn_x;
	float player_spawn_y;

	void checkCollisions();
public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	void LoadLevel(std::string filename);
	void resetLevel();
	void setPlayerSpawn(float x, float y);
	Level();
	Level(std::string level_path);
	~Level();

	// Used by level maker
	std::list<StaticObject*>& getStaticObjects() {return m_static_objects;}
	std::list<DynamicObject*>& getDynamicObjects() {return m_dynamic_objects;}
	float getPlayerSpawnX() { return player_spawn_x; }
	float getPlayerSpawnY() { return player_spawn_y; }

};