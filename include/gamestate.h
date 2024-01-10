#pragma once
#include "config.h"
#include <string>

class GameState
{
private:
	static GameState* m_unique_instance;

	class Level * m_current_level = nullptr;
	class Player* m_player = nullptr;
	
	GameState();

public:
	float m_global_offset_x = 0.0f;
	float m_global_offset_y = 0.0f;
	
	bool m_debugging = false;

public:
	~GameState();
	static GameState* getInstance();

	bool init();
	void draw();
	void update(float dt);

	std::string getFullAssetPath(const std::string& asset);
	std::string getAssetDir();
	class Player* getPlayer() { return m_player; }
	void playerDeath();
};
