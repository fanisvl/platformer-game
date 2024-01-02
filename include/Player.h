#pragma once
#include "GameObject.h"
#include "graphics.h"
#include "box.h"
#include "config.h"

class Player : public GameObject, public Box {

    graphics::Brush mPlayerBrush;
    graphics::Brush mPlayerBrushDebug;
    float speed;

public:
    void update(float dt) override;
    void draw() override;
    void init() override;
};

