#include "Controller.h"



void Controller::update(float dt) {

    float dx = 0.0f;
    float dy = 0.0f;


    // WASD Keyboard Controls
    // Determine dx. Speed is determined by the object moving (move method)
    // dx = direction * t * speed
    if (graphics::getKeyState(graphics::SCANCODE_A)) {
        direction = LEFT;
        if (intersectLeft) return;
        intersectDown = false;
        intersectRight = false;
        dx = -1.0f * graphics::getDeltaTime();
        // Possible Collision left
    }

    if (graphics::getKeyState(graphics::SCANCODE_D)) {
        direction = RIGHT;
        if (intersectRight) return;
        intersectDown = false;
        intersectLeft = false;
        dx = +1.0f * graphics::getDeltaTime();
        // Possible collision right
    }

    if (graphics::getKeyState(graphics::SCANCODE_W)) {
        direction = UP;
        dy = -1.0f * graphics::getDeltaTime();
        intersectDown = false;
        intersectLeft = false;
        intersectRight = false;

        // Possible collision up

    }

    if (graphics::getKeyState(graphics::SCANCODE_S)) {
        direction = DOWN;
        if (intersectDown) return;
        intersectLeft = false;
        intersectRight = false;

        dy = +1.0f * graphics::getDeltaTime();
        // Possible collision down
    }

    // TODO: Move all movement calls to a new method
    mPlayer->move(dx, dy);
    // Move Static & Dynamic Objects relative to Player
    for (auto& pGob : mLevel->getStaticObjects()) {
        // If the object pointed to by pGob is a derived type of 'Box' (e.g. 'Block' or 'Player')
        // the cast returns a pointer of type Box*, necessary for the intersect method.
        // otherwise it returns a nullptr and the if-statement isn't executed.
        if (Box* pBox = dynamic_cast<Box*>(pGob)) {
            pBox->move(-dx, -dy);
        }
    }
    for (auto& pGob : mLevel->getDynamicObjects()) {
        if (Box* pBox = dynamic_cast<Box*>(pGob)) {
            pBox->move(-dx, -dy);
        }
    }
    // Move background relative to Player
    mLevel->moveBackground(-dx, -dy);

    checkCollisions();

}

// TODO: Remove after debugging.
#include <iostream>
void Controller::checkCollisions() {
    for (auto& pGob : mLevel->getStaticObjects()) {
        if (Box* pBox = dynamic_cast<Box*>(pGob)) {

            // Check for collision
            if (float offset = mPlayer->intersectDown(*pBox)) {
                mPlayer->mPosY += offset;
                intersectDown = true;
            }
            
            // TODO: Seperate left and right intersect sideways using offset.
//            intersectDown = mState->getPlayer()->intersectDown(*pBox);
//
//            float sidewaysOffset = mState->getPlayer()->intersectSideways(*pBox);
//
//            std::cout << "sidewaysOffset: " << sidewaysOffset << std::endl;
//

//
//            if (intersectDown) std::cout << "intersectDown  V " << std::endl;
//            if (intersectRight) std::cout << "intersectRight >> " << intersectRight << std::endl;
//            if (intersectLeft) std::cout << "intersectLeft  << " << intersectLeft << std::endl;
        }





        // NOTE on dynamic_cast<Box>: We have a few other options here, we could:
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


void Controller::draw() {

}

void Controller::init() {

}

Controller::Controller(Level *level, Player *player) {
    mLevel = level;
    mPlayer = player;
}
