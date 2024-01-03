#include "Level.h"
#include "GameState.h"
#include "config.h"
#include <string>
#include "graphics.h"
#include "Player.h"
#include "GameObject.h"
#include "Block.h"
#include <iostream>

void Level::update(float dt) {

    // If player is active call update
    if (mState->getPlayer()->isActive()) mState->getPlayer()->update(dt);

    // Update dynamic objects
    for (auto& pGob : mDynamicObjects) {
        if (pGob) pGob->update(dt);
    }

    checkCollisions();

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
    backgroundSpeed = 0.5f;

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

void Level::checkCollisions() {
    for (auto& pGob : mStaticObjects) {

        // If the object pointed to by pGob is a derived type of 'Box' (e.g. 'Block' or 'Player')
        // the cast returns a pointer of type Box*, necessary for the intersect method.
        // otherwise it returns a nullptr and the if-statement isn't executed.
        if (Box* pBox = dynamic_cast<Box*>(pGob)) {
            // Check for collision
            if (mState->getPlayer()->intersect(*pBox)) {
                std::cout << "intersect" << std::rand() << std::endl;
            }
        }

        // NOTE: We have a few other options here, we could:
        // 1. Make every GameObject inherit from Box.
        //    This approach also had the added benefit of inheriting the attributes mPosX, mPosY, mWidth, mHeight from Box,
        //    which are arguably necessary for every GameObject.
        //    Even for GameObjects like UI Elements, collisions could also prove to be useful for clicking/selecting.
        //
        // 2. Composite approach. Every GameObject would contain a 'Box' member that would be responsible for collisions.

        // 3. Store Box* types inside mStaticObjects instead of GameObject* types, however that introduces a similar
        //    problem for the init, update & draw GameObject methods, since Box and GameObject don't have any relationship.
        //    Not a great option.
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
    backgroundX += dx * backgroundSpeed;
    backgroundY += dy * backgroundSpeed;
}
