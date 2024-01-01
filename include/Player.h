#pragma once
#include "GameObject.h"
#include "graphics.h"
#include "box.h"
#include "config.h"

class Player : public GameObject {

    graphics::Brush mPlayerBrush;
    float mPosX;
    float mPosY;
    float speed;

public:
    void update(float dt) override;
    void draw() override;
    void init() override;
};

