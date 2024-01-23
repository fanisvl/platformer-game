#pragma once
#include "gameobject.h"
#include "background.h"
#include "sgg/graphics.h"

enum CurrentMenu {
	MainMenu,
	LevelMakerMenu,

};

class Menu : public GameObject {

	CurrentMenu m_current_menu;
	Background* m_background;
	graphics::Brush m_brush;
public:
	void init() override;
	void update(float dt) override;
	void draw() override;
	void showMainMenu();
	void showLevelMakerMenu();
	std::vector<std::string> Menu::getLevelNames(const std::string& path);
};