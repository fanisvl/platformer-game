#include <sgg/graphics.h>
#include "config.h"
#include "gamestate.h"

void draw()
{
    GameState::getInstance()->draw();
}

void update(float dt)
{
    GameState::getInstance()->update(dt);
}


int main(int argc, char** argv)
{
    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game");

    GameState::getInstance()->init();

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    graphics::setFont("assets\\Roboto-Bold.ttf");

    graphics::startMessageLoop();
	return 0;
}

