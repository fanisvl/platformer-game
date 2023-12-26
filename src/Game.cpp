#include <cmath>
#include "../include/Game.h"
#include "../include/config.h"
#include "../sgg/include/graphics.h"

void Game::update() {
}

void Game::draw() {
    graphics::Brush br;
    br.texture = std::string(ASSET_PATH) + "city_background.png";

    float bgOffset = CANVAS_WIDTH * sinf(graphics::getGlobalTime()/1000.0f) / 4;

    graphics::drawRect(CANVAS_WIDTH/2 + bgOffset, CANVAS_HEIGHT/2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
}


void Game::init() {

}
Game::Game() {

};
Game::~Game() {

};