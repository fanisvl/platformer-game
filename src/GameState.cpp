#include "GameState.h"

void GameState::update(float dt) {
    if (player) player->update();
}

void GameState::draw() {

    // Draw Background
    graphics::Brush br;
    br.texture = std::string(ASSET_PATH) + "city_background.png";
    graphics::drawRect(CANVAS_WIDTH/2.0f, CANVAS_HEIGHT/2.0f, CANVAS_WIDTH, CANVAS_HEIGHT, br);

    // Draw Player
    if (player) {
        player->draw();
    }
}


void GameState::init() {

}

GameState::GameState() {
    if (!player) {
        player = new Player();
    }
}

GameState::~GameState() {
    if (player) delete player;
}

GameState* GameState::getInstance() {
    if (mUniqueInstance == nullptr) mUniqueInstance = new GameState();
    return mUniqueInstance;
}

std::string GameState::getAssetDir() {
    return ASSET_PATH;
}

std::string GameState::getFullAssetPath(const std::string &asset) {
    return ASSET_PATH + asset;
};

GameState* GameState::mUniqueInstance = nullptr;

