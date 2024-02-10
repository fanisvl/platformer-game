#pragma once
#include "config.h"
#include <string>
#include <vector>

enum CurrentState {
	MenuActive,
	GameActive,
	LevelMakerActive,
	//PausedActive,
};

class GameState {
private:
	static GameState* m_unique_instance;
	CurrentState m_current_state;
	class Menu* m_menu = nullptr;
	class Level* m_current_level = nullptr;
	int current_level_index = 0;
	class Level* m_next_level = nullptr;
	class Player* m_player = nullptr;
	class LevelMaker* m_level_maker = nullptr;
	std::vector<std::string> m_level_names;


public:
	bool m_debugging = false;
	GameState();
	~GameState();
	static GameState* getInstance();
	void init();
	void draw();
	void update(float dt);

	std::string getFullAssetPath(const std::string& asset);
	std::string getAssetDir();
	class Player* getPlayer() { return m_player; }
	void playerDeath();
	void enterLevelMaker(const std::string& load_level);
	void exitLevelMaker();
	void startNewGame();
	void loadLevelNames();
	void loadNextLevel();
	void goToNextLevel();
	void exitToMenu();
};
