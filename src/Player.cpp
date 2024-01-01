#include <cmath>
#include "Player.h"
#include "GameState.h"
#include "graphics.h"

void Player::update(float dt) {


    // WASD Keyboard Controls
    if (graphics::getKeyState(graphics::SCANCODE_A)) {
        mPosX -= speed * graphics::getDeltaTime();
    }

    if (graphics::getKeyState(graphics::SCANCODE_D)) {
        mPosX += speed * graphics::getDeltaTime();
    }

    if (graphics::getKeyState(graphics::SCANCODE_W)) {
        mPosY -= speed * graphics::getDeltaTime();
    }

    if (graphics::getKeyState(graphics::SCANCODE_S)) {
        mPosY += speed * graphics::getDeltaTime();
    }

    // Update Global Offset
    mState->mGlobalOffsetX = CANVAS_WIDTH / 2.0f - mPosX;
    mState->mGlobalOffsetY = CANVAS_HEIGHT / 2.0f - mPosY;

    // Boundaries
    if (mPosX < 0) mPosX = 0;
    if (mPosX > CANVAS_WIDTH) mPosX = CANVAS_WIDTH;
    if (mPosY < 0) mPosY = 0;
    if (mPosY > CANVAS_HEIGHT) mPosY = CANVAS_HEIGHT;

}

void Player::draw() {
    graphics::drawRect(mPosX, mPosY, 70, 70, mPlayerBrush);
}

void Player::init() {

    // Initialize player position & speed
    mPosX = 100.0f;
    mPosY = CANVAS_HEIGHT-100.0f;
    speed = 0.5f;

    // Initialize brush to draw player
    mPlayerBrush.texture = std::string(ASSET_PATH) + "ghost.png";
    mPlayerBrush.outline_opacity = 0.0f;
}
