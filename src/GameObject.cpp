#include "GameObject.h"
#include "GameState.h"

GameObject::GameObject(const std::string& name)
    : mName(name), mState(GameState::getInstance()), mId(mNextId++){};

int GameObject::mNextId = 1;