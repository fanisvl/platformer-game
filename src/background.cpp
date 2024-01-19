#include "background.h"

void Background::update(float dt) {
}

void Background::init() {
    m_background_path = m_state->getFullAssetPath("background\\cave_background.png");
    m_brush_background.texture = m_background_path;
    m_brush_background.outline_opacity = 0.0f;
}

void Background::draw() {
    float w = CANVAS_WIDTH;
    float h = CANVAS_HEIGHT;

    //Draw Background
    graphics::drawRect(CANVAS_WIDTH / 2.0f, CANVAS_HEIGHT / 2.0f, 2.0f * w, 2.0f * h, m_brush_background);
}