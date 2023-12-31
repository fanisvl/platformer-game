#pragma once
#include "GameObject.h"
#include "graphics.h"
#include "box.h"
#include "config.h"

class Player : public GameObject, public Box {

    graphics::Brush mPlayerBrush;
    float mPosX = CANVAS_WIDTH / 2.0f;
    float mPosY = CANVAS_HEIGHT / 2.0f;
    float speed = 0.5f;

public:
    Player(std::string name) : GameObject(name) {}
    void update(float dt) override;
    void draw() override;
    void init() override;
};

