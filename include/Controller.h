#pragma once
#include "GameObject.h"
#include "Player.h"
#include "GameState.h"
#include "graphics.h"

enum MoveDirection {
    RIGHT,
    LEFT,
    UP,
    DOWN,
};


class Controller : public GameObject {

    Level* mLevel;
    Player* mPlayer;
    MoveDirection direction;
    bool intersectDown = false;
    bool intersectUp = false;
    bool intersectRight = false;
    bool intersectLeft = false;

public:
    void update(float dt) override;
    void draw() override;
    void init() override;
    Controller(Level* level, Player* player);
    void checkCollisions();

};