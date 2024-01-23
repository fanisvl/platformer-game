#include "gamestate.h"
#include "level.h"
#include "player.h"
#include "level_maker.h"
#include "menu.h"
#include <thread>
#include <chrono>
#include <iostream>
using namespace std::chrono_literals;

GameState::GameState(){
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

	m_current_state = MenuActive;

	m_menu = new Menu();
	m_menu->init();

	m_player = new Player();
	m_player->init();

	graphics::preloadBitmaps(getAssetDir());
	graphics::setFont(getFullAssetPath("OpenSans-Regular.ttf"));

}

void GameState::draw()
{

	switch (m_current_state) {
	case MenuActive:
		if (m_menu) m_menu->draw();
		break;

	case GameActive:
		if (m_current_level) m_current_level->draw();
		if (m_player) m_player->draw();
		break;

	case LevelMakerActive:
		if (m_level_maker) m_level_maker->draw();
		break;
	}

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

	// Press 1 to go back to main menu
	if (graphics::getKeyState(graphics::SCANCODE_1)) exitToMenu();

	// Hold 0 to activate debug mode
	m_debugging = graphics::getKeyState(graphics::SCANCODE_0);

	// Check the CurrentState and call the appropriate update methods.
	switch (m_current_state) {
	case MenuActive:
		if (m_menu) m_menu->update(dt);
		break;
		
	case GameActive:
		if (m_current_level) m_current_level->update(dt);
		if (m_player) m_player->update(dt);
		break;

	case LevelMakerActive:
		if (m_level_maker) m_level_maker->update(dt);
		break;
	}

}

void GameState::startNewGame() {

	m_current_state = GameActive;

	// Move these back to gameState init for quicker load time.
	m_current_level = new Level("level1.txt");
	m_current_level->init();

}

void GameState::exitToMenu() {
	
	if (m_current_state == LevelMakerActive) exitLevelMaker();

	m_current_state = MenuActive;
	delete m_current_level;
	m_current_level = nullptr;
}


void GameState::playerDeath() {
	m_current_level->resetLevel();
}

GameState* GameState::m_unique_instance = nullptr;

void GameState::enterLevelMaker() {
	m_current_state = LevelMakerActive;

	// Create a level maker
	if (!m_level_maker) {
		m_level_maker = new LevelMaker();
		m_level_maker->init();
		std::cout << "Level maker created" << std::endl;
	}
}

void GameState::exitLevelMaker() {

	// Delete level maker
	delete m_level_maker;
	m_level_maker = nullptr;
	std::cout << "Level maker deleted" << std::endl;
}

std::string GameState::getFullAssetPath(const std::string& asset)
{
	return ASSET_PATH + asset;
}

std::string GameState::getAssetDir()
{
	return ASSET_PATH;
}