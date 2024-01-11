#include "dynamic_object.h"

void DynamicObject::update(float dt) {

}

void DynamicObject::draw() {

    if (!hidden) {
        StaticObject::draw();
    }
}

void DynamicObject::init() {
    m_pos_x = init_x;
    m_pos_y = init_y;
    show();
    StaticObject::init();
}

DynamicObject::DynamicObject(float x, float y, float w, float h, const std::string& assetName) 
    : StaticObject(x, y, w, h, assetName)
{
    init_x = x;
    init_y = y;
    hidden = false;
}

void DynamicObject::hide() {
    hidden = true;
}

void DynamicObject::show() {
    hidden = false;
}