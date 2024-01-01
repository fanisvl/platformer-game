#include "Block.h"
#include "config.h"

void Block::update(float dt) {

}

void Block::draw() {
    graphics::drawRect(mPosX, mPosY, mWidth, mHeight, mBlockBrush);
}

void Block::init() {
    mBlockBrush.texture = std::string(ASSET_PATH) + mAssetName;
}

Block::Block(float x, float y, float w, float h, std::string &assetName) {
    mPosX = x;
    mPosY = y;
    mWidth = w;
    mHeight = h;
    mAssetName = assetName;
}
