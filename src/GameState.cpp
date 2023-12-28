#include "GameState.h"

void GameState::update(float dt) {
    if (mPlayer) mPlayer->update(dt);
}

void GameState::draw() {

    // Draw Background
    graphics::Brush br;
    br.texture = std::string(ASSET_PATH) + "city_background.png";
    graphics::drawRect(CANVAS_WIDTH/2.0f, CANVAS_HEIGHT/2.0f, CANVAS_WIDTH, CANVAS_HEIGHT, br);

    // Draw mPlayer
    if (mPlayer) mPlayer->draw();
}


void GameState::init() {

}

GameState::GameState() {
    if (!mPlayer) mPlayer = new Player("player1");
}

GameState::~GameState() {
    if (mPlayer) delete mPlayer;
}

GameState* GameState::getInstance() {
    if (mUniqueInstance == nullptr) mUniqueInstance = new GameState();
    return mUniqueInstance;
}

GameState* GameState::mUniqueInstance = nullptr;

