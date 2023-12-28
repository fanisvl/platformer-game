#pragma once
#include "GameObject.h"
#include "graphics.h"
#include "box.h"
#include "config.h"

class Player : public GameObject, public Box {

    graphics::Brush mBrushPlayer;
    float posX = CANVAS_WIDTH / 2.0f;
    float posY = CANVAS_HEIGHT / 2.0f;
    float speed = 10.0f;

public:
    Player(std::string name) : GameObject(name) {}
    void update(float dt) override;
    void draw() override;
    void init() override;
};

