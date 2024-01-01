#include "GameObject.h"
#include "GameState.h"

GameObject::GameObject()
    : mState(GameState::getInstance()), mId(mNextId++){};

int GameObject::mNextId = 1;