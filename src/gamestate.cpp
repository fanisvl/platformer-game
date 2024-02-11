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

	graphics::playMusic("assets\\music.mp3", 0.01f, true, 0);


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

	// Press Q to go back to main menu
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

		// Start loading next level when the player has collected almost all the points
		if (m_player->getPoints() >= 5 && m_next_level == nullptr) {
			// Start loading next level
			loadNextLevel();
		}

		// If player collected all points, go to next level
		if (m_player->getPoints() >= 10) {

			if (m_next_level != nullptr) goToNextLevel();
			else if (m_next_level == nullptr) {
				std::cout << "No more levels - Go back to main menu" << std::endl;

				m_current_state = MenuActive;

				delete m_current_level;
				m_current_level = nullptr;
				current_level_index = 0;

				m_player->resetPoints();
			}
			m_player->resetPoints();
		}
		break;

	case LevelMakerActive:
		if (m_level_maker) m_level_maker->update(dt);
		break;
	}

}

void GameState::startNewGame() {
	// Reset everything from previous games
	delete m_current_level;
	m_current_level = nullptr;
	current_level_index = 0;
	m_player->resetPoints();

	// Start new game
	m_current_state = GameActive;
	m_current_level = new Level("level1.txt");
	m_current_level->init();
	m_current_level->resetLevel();

}

void GameState::loadNextLevel() {

	int next_level_index = current_level_index + 1;

	// Check if there are any more levels left, if not reset & return to menu
	if (next_level_index >= m_level_names.size()) {
		return;
	}

	// Create next level object and initialize
	m_next_level = new Level(m_level_names[next_level_index]);
	std::cout << "Created level: " << m_level_names[next_level_index] << std::endl;
	m_next_level->init();
}

void GameState::goToNextLevel() {
	std::cout << "Go to next level" << std::endl;

	delete m_current_level;
	m_current_level = m_next_level;
	current_level_index++;

	m_current_level->resetLevel(); // called to move player to the initial position
	m_next_level = nullptr;
}

void GameState::loadLevelNames() {
	std::string level_folder = "levels/";

	if (!m_level_names.empty()) m_level_names.clear();

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
	loadLevelNames();
}

std::string GameState::getFullAssetPath(const std::string& asset)
{
	return ASSET_PATH + asset;
}

std::string GameState::getAssetDir()
{
	return ASSET_PATH;
}