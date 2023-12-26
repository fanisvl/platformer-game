#pragma once
#include "GameObject.h"
#include "config.h"

class Player : public GameObject {

    float posX = CANVAS_WIDTH / 2;
    float posY = CANVAS_HEIGHT / 2;
    float speed = 10.0f;

public:
    void update() override;
    void draw() override;
    void init() override;
};

