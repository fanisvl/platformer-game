#include "GameObject.h"
#include "GameState.h"

int GameObject::mNextId = 1;

GameObject::GameObject()
    : mState(GameState::getInstance()), mId(mNextId++){};

