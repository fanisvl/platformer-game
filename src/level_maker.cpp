#include "level_maker.h"
#include "level.h"
#include <iostream>

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

void LevelMaker::saveToFile() {
	for (auto& p_sob : m_level->getStaticObjects()) {
		std::cout << p_sob->to_string() << std::endl;
	}
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

}


LevelMaker::~LevelMaker() {
	delete m_level;
}