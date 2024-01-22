#pragma once
#include "gameobject.h"
#include "sgg/graphics.h"
#include "level.h"
#include "spikes.h"
#include "player.h"

enum BlockType {

	// LAST_TYPE represents the last block type in the enumeration. 
	// It is used by nextType() to ensure cyclical scrolling, 
	// where incrementing beyond the last type wraps around to the first type.

	Block,
	SpikeBlock,
	//MovingEnemyBlock,
	//CoinsBlock,
	//PlayerSpawnBlock,
	LAST_TYPE,

};

class LevelMaker : public GameObject {
	Player* m_player;
	graphics::MouseState mouse;
	graphics::Brush mouse_brush;
	Level* m_level = nullptr;
	float mouse_canvas_x;
	float mouse_canvas_y;
	int snap_mouse_x;
	int snap_mouse_y;
	bool snap_mode;
	BlockType current_block_type;

public:
	void update(float ms) override;
	void draw() override;
	void init() override;
	void create_object();
	void remove_object();
	void save_to_file();
	bool file_exists(const std::string& filename);
	void show_options();
	bool mouse_intersect(float x, float y);
	void next_block_type();
	LevelMaker();
	~LevelMaker();
};