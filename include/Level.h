#pragma once
#include "GameObject.h"
#include "graphics.h"
#include <list>
#include <vector>

class Level : public GameObject {

    graphics::Brush mBrushBackground;

    std::vector<GameObject*> mStaticObjects;
    std::list<GameObject*> mDynamicObjects;

    void checkCollisions();

public:
    void update(float dt) override;
    void draw() override;
    void init() override;
    Level (const std::string& name = "Level 0");
    ~Level();
};


