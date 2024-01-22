#include "background.h"
#include <iostream>

void Background::update(float dt) {
}

void Background::init() {
}

void Background::draw() {

    float w = CANVAS_WIDTH;
    float h = CANVAS_HEIGHT;

    //Draw Background
    graphics::drawRect(CANVAS_WIDTH / 2.0f, CANVAS_HEIGHT / 2.0f, 2.0f * w, 2.0f * h, m_brush_background);
}

Background::Background(std::string background) {
    m_background_path = m_state->getFullAssetPath(background);
    m_brush_background.texture = m_background_path;
}
