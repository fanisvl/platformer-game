#pragma once

#include "Player.h"

class Game {

    Player* player = nullptr;

public:
    void update();
    void draw();
    void init();
    Game();
    ~Game();
};
