#include "Level.h"
#include "GameState.h"
#include "config.h"
#include <string>
#include "graphics.h"
#include "Player.h"
#include "GameObject.h"

void Level::update(float dt) {

    // If player is active call update
    if (mState->getPlayer()->isActive()) mState->getPlayer()->update(dt);

}

void Level::draw() {

    // Draw background
    float backgroundX = mState->mGlobalOffsetX + CANVAS_WIDTH / 2.0f;
    float backgroundY = mState->mGlobalOffsetY + CANVAS_HEIGHT/ 2.0f;
    graphics::drawRect(backgroundX, backgroundY, CANVAS_WIDTH, CANVAS_HEIGHT, mBrushBackground);

    // Draw Player
    if (mState->getPlayer()->isActive()) mState->getPlayer()->draw();

    // Call draw() for all static and dynamic objects of level
    for (auto pGob : mStaticObjects) {
        if (pGob) pGob->draw();
    }

    for (auto pGob : mDynamicObjects) {
        if (pGob) pGob->draw();
    }

}

void Level::init() {

    // Initialize brush to draw background
    mBrushBackground.outline_opacity = 0.0f;
    mBrushBackground.texture = std::string(ASSET_PATH) + "city_background.png";


    // Call init() for all static and dynamic objects of level
    for (auto pGob : mStaticObjects) {
        if (pGob) pGob->init();
    }

    for (auto pGob : mDynamicObjects) {
        if (pGob) pGob->init();
    }

}

Level::Level (const std::string& name) {

};

Level::~Level() {

    for (auto pGob : mStaticObjects) {
        if (pGob) delete pGob;
    }

    for (auto pGob : mDynamicObjects) {
        if (pGob) delete pGob;
    }
};