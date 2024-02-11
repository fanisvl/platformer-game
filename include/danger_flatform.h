#pragma once
#include "static_object.h"

class DangerPlatform : public StaticObject {
protected:
    bool falling = true;
    bool destruct = false;
public:
    void update(float dt) override;
    void draw() override;
    void init() override;
    DangerPlatform(float x, float y, float w, float h, const std::string& assetName);
    bool isFalling();
    void setFalling();
    void goDown();
    void handleCollision(CollisionType type) override;

};