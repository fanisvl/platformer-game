#include "graphics.h"
#include "GameState.h"
#include "config.h"

void update(float ms) {
    GameState::getInstance()->update(ms);
}

void draw() {
    GameState::getInstance()->draw();
}

void init() {
    GameState::getInstance()->init();
}

int main() {

    // Window
    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game");
    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    // Draw & Update setup
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    // Library starts calling update & draw
    graphics::startMessageLoop();

    return 0;
}