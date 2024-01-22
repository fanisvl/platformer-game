#pragma once
#include "config.h"
#include <string>

enum CurrentState {
	MenuActive,
	GameActive,
	LevelMakerActive,
	DebuggingActive,
	//PausedActive,
};

class GameState {
private:
	static GameState* m_unique_instance;
	CurrentState m_current_state;
	class Menu* m_menu = nullptr;
	class Level * m_current_level = nullptr;
	class Player* m_player = nullptr;
	class LevelMaker* m_level_maker = nullptr;

public:
	bool m_debugging = false; // TODO: Modify this functionality to use CurrentState enum instead of a boolean
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
	void enterLevelMaker();
	void exitLevelMaker();
	void startNewGame();
	void exitToMenu();
};
