#include "gamestate.h"
#include "level.h"
#include "player.h"
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

GameState::GameState()
{
}

GameState::~GameState()
{
	if (m_current_level)
		delete m_current_level;
	if (m_player)
		delete m_player;
}

GameState* GameState::getInstance()
{
	if (!m_unique_instance)
	{
		m_unique_instance = new GameState();
	}
	return m_unique_instance;
}

bool GameState::init()
{
	m_current_level = new Level();
	m_player = new Player();
	m_current_level->init();
	m_player->init();

	graphics::preloadBitmaps(getAssetDir());
	graphics::setFont(getFullAssetPath("OpenSans-Regular.ttf"));

	return true;
}

void GameState::draw()
{
	if (!m_current_level)
		return;

	// Draw Level
	m_current_level->draw();

	// Draw Player
	if (m_player->isActive()) m_player->draw();
	
	
}

void GameState::update(float dt)
{
	// Skip an update if a long delay is detected 
	// to avoid messing up the collision simulation
	if (dt > 500) // ms
		return;
	
	// Avoid too quick updates
	float sleep_time = std::max(17.0f - dt, 0.0f);
	if (sleep_time > 0.0f)
	{
		std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));
	}

	if (!m_current_level)
		return;

	m_current_level->update(dt);

	m_debugging = graphics::getKeyState(graphics::SCANCODE_0);
	

}

std::string GameState::getFullAssetPath(const std::string& asset)
{
	return ASSET_PATH + asset;
}

std::string GameState::getAssetDir()
{
	return ASSET_PATH;
}

GameState* GameState::m_unique_instance = nullptr;