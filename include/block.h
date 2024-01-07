#pragma once
#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"
#include <vector>

class Block : public GameObject, public Box {

    std::string m_asset_name;
    graphics::Brush m_block_brush;
    graphics::Brush m_block_brush_debug;

public:
    void update(float dt) override;
    void draw() override;
    void init() override;
    // TODO: If GameObject inherits from Box, call GameObject consturctor. + move m_asset_name to GameObject.
    Block(float x, float y, float w, float h, const std::string& assetName);
};