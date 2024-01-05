#include "block.h"
#include "config.h"
#include "gamestate.h"

void Block::update(float dt) {

}

void Block::draw() {

    graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_block_brush);

    if (mState->mDebugging) {
        graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_block_brush_debugk);
    }
}

void Block::init() {

    // Normal Brush init
    m_block_brush.outline_opacity = 0.0f;
    m_block_brush.texture = std::string(ASSET_PATH) + m_asset_name;

    // Debug Brush init
    m_block_brush_debug.fill_opacity = 0.1f;
    SETCOLOR(m_block_brush_debug.fill_color, 0.2f, 1.0f, 0.0f);
    SETCOLOR(m_block_brush_debug.outline_color, 0.5f, 1.0f, 0.2f);
}

Block::Block(float x, float y, float w, float h, const std::string &assetName) {
    m_pos_x = x;
    m_pos_y = y;
    m_width = w;
    m_height = h;
    m_asset_name = assetName;
}
