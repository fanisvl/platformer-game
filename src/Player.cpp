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
    graphics::drawRect(mPosX, mPosY, mWidth, mHeight, mPlayerBrush);
    if (mState->mDebugging) {
        graphics::drawRect(mPosX, mPosY, mWidth, mHeight, mPlayerBrushDebug);
    }
}

void Player::init() {

    // Initialize player position & speed
    mPosX = CANVAS_WIDTH / 2.0f;
    mPosY = CANVAS_HEIGHT / 2.0f;
    mWidth = 70.0f;
    mHeight = 70.0f;
    speed = 0.5f;

    // Initialize brush to draw player
    mPlayerBrush.texture = std::string(ASSET_PATH) + "ghost.png";
    mPlayerBrush.outline_opacity = 0.0f;

    // Initialize Debug brush
    mPlayerBrushDebug.fill_opacity = 0.1f;
    SETCOLOR(mPlayerBrushDebug.fill_color, 0.5f, 0.0f, 0.0f);
    SETCOLOR(mPlayerBrushDebug.outline_color, 1.0f, 0.0f, 0.0f);
}
