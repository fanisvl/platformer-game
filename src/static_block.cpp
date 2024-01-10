#include "static_block.h"
#include "config.h"

void StaticBlock::update(float dt) {

}

void StaticBlock::draw() {

    float x = m_pos_x + m_state->m_global_offset_x;
    float y = m_pos_y + m_state->m_global_offset_y;
    graphics::drawRect(x, y, 1.0f*m_width, 1.0f*m_height, m_brush);

    if (m_state->m_debugging) {
        graphics::drawRect(x, y, m_width, m_height, m_brush_debug);
    }
}

void StaticBlock::init() {

    // Normal Brush init
    m_brush.outline_opacity = 0.0f;
    m_brush.texture = m_state->getFullAssetPath(m_asset_path);

    // Debug Brush init
    m_brush_debug.fill_opacity = 0.1f;
    SETCOLOR(m_brush_debug.fill_color, 0.2f, 1.0f, 0.0f);
    SETCOLOR(m_brush_debug.outline_color, 0.5f, 1.0f, 0.2f);
}

StaticBlock::StaticBlock(float x, float y, float w, float h, const std::string &assetName) : Box(x, y, w, h)
{
    m_asset_path = assetName;
}

