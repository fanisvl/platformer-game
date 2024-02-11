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
	MovingEnemyBlock,
	ProjectileEnemyBlock,
	CoinsBlock,
	PlayerSpawn,
	RotatingTrapBlock ,
	LAST_TYPE,

};

class LevelMaker : public GameObject {
	graphics::MouseState mouse;
	graphics::Brush mouse_brush;
	Level* m_level = nullptr;
	float mouse_canvas_x; // Mouse canvas coordinates
	float mouse_canvas_y;
	int snap_mouse_x; // Integer rounded mouse canvas coordinates
	int snap_mouse_y; // 
	bool snap_mode; // Snap blocks in place for better accuracy
	bool edit_mode; // Editing an existing level
	std::string save_to; // Used by SaveToFile() in case of edit mode, to remember the file it should save to, once done editing.
	BlockType current_block_type;

public:
	void update(float ms) override;
	void draw() override;
	void init() override;
	void createObject();
	void removeObject();
	void saveToFile();
	bool fileExists(const std::string& filename);
	void showOptions();
	bool mouseIntersect(float x, float y);
	void nextBlockType();
	Level* getLevel() { return m_level; }
	LevelMaker(const std::string& load_level);
	~LevelMaker();
};