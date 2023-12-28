#pragma once
#include <string>

class GameObject {

    static int mNextId;

protected:
    class GameState* mState;
    std::string mName;
    int mId = 0;
    bool mActive = true;

public:
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void init() = 0;

    GameObject(const std::string& name = "");
    virtual ~GameObject() {};
    bool isActive() {return mActive;}
    void setActive(bool a) {mActive = a;}

};

