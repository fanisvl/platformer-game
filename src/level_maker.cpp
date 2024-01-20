#include "level_maker.h"
#include "level.h"
#include <iostream>

void LevelMaker::update(float ms) {
	// mouse.cur_pos_x and mouse.cur_pos_y are pixel coordinates
	mouse_canvas_x = (mouse.cur_pos_x / static_cast<float>(WINDOW_WIDTH)) * CANVAS_WIDTH;
	mouse_canvas_y = (mouse.cur_pos_y / static_cast<float>(WINDOW_HEIGHT)) * CANVAS_HEIGHT;
	m_level->update(ms);
	createObject();

}

// Create a new block (static object) with left click and add it to level vector.
void LevelMaker::createObject() {
	graphics::getMouseState(mouse);
	if (mouse.button_left_pressed) {
		m_level->getStaticObjects().push_back(new StaticObject(mouse_canvas_x, mouse_canvas_y, 1.0f, 1.0f, "terrain\\cave_block.png"));
		std::cout << "Mouse left pressed " << std::endl;
	}
}

void LevelMaker::draw() {
	m_level->draw();

	mouse_brush.fill_opacity = 1.0f;
	graphics::drawRect(mouse_canvas_x, mouse_canvas_y, 1.0f, 1.0f, mouse_brush);

	// Add test level option, draw player then
	// TODO: Draw player is being called twice, making to player run faster.
	m_state->getPlayer()->draw();
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