#include <cmath>
#include "Player.h"
#include "graphics.h"

void Player::update() {


    // WASD Keyboard Controls
    if (graphics::getKeyState(graphics::SCANCODE_A)) {
        posX -= speed * graphics::getDeltaTime() / 10.0f;
    }

    if (graphics::getKeyState(graphics::SCANCODE_D)) {
        posX += speed * graphics::getDeltaTime() / 10.0f;
    }

    if (graphics::getKeyState(graphics::SCANCODE_W)) {
        posY -= speed * graphics::getDeltaTime() / 10.0f ;
    }

    if (graphics::getKeyState(graphics::SCANCODE_S)) {
        posY += speed * graphics::getDeltaTime() / 10.0f;
    }

    // Boundaries
    if (posX < 0) posX = 0;
    if (posX > CANVAS_WIDTH) posX = CANVAS_WIDTH;
    if (posY < 0) posY = 0;
    if (posY > CANVAS_HEIGHT) posY = CANVAS_HEIGHT;

}

void Player::draw() {

    graphics::Brush br;
    br.texture = std::string(ASSET_PATH) + "ghost.png";
    br.outline_opacity = 0.0f;
    graphics::drawRect(posX, posY, 100, 100, br);

}

void Player::init() {

}
