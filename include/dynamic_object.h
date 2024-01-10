#pragma once

#include "sgg/graphics.h"
#include "static_block.h"

enum CollisionType {
    SIDEWAYS,
    DOWNWARDS,
    UPWARDS,
};

class DynamicObject : public StaticBlock {
    bool hidden;
public:
    void update(float dt) override;
    void draw() override;
    void init() override;
    DynamicObject(float x, float y, float w, float h, const std::string& assetName);
    void hide();
    void show();
    void handleCollision(CollisionType type);
};