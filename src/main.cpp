#include "graphics.h"
#include "GameState.h"
#include "config.h"

void update(float ms) {
    GameState* game = reinterpret_cast<GameState *> (graphics::getUserData());
    game->update();
}

void draw() {
    GameState* game = reinterpret_cast<GameState *> (graphics::getUserData());
    game->draw();
}

int main() {

    // Window
    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GameState");
    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    // Draw & Update setup
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    // GameState object
    GameState game;
    graphics::setUserData(&game);
    game.init();

    // Library starts calling update & draw
    graphics::startMessageLoop();

    return 0;
}