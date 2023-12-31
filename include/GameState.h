#pragma once
#include "Player.h"
#include "Level.h"
#include <string>
#include "graphics.h"


class GameState {
private:
    class Player* mPlayer = nullptr;
    class Level* mCurrentLevel;
    static GameState* mUniqueInstance;

    GameState();

public:
    bool mDebugging = false;
    // TODO: Make player a friendly class
    float mGlobalOffsetX = 0.0f;
    float mGlobalOffsetY = 0.0f;

    void update(float dt);
    void draw();
    void init();
    static GameState* getInstance();
    ~GameState();

    class Player* getPlayer() {return mPlayer;}
};
