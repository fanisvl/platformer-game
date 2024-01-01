#pragma once
#include "GameObject.h"
#include "box.h"
#include "graphics.h"
#include <vector>

class Block : public GameObject {

    std::string mAssetName;
    graphics::Brush mBlockBrush;
    graphics::Brush mBlockBrushDebug;

public:
    void update(float dt) override;
    void draw() override;
    void init() override;
    Block(float x, float y, float w, float h, const std::string& assetName);
};
