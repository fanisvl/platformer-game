#include "gameobject.h"

int GameObject::m_next_id = 1;

GameObject::GameObject()
	: m_id(m_next_id++), m_state(GameState::getInstance())
{

}
