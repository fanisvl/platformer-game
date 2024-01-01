#include "GameState.h"
#include "Level.h"
#include "Player.h"

void GameState::update(float dt) {

    // Don't update when window resizes
    if (dt>500) return;

    if (mCurrentLevel) mCurrentLevel->update(dt);
    if (mPlayer) mPlayer->update(dt);

    mDebugging = graphics::getKeyState(graphics::SCANCODE_0);
}

void GameState::draw() {
    if (mCurrentLevel) mCurrentLevel->draw();
    if (mPlayer) mPlayer->draw();
}


void GameState::init() {
    if (!mCurrentLevel) mCurrentLevel = new Level();
    mCurrentLevel->init();

    if (!mPlayer) mPlayer = new Player();
    mPlayer->init();

    graphics::preloadBitmaps(ASSET_PATH);
    // Font
    //    graphics::setFont(std::string(ASSET_PATH) + "font.ttf");
}

GameState::GameState() {
}

GameState::~GameState() {
    if (mPlayer) delete mPlayer;
}

GameState* GameState::getInstance() {
    if (mUniqueInstance == nullptr) mUniqueInstance = new GameState();
    return mUniqueInstance;
}

GameState* GameState::mUniqueInstance = nullptr;

