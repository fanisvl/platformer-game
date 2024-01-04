#pragma once
#include "GameObject.h"
#include "graphics.h"
#include <list>
#include <vector>

class Level : public GameObject {

    graphics::Brush mBrushBackground;
    const float backgroundSpeed = 400.0f;
    float backgroundX;
    float backgroundY;

    std::vector<GameObject*> mStaticObjects;
    std::list<GameObject*> mDynamicObjects;

public:
    void update(float dt) override;
    void draw() override;
    void init() override;
    Level (const std::string& name = "Level 0");
    ~Level();
    std::vector<GameObject*>& getStaticObjects();
    std::list<GameObject*>& getDynamicObjects();
    void moveBackground(float dx, float dy);
};


