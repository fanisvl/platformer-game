#include "Level.h"
#include "GameState.h"
#include "config.h"
#include <string>
#include "graphics.h"
#include "Player.h"
#include "GameObject.h"
#include "Block.h"
#include "Controller.h"
#include <iostream>

void Level::update(float dt) {

    // If player is active call update
    if (mState->getPlayer()->isActive()) mState->getPlayer()->update(dt);

    // Update dynamic objects
    for (auto& pGob : mDynamicObjects) {
        if (pGob) pGob->update(dt);
    }

}

void Level::draw() {

    // Draw background
    graphics::drawRect(backgroundX, backgroundY, 2*CANVAS_WIDTH, 2*CANVAS_HEIGHT, mBrushBackground);

    // Draw Player
    if (mState->getPlayer()->isActive()) mState->getPlayer()->draw();

    // Call draw() for all static and dynamic objects of level
    for (auto& pGob : mStaticObjects) {
        if (pGob) pGob->draw();
    }

    for (auto& pGob : mDynamicObjects) {
        if (pGob) pGob->draw();
    }

}

void Level::init() {

    // Initialize brush to draw background
    mBrushBackground.outline_opacity = 0.0f;
    mBrushBackground.texture = std::string(ASSET_PATH) + "city_background.png";
    backgroundX = CANVAS_WIDTH / 2.0f;
    backgroundY = CANVAS_HEIGHT / 2.0f;
    // TODO: Load level from txt file
    // TODO: load based on current level
    // Load Level
    mStaticObjects.push_back(new Block(CANVAS_WIDTH/2.0f, CANVAS_HEIGHT/2.0f, 250.0f, 55.0f, "platform.png"));


    // Call init() for all static and dynamic objects of level
    for (auto& pGob : mStaticObjects) {
        if (pGob) pGob->init();
    }

    for (auto& pGob : mDynamicObjects) {
        if (pGob) pGob->init();
    }

}



Level::Level (const std::string& name) {

};

Level::~Level() {

    for (auto& pGob : mStaticObjects) {
        if (pGob) delete pGob;
    }

    for (auto& pGob : mDynamicObjects) {
        if (pGob) delete pGob;
    }
};

std::vector<GameObject *> &Level::getStaticObjects() {
    return mStaticObjects;
}

std::list<GameObject *> &Level::getDynamicObjects() {
    return mDynamicObjects;
}

void Level::moveBackground(float dx, float dy) {
    //= (mState->mGlobalOffsetX + CANVAS_WIDTH / 2.0f) * backgroundSpeed;
    // Boundaries
    if (backgroundX < 0) backgroundX = 0;
    if (backgroundX > CANVAS_WIDTH) backgroundX = CANVAS_WIDTH;
    if (backgroundY < 0) backgroundY = 0;
    if (backgroundY > CANVAS_HEIGHT) backgroundY = CANVAS_HEIGHT;
    
    backgroundX += dx * backgroundSpeed;
    backgroundY += dy * backgroundSpeed;
}
