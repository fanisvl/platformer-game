#include "gamestate.h"
#include "level.h"
#include "player.h"
#include "level_maker.h"
#include "menu.h"
#include <thread>
#include <chrono>
#include <iostream>
using namespace std::chrono_literals;

GameState::GameState()
{
}

GameState::~GameState()
{
	// It's safe to delete a nullptr
	delete m_menu;
	delete m_current_level;
	delete m_player;
	delete m_level_maker;
}

GameState* GameState::getInstance()
{
	if (!m_unique_instance) m_unique_instance = new GameState();
	return m_unique_instance;
}

void GameState::init()
{
	m_menu = new Menu();
	m_current_level = new Level("level1.txt");
	m_player = new Player();

	m_menu->init();
	m_current_level->init();
	m_player->init();

	graphics::preloadBitmaps(getAssetDir());
	graphics::setFont(getFullAssetPath("OpenSans-Regular.ttf"));

}

void GameState::draw()
{
	if (!m_current_level)
		return;


	// Draw Level Maker
	if (m_level_maker != nullptr) {
		m_level_maker->draw();
		// level maker handles it's own level
		return; // don't draw m_current_level or m_player if level maker is active
	}

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
	if (sleep_time > 0.0f) {
		std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));
	}



	// Level Maker
	if (graphics::getKeyState(graphics::SCANCODE_1))
		enter_level_maker();
	if (graphics::getKeyState(graphics::SCANCODE_2))
		exit_level_maker();

	// If m_level_maker != nullptr the method returns so as not to call m_currentlevel->update() and m_player->update().
	// If m_level_maker is active, it's responsible for level and player.
	if (m_level_maker != nullptr) {
		m_level_maker->update(dt);
		return;
	}


	if (m_current_level != nullptr) m_current_level->update(dt);
	if (m_player->isActive()) m_player->update(dt);

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

void GameState::playerDeath() {
	m_current_level->resetLevel();
}

GameState* GameState::m_unique_instance = nullptr;

void GameState::enter_level_maker() {
	if (!m_level_maker) {
		m_level_maker = new LevelMaker(); // I get a warning "expected a type specifier" but no errors. ????
		m_level_maker->init();
		// User can choose to save their new level or discard it
		// If the user saves the level a new txt file is created
		// If the user discards the level he's back to level 1
		// TODO: Add level selector???
		std::cout << "Level maker created" << std::endl;
	}
}

void GameState::exit_level_maker() {
	// Exit Level Maker Mode
	if (m_level_maker != nullptr) {
		delete m_level_maker;
		m_level_maker = nullptr;
		std::cout << "Level maker deleted" << std::endl;
	}
}


