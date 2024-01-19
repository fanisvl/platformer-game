#include "level_maker.h"
#include <iostream>

void LevelMaker::update(float ms) {
	graphics::getMouseState(mouse);
	if (mouse.button_left_pressed) {
		std::cout << "left button pressed" << std::endl;
	}

	// Assuming mouse.cur_pos_x and mouse.cur_pos_y are pixel coordinates
	mouse_canvas_x = (mouse.cur_pos_x / static_cast<float>(WINDOW_WIDTH)) * CANVAS_WIDTH;
	mouse_canvas_y = (mouse.cur_pos_y / static_cast<float>(WINDOW_HEIGHT)) * CANVAS_HEIGHT;



}

void LevelMaker::draw() {
	mouse_brush.fill_opacity = 1.0f;
	graphics::drawRect(mouse_canvas_x, mouse_canvas_y, 1.0f, 1.0f, mouse_brush);
}

void LevelMaker::init() {

}
