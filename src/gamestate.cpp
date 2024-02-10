#include "gamestate.h"
#include "level.h"
#include "player.h"
#include "level_maker.h"
#include "menu.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <filesystem>
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

	loadLevelNames();

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

	// Press BackSpace to go back to main menu
	if (graphics::getKeyState(graphics::SCANCODE_Q)) exitToMenu();

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


		if (m_player->getPoints() >= 8 && m_next_level == nullptr) {
			// Start loading next level
			loadNextLevel();
		}

		// If player collected all points, go to next level
		if (m_player->getPoints() >= 20 && m_next_level != nullptr) {
			goToNextLevel();
			m_player->resetPoints();
		}
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
	m_current_level->resetLevel();

}

void GameState::loadNextLevel() {

	std::cout << "Load next level" << std::endl;
	int next_level_index = current_level_index + 1;
	std::cout << "Next level index: " << next_level_index << std::endl;
	if (next_level_index >= m_level_names.size()) {
		std::cout << "No more levels - Go to Main Menu" << std::endl;
		m_current_state = MenuActive;

		delete m_current_level;
		m_current_level = nullptr;
		current_level_index = 0;

		m_player->resetPoints();
		return;
	}

	m_next_level = new Level(m_level_names[next_level_index]);
	std::cout << "Created level: " << m_level_names[next_level_index] << std::endl;
	m_next_level->init();
}

void GameState::goToNextLevel() {
	std::cout << "Go to next level" << std::endl;
	delete m_current_level;
	m_current_level = m_next_level;
	current_level_index++;
	m_current_level->resetLevel();
	m_next_level = nullptr;
}

void GameState::loadLevelNames() {
	std::string level_folder = "levels/";
	try {
		for (const auto& entry : std::filesystem::directory_iterator(level_folder)) {
			// Convert std::filesystem::path to std::string
			std::string filename = entry.path().filename().string();
			if (filename != "default_level.txt") {
				std::cout << "Pushing: " << filename << std::endl;
				m_level_names.push_back(filename);
			}
		}
	}

	catch (const std::filesystem::filesystem_error& ex) {
		std::cerr << "Error accessing the directory: " << ex.what() << std::endl;
	}
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

void GameState::enterLevelMaker(const std::string& load_level) {
	m_current_state = LevelMakerActive;

	// Create a level maker
	if (!m_level_maker) {
		m_level_maker = new LevelMaker(load_level);
		m_level_maker->init();

		// Level maker has it's own level, however we need to pass it to gamestate as m_current_level
		// in order to use it for methods like playerDeath (m_current_level->resetLevel())
		m_current_level = m_level_maker->getLevel();

		std::cout << "Level maker created" << std::endl;
	}
}

void GameState::exitLevelMaker() {

	// Set current level (previously level maker's m_level) to nullptr
	// Level maker will delete their m_level
	m_current_level = nullptr;
	
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