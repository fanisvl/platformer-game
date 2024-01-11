#include "background.h"

void Background::update(float dt) {
}

void Background::init() {
    m_background_path = m_state->getFullAssetPath("background\\forrest.png");
    m_brush_background.texture = m_background_path;
    m_brush_background.outline_opacity = 0.0f;
}

void Background::draw() {
    float w = CANVAS_WIDTH;
    float h = CANVAS_HEIGHT;
    float offset_x = m_state->m_global_offset_x / 2.0f + w/2.0f;
    float offset_y = m_state->m_global_offset_y / 2.0f + h/2.0f;

    //Draw Background
    graphics::drawRect(offset_x, offset_y, 2.0f*w, 2.0f*h, m_brush_background);
}
