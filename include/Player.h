#pragma once
#include "GameObject.h"
#include "config.h"

class Player : public GameObject {

    float posX = CANVAS_WIDTH / 2.0f;
    float posY = CANVAS_HEIGHT / 2.0f;
    float speed = 10.0f;

public:
    void update() override;
    void draw() override;
    void init() override;
};

