#include "spikes.h"

void Spikes::update(float dt) {
    StaticBlock::update(dt);

}

void Spikes::draw() {
    StaticBlock::draw();
}

void Spikes::init() {

    StaticBlock::init();

    // Adjust hitbox
    m_pos_y += 0.25f;
    m_height /= 2.0f;
}

Spikes::Spikes(float x, float y, float w, float h, const std::string& asset) 
    : StaticBlock(x, y, w, h, asset)
{
    is_deadly = true;
}