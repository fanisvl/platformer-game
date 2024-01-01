#pragma once
#include "GameObject.h"
#include "box.h"
#include "graphics.h"
#include <vector>

class Block : public GameObject, public Box {

    std::string mAssetName;
    graphics::Brush mBlockBrush;
    graphics::Brush mBlockBrushDebug;

public:
    void update(float dt) override;
    void draw() override;
    void init() override;
    Block(float x, float y, float w, float h, std::string& assetName);
};
