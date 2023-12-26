#include "../sgg/include/graphics.h"
#include "../include/Game.h"

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
    graphics::createWindow(1200, 600, "Tutorial");
    graphics::setCanvasSize(1000, 500);
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