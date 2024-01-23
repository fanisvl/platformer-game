#include "spikes.h"
#include <sstream>


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

std::string Spikes::to_string() const {
        std::ostringstream oss;
        oss << "Spikes" << " " << m_pos_x << " " << m_pos_y << " " << m_width << " " << m_height << " " << m_asset_path;
        return oss.str();
}
