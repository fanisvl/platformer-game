#pragma once
#include "Player.h"
#include "Level.h"
#include <string>
#include "graphics.h"


class GameState {
private:
    class Player* mPlayer = nullptr;
    class Level* mCurrentLevel = nullptr;
    class Controller* mController = nullptr;
    static GameState* mUniqueInstance;

    GameState();

public:
    bool mDebugging = false;

    void update(float dt);
    void draw();
    void init();
    static GameState* getInstance();
    ~GameState();

    class Player* getPlayer() {return mPlayer;}
};
