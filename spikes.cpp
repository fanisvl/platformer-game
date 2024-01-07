#include "spikes.h"

void Spikes::update(float dt) {

}

void Spikes::draw() {
    float x = m_pos_x + m_state->m_global_offset_x;
    float y = m_pos_y + m_state->m_global_offset_y;
    graphics::drawRect(x, y, 1.0f * m_width, 1.0f * m_height, m_brush);

    if (m_state->m_debugging) {
        graphics::drawRect(x, y, m_width, m_height, m_brush_debug);
    }
}

void Spikes::init() {
    m_brush.outline_opacity = 0.0f;
    m_brush.texture = m_state->getFullAssetPath(m_asset_path);
}

Spikes::Spikes(float x, float y, float w, float h, const std::string& asset) {
    m_pos_x = x;
    m_pos_y = y;
    m_width = w;
    m_height = h;
    m_asset_path = asset;
}