#pragma once
#include "Player.h"
#include <string>
#include "graphics.h"


class GameState {
private:
    Player* player = nullptr;
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
};
