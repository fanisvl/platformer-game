#pragma once
#include "static_object.h"

class DynamicObject : public StaticObject {
protected:
    float init_x;
    float init_y;
    bool hidden;
public:
    class Projectile* m_projectile = nullptr;
public:
    void update(float dt) override;
    void draw() override;
    void init() override;
    DynamicObject(float x, float y, float w, float h, const std::string& assetName);
    void reset();
    void hide();
    void show();
};