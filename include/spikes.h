#pragma once
#include "static_block.h"

class Spikes : public StaticBlock {
	
public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	Spikes(float x, float y, float w, float h, const std::string& asset);
};