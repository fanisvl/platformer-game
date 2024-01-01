#pragma once
#include "GameObject.h"
#include "graphics.h"
#include "box.h"
#include "config.h"

class Player : public GameObject, public Box {

    graphics::Brush mPlayerBrush;
    float mPosX;
    float mPosY;
    float speed;

public:
    Player(std::string name) : GameObject(name) {}
    void update(float dt) override;
    void draw() override;
    void init() override;
};

