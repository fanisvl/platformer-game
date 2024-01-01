#include "Block.h"
#include "config.h"
#include "GameState.h"

void Block::update(float dt) {

}

void Block::draw() {
    float x = mPosX + mState->mGlobalOffsetX;
    float y = mPosY + mState->mGlobalOffsetY;
    graphics::drawRect(x, y, mWidth, mHeight, mBlockBrush);
}

void Block::init() {
    mBlockBrush.outline_opacity = 0.0f;
    mBlockBrush.texture = std::string(ASSET_PATH) + mAssetName;
}

Block::Block(float x, float y, float w, float h, const std::string &assetName) {
    mPosX = x;
    mPosY = y;
    mWidth = w;
    mHeight = h;
    mAssetName = assetName;
}
