#include "level_maker.h"
#include <iostream>

void LevelMaker::update(float ms) {
	graphics::getMouseState(mouse);
	if (mouse.button_left_pressed) {
		std::cout << "left button pressed" << std::endl;
	}

	// Assuming mouse.cur_pos_x and mouse.cur_pos_y are pixel coordinates
	float canvas_x = (mouse.cur_pos_x / static_cast<float>(WINDOW_WIDTH)) * CANVAS_WIDTH;
	float canvas_y = (mouse.cur_pos_y / static_cast<float>(WINDOW_HEIGHT)) * CANVAS_HEIGHT;

	std::cout << "Canvas X: " << canvas_x << std::endl;
	std::cout << "Canvas Y: " << canvas_y << std::endl;


}

void LevelMaker::draw() {
	mouse_brush.fill_opacity = 1.0f;
	
}

void LevelMaker::init() {

}
