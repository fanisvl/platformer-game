#include "menu.h"
#include <iostream>
#include <filesystem>


#pragma once

void Menu::init() {

	m_current_menu = MainMenu;

	m_brush.fill_opacity = 1.0f;
	graphics::setFont("assets\\Roboto-Bold.ttf");

	if (m_background == nullptr) m_background = new Background("background/cave_background.png");
}

void Menu::update(float dt) {

	// Prevent detecting multiple key presses for a single physical press.
	static bool mKeyProcessed = false;
	static float cooldownTime = 1000.0f;  // 1 second cooldown time
	static float cooldownTimer = 0.0f;

	if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
		std::cout << "SPACE pressed" << std::endl;
		m_state->startNewGame();
	}
	else if (graphics::getKeyState(graphics::SCANCODE_M) && !mKeyProcessed) {
		std::cout << "M pressed" << std::endl;
		m_current_menu = LevelMakerMenu;
		mKeyProcessed = true;
		cooldownTimer = cooldownTime;  // Start cooldown timer
		
		

	}

	// Update cooldown timer
	if (cooldownTimer > 0.0f) {
		cooldownTimer -= dt;
		if (cooldownTimer <= 0.0f) {
			mKeyProcessed = false;  // Reset key processed flag after cooldown
		}
	}

}

void Menu::draw() {

	if (m_background)
		m_background->draw();

	switch (m_current_menu) {
	case MainMenu:
		showMainMenu();
		break;

	case LevelMakerMenu:
		showLevelMakerMenu();
		break;
	}
}

void Menu::showMainMenu() {
	SETCOLOR(m_brush.fill_color, 255, 255, 255);
	graphics::drawText(6.0f, CANVAS_HEIGHT / 2.0f, 0.5f, "Press SPACE to play", m_brush);
	graphics::drawText(5.0f, 5.5f, 0.4, "Press   M   to   activate   Level   Maker", m_brush);
	graphics::drawText(6.2f, 8.5f, 0.3, "Press   Q   to   return   to   Menu", m_brush);

}

void Menu::showLevelMakerMenu() {
	SETCOLOR(m_brush.fill_color, 255, 255, 255);

	graphics::drawText(1.0f, 4.0f, 0.5f, "Press   'N'   to   create   a   New   Level", m_brush);

	graphics::drawText(1.0f, 5.0f, 0.5f, "Or select   an   existing   level   to   edit", m_brush);

	// Display levels available to edit
	std::vector<std::string> level_names = getLevelNames("levels\\");
	float text_offset_y = 0.0;
	float text_add_offset = 0.7f; // used to display level names in a list format
	int max_levels_allowed = 9; // max number of levels before they overflow the screen
	int index = 0; // level index

	for (std::string name : level_names) {

		graphics::drawText(10.0f, 2.0 + text_offset_y, 0.4f, std::to_string(index) + ".   " + name, m_brush);

		text_offset_y += text_add_offset;
		index++;

		if (index == max_levels_allowed) break; // Stop printing more levels before they overflow the screen
	}
	

	// Create a new Level
	if (graphics::getKeyState(graphics::SCANCODE_N)) {
		m_state->enterLevelMaker("default_level.txt");
		m_current_menu = MainMenu;
	}


	// Select a level to edit
	int selection = 0;

	if (graphics::getKeyState(graphics::SCANCODE_0)) selection = 0;
	else if (graphics::getKeyState(graphics::SCANCODE_1)) selection = 1;
	else if (graphics::getKeyState(graphics::SCANCODE_2)) selection = 2;
	else if (graphics::getKeyState(graphics::SCANCODE_3)) selection = 3;
	else if (graphics::getKeyState(graphics::SCANCODE_4)) selection = 4;
	else if (graphics::getKeyState(graphics::SCANCODE_5)) selection = 5;
	else if (graphics::getKeyState(graphics::SCANCODE_6)) selection = 6;
	else if (graphics::getKeyState(graphics::SCANCODE_7)) selection = 7;
	else if (graphics::getKeyState(graphics::SCANCODE_8)) selection = 8;
	else if (graphics::getKeyState(graphics::SCANCODE_9)) selection = 9;
	else selection = -1; // -1 indicates no selection.

	if (selection != -1 && selection < level_names.size()) {
		std::string selected_level = level_names[selection];
		std::cout << selected_level << std::endl;
		m_state->enterLevelMaker(selected_level + ".txt");
		m_current_menu = MainMenu;
	}



	
}

std::vector<std::string> Menu::getLevelNames(const std::string& path) {

	std::vector<std::string> levelNames;

	try {
		for (const auto& entry : std::filesystem::directory_iterator(path)) {


			// Convert std::filesystem::path to std::string
			std::string filename = entry.path().stem().string();

			if (filename == "default_level") continue; // Default level is used only for new level creation.

			levelNames.push_back(filename);
		}
	}

	catch (const std::filesystem::filesystem_error& ex) {
		std::cerr << "Error accessing the directory: " << ex.what() << std::endl;
	}

	return levelNames;
}
