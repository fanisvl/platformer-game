#pragma once
#include "gameobject.h"
#include "box.h"

class Spikes : public GameObject, public Box {
	std::string m_asset_path;
public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	Spikes(float x, float y, float w, float h, std::string asset);
};