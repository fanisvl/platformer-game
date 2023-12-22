#include "../sgg/include/graphics.h"
#include "Game.h"

void update(float ms) {
    Game* game = graphics::getUserData();
}

void draw() {

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