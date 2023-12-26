#pragma once
#include "GameObject.h"

class Player : public GameObject {
public:
    void update() override;
    void draw() override;
    void init() override;
};

