#pragma once
#include "GameObject.h"
#include "graphics.h"
#include <list>
#include <vector>

class Level : public GameObject {

    graphics::Brush mBrushBackground;
    float backgroundSpeed;
    float backgroundX; // = (mState->mGlobalOffsetX + CANVAS_WIDTH / 2.0f) * backgroundSpeed;
    float backgroundY; // = (mState->mGlobalOffsetY + CANVAS_HEIGHT/ 2.0f) * backgroundSpeed;

    std::vector<GameObject*> mStaticObjects;
    std::list<GameObject*> mDynamicObjects;

    void checkCollisions();

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


