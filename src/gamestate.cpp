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

	graphics::preloadBitmaps(getAssetDir());
	graphics::setFont(getFullAssetPath("OpenSans-Regular.ttf"));

}

void GameState::draw()
{

	switch (m_current_state) {
	case MenuActive:
		m_menu->draw();
		break;

	case GameActive:
		m_current_level->draw();
		m_player->draw();
		break;

	case LevelMakerActive:
		m_level_maker->draw();
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
		m_menu->update(dt);
		break;
		
	case GameActive:
		m_current_level->update(dt);
		m_player->update(dt);
		break;

	case LevelMakerActive:
		m_level_maker->update(dt);
		break;
	}

}

void GameState::startNewGame() {

	m_current_state = GameActive;

	// Move these back to gameState init for quicker load time.
	m_current_level = new Level("level1.txt");
	m_player = new Player();
	m_current_level->init();
	m_player->init();

}

void GameState::exitToMenu() {
	if (m_current_state == GameActive) {
		m_current_state = MenuActive;
		delete m_current_level;
		delete m_player;
	}
}


void GameState::playerDeath() {
	m_current_level->resetLevel();
}

GameState* GameState::m_unique_instance = nullptr;

void GameState::enterLevelMaker() {
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

void GameState::exitLevelMaker() {
	// Exit Level Maker Mode
	if (m_level_maker != nullptr) {
		delete m_level_maker;
		m_level_maker = nullptr;
		std::cout << "Level maker deleted" << std::endl;
	}
}

std::string GameState::getFullAssetPath(const std::string& asset)
{
	return ASSET_PATH + asset;
}

std::string GameState::getAssetDir()
{
	return ASSET_PATH;
}