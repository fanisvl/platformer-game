#pragma once
#include "GameObject.h"
#include "Player.h"
#include "GameState.h"
#include "graphics.h"

class Controller : public GameObject {

    Level* mLevel;
    Player* mPlayer;

public:
    void update(float dt) override;
    void draw() override;
    void init() override;
    Controller(Level* level, Player* player);

};