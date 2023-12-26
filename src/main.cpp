#include "graphics.h"
#include "Game.h"
#include "config.h"

void update(float ms) {
    Game* game = reinterpret_cast<Game *> (graphics::getUserData());
    game->update();
}

void draw() {
    Game* game = reinterpret_cast<Game *> (graphics::getUserData());
    game->draw();
}

int main() {

    // Window
    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game");
    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    // Draw & Update setup
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    // Game object
    Game game;
    graphics::setUserData(&game);
    game.init();

    // Library starts calling update & draw
    graphics::startMessageLoop();

    return 0;
}