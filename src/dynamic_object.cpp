#include "dynamic_object.h"

void DynamicObject::update(float dt) {

}

void DynamicObject::draw() {

    if (!hidden) {
        StaticBlock::draw();
    }
}

void DynamicObject::init() {
    show();
    StaticBlock::init();
}

DynamicObject::DynamicObject(float x, float y, float w, float h, const std::string& assetName) 
    : StaticBlock(x, y, w, h, assetName)
{
    hidden = false;
}

void DynamicObject::hide() {
    hidden = true;
}

void DynamicObject::show() {
    hidden = false;
}