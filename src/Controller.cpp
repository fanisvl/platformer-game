#include "Controller.h"

void Controller::update(float dt) {

    float dx = 0.0f;
    float dy = 0.0f;

    // WASD Keyboard Controls
    // Determine dx. Speed is determined by the object moving (move method)
    // dx = direction * t * speed
    if (graphics::getKeyState(graphics::SCANCODE_A)) {
        dx = -1.0f * graphics::getDeltaTime();
    }

    if (graphics::getKeyState(graphics::SCANCODE_D)) {
        dx = +1.0f * graphics::getDeltaTime();

    }

    if (graphics::getKeyState(graphics::SCANCODE_W)) {
        dy = -1.0f * graphics::getDeltaTime();

    }

    if (graphics::getKeyState(graphics::SCANCODE_S)) {
        dy = +1.0f * graphics::getDeltaTime();
    }

    // Move player
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

}

void Controller::draw() {

}

void Controller::init() {

}

Controller::Controller(Level *level, Player *player) {
    mLevel = level;
    mPlayer = player;
}
