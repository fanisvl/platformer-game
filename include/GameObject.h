#pragma once
#include <string>

class GameObject {

    static int mNextId;

protected:
    class GameState* mState;
    int mId = 0;
    bool mActive = true;

public:
    virtual void update(float dt) = 0;
    virtual void draw() = 0;
    virtual void init() = 0;

    GameObject();
    virtual ~GameObject() {};
    bool isActive() {return mActive;}
    void setActive(bool a) {mActive = a;}

};

