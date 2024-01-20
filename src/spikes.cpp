#include "spikes.h"

void Spikes::update(float dt) {
    StaticObject::update(dt);

}

void Spikes::draw() {
    StaticObject::draw();
}

void Spikes::init() {

    StaticObject::init();

    // Adjust hitbox
   
}

void Spikes::handleCollision(CollisionType type) {
    m_state->playerDeath();
}

Spikes::Spikes(float x, float y, float w, float h, const std::string& asset) 
    : StaticObject(x, y, w, h, asset)
{
}