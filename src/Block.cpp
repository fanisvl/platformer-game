#include "Block.h"
#include "config.h"
#include "GameState.h"

void Block::update(float dt) {

}

void Block::draw() {
    float x = mPosX + mState->mGlobalOffsetX;
    float y = mPosY + mState->mGlobalOffsetY;
    graphics::drawRect(x, y, mWidth, mHeight, mBlockBrush);

    if (mState->mDebugging) {
        graphics::drawRect(x, y, mWidth, mHeight, mBlockBrushDebug);

    }
}

void Block::init() {

    // Normal Brush init
    mBlockBrush.outline_opacity = 0.0f;
    mBlockBrush.texture = std::string(ASSET_PATH) + mAssetName;

    // Debug Brush init
    mBlockBrushDebug.fill_opacity = 0.1f;
    SETCOLOR(mBlockBrushDebug.fill_color, 0.2f, 1.0f, 0.0f);
    SETCOLOR(mBlockBrushDebug.outline_color, 0.5f, 1.0f, 0.2f);
}

Block::Block(float x, float y, float w, float h, const std::string &assetName) {
    mPosX = x;
    mPosY = y;
    mWidth = w;
    mHeight = h;
    mAssetName = assetName;
}
