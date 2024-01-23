#include "level_maker.h"
#include "level.h"
#include <iostream>
#include <fstream>
#include "spikes.h"
#include "static_object.h"

void LevelMaker::update(float ms) {
	// mouse.cur_pos_x and mouse.cur_pos_y are pixel coordinates
	graphics::getMouseState(mouse);
	mouse_canvas_x = (mouse.cur_pos_x / static_cast<float>(WINDOW_WIDTH)) * CANVAS_WIDTH;
	mouse_canvas_y = (mouse.cur_pos_y / static_cast<float>(WINDOW_HEIGHT)) * CANVAS_HEIGHT;

	// Get snapped positions, used by snap mode.
	if (snap_mode) {
		mouse_canvas_x = static_cast<int>(mouse_canvas_x) + 1;
		mouse_canvas_y = static_cast<int>(mouse_canvas_y) + 1;
	}

	// LevelMaker is responsible for m_level and player when enabled.
	m_level->update(ms);
	m_state->getPlayer()->update(ms);

	// Check if any mouse button is clicked and perform necessary operations
	createObject();
	removeObject();

	if (mouse.button_middle_pressed && !mouse.button_left_pressed) {
		nextBlockType();
		std::cout << current_block_type << std::endl;
	}

	// Save to file
	if (graphics::getKeyState(graphics::SCANCODE_BACKSPACE)) {
		saveToFile();
	}

	// Enable snap mode
	snap_mode = graphics::getKeyState(graphics::SCANCODE_E);
}

// Create a new block (static object) with left click and add it to level vector.
void LevelMaker::createObject() {
	if (mouse.button_left_pressed) {

		std::string asset_path = "";
		auto& static_objects = m_level->getStaticObjects();

		switch (current_block_type) {

		case Block:
			asset_path = "terrain\\cave_block.png";
			static_objects.push_back(new StaticObject(mouse_canvas_x, mouse_canvas_y, 1.0f, 1.0f, asset_path));
			static_objects.back()->init();
			break;
		case SpikeBlock:
			asset_path = "terrain\\cave_spikes2.png";
			static_objects.push_back(new Spikes(mouse_canvas_x, mouse_canvas_y, 1.0f, 1.0f, asset_path));
			static_objects.back()->init();
			break;
		}

	}
}

// Remove a block with right click.
void LevelMaker::removeObject() {
	if (mouse.button_right_pressed && !mouse.button_left_pressed) {
		auto& static_objects = m_level->getStaticObjects();

		for (auto it = static_objects.begin(); it != static_objects.end();) {
			
			const auto& p_sob = *it;

			if (mouseIntersect(p_sob->m_pos_x, p_sob->m_pos_y)) {
				it = static_objects.erase(it);
			}

			else ++it;

		}
	}
}

void LevelMaker::saveToFile() {
	std::ofstream outputFile;

	if (edit_mode) {
		outputFile.open("levels\\" + save_to);
	}

	else {

		int level_id = 1;
		// Check for an existing file and increment level_id if necessary
		while (fileExists("levels\\my_level_" + std::to_string(level_id) + ".txt")) {
			level_id++;
		}

		// Open the file to write with the updated level_id
		outputFile.open("levels\\my_level_" + std::to_string(level_id) + ".txt");
	}

	// Check if the file is opened successfully
	if (!outputFile.is_open()) {
		std::cerr << "Error opening file for writing." << std::endl;
		return;
	}

	// Iterate through static objects and write to the file
	for (const auto& p_sob : m_level->getStaticObjects()) {
		outputFile << p_sob->to_string() << std::endl;
	}

	outputFile.close();

	std::cout << "File save complete!" << std::endl;

	m_state->exitToMenu();
}

bool LevelMaker::fileExists(const std::string& filename) {
	FILE* file = fopen(filename.c_str(), "r");
	if (file != nullptr) {
		fclose(file);
		return true;
	}
	return false;
}

void LevelMaker::showOptions() {
	graphics::Brush text_brush;
	text_brush.fill_opacity = 1.0f;
	SETCOLOR(text_brush.fill_color, 255, 255, 255);
	graphics::setFont("assets\\Roboto-Bold.ttf");

	graphics::drawText(7.0f, 0.5f, 0.4f, "Left/Right Click   ---   Add/Remove Object", text_brush);
	graphics::drawText(7.0f, 1.0f, 0.4f, "Middle Mouse Button   ---   Change object type", text_brush);
	graphics::drawText(0.5f, 0.5f, 0.4f, "BACKSPACE   ---   Save Level", text_brush);
	graphics::drawText(0.5f, 1.0f, 0.4f, "Q   ---   Exit Level Maker", text_brush);
	graphics::drawText(0.5f, 1.5f, 0.4f, "E   ---   Hold for Snap Mode", text_brush);
}

void LevelMaker::draw() {
	m_level->draw();
	m_state->getPlayer()->draw();

	mouse_brush.fill_opacity = 0.5f;
	mouse_brush.outline_opacity = 0.5f;

	switch (current_block_type) {
	case Block:
		mouse_brush.texture = m_state->getFullAssetPath("terrain\\cave_block.png");
		graphics::drawRect(mouse_canvas_x, mouse_canvas_y, 1.0f, 1.0f, mouse_brush);
		break;
	case SpikeBlock:
		mouse_brush.texture = m_state->getFullAssetPath("terrain\\cave_spikes2.png");
		graphics::drawRect(mouse_canvas_x, mouse_canvas_y, 1.0f, 1.0f, mouse_brush);
		break;

	}

	showOptions();

}

void LevelMaker::init() {
}

LevelMaker::LevelMaker(const std::string& load_level) {

	if (load_level != "default_level") {
		edit_mode = true;
		save_to = load_level;
	}
	m_level = new Level(load_level);
	m_level->init();
	mouse_canvas_x = 0;
	mouse_canvas_y = 0;
	snap_mouse_x = 0;
	snap_mouse_y = 0;
	snap_mode = false;
	current_block_type = Block;
}


LevelMaker::~LevelMaker() {
	delete m_level;
}

bool LevelMaker::mouseIntersect(float x, float y) {
	return static_cast<int>(x) == static_cast<int>(mouse_canvas_x) && static_cast<int>(y) == static_cast<int>(mouse_canvas_y);
}

void LevelMaker::nextBlockType() {
	int nextTypeIndex = static_cast<int>(current_block_type) + 1;
	current_block_type = (nextTypeIndex >= LAST_TYPE) ? static_cast<BlockType>(0) : static_cast<BlockType>(nextTypeIndex);
}