#include "level_maker.h"
#include "level.h"
#include <iostream>
#include <fstream>

void LevelMaker::update(float ms) {
	// mouse.cur_pos_x and mouse.cur_pos_y are pixel coordinates
	mouse_canvas_x = (mouse.cur_pos_x / static_cast<float>(WINDOW_WIDTH)) * CANVAS_WIDTH;
	mouse_canvas_y = (mouse.cur_pos_y / static_cast<float>(WINDOW_HEIGHT)) * CANVAS_HEIGHT;
	m_level->update(ms);
	m_state->getPlayer()->update(ms);
	createObject();

	if (graphics::getKeyState(graphics::SCANCODE_3)) {
		saveToFile();
	}
}

// Create a new block (static object) with left click and add it to level vector.
void LevelMaker::createObject() {
	graphics::getMouseState(mouse);
	if (mouse.button_left_pressed) {
		std::string asset_path = "terrain\\cave_block.png";
		m_level->getStaticObjects().push_back(new StaticObject(mouse_canvas_x, mouse_canvas_y, 1.0f, 1.0f, asset_path));
		std::cout << "Mouse left pressed " << std::endl;
	}
}

// TODO: Add removeObject() method, StaticObjects should be stored in a list, in order to be dynamically removed.

void LevelMaker::saveToFile() {

	int level_id = 1;
	std::string file_name = "levels\\my_level_" + std::to_string(level_id) + ".txt";

	// Check for an existing file and increment level_id if necessary

	// Open the file to write
	std::ofstream outputFile(file_name);

	// Check if the file is opened successfully
	if (!outputFile.is_open()) {
		std::cerr << "Error opening file for writing." << std::endl;
		return;
	}

	// Iterator through static objects and write to the file
	for (auto& p_sob : m_level->getStaticObjects()) {
		outputFile << p_sob->to_string() << std::endl;
	}

	outputFile.close();

	std::cout << "File save complete!" << std::endl;

	m_state->exit_level_maker();

}

void LevelMaker::draw() {
	m_level->draw();
	m_state->getPlayer()->draw();

	mouse_brush.fill_opacity = 0.5f;
	mouse_brush.outline_opacity = 1.0f;
	graphics::drawRect(mouse_canvas_x, mouse_canvas_y, 1.0f, 1.0f, mouse_brush);

}

void LevelMaker::init() {
}

LevelMaker::LevelMaker() {
	m_level = new Level("default_level.txt");
	m_level->init();
	mouse_canvas_x = 0;
	mouse_canvas_y = 0;
}


LevelMaker::~LevelMaker() {
	delete m_level;
}