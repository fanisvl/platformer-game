#pragma once
#include "dynamic_object.h"

class FallingPlatform : public DynamicObject {
protected:
    bool falling;
    bool destruct;
public:
    void update(float dt) override;
    void draw() override;
    void init() override;  
    void reset() override;
    FallingPlatform(float x, float y, float w, float h, const std::string& assetName);
    bool isFalling();
    void setFalling(bool b);
    void goDown();
    void handleCollision(CollisionType type) override;
    std::string FallingPlatform::to_string() const override;
    void checkHide();
};