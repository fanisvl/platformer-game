#pragma once
#include "gameobject.h"
#include "sgg/graphics.h"
#include "level.h"

class LevelMaker : public GameObject {
	graphics::MouseState mouse;
	graphics::Brush mouse_brush;
	Level* m_level = nullptr;
	float mouse_canvas_x;
	float mouse_canvas_y;
	int snap_mouse_x;
	int snap_mouse_y;
	bool snap_mode;

public:
	void update(float ms) override;
	void draw() override;
	void init() override;
	void create_object();
	void remove_object();
	void save_to_file();
	bool file_exists(const std::string& filename);
	void show_options();
	bool mouseIntersect(float x, float y);
	LevelMaker();
	~LevelMaker();
};