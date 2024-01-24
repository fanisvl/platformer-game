#pragma once
#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"
#include <vector>

class StaticObject : public GameObject, public Box {
protected:
    std::string m_asset_path;
    graphics::Brush m_brush;
    graphics::Brush m_brush_debug;

public:
    void update(float dt) override;
    void draw() override;
    void init() override;
    StaticObject(float x, float y, float w, float h, const std::string& assetName);
    virtual std::string StaticObject::to_string() const;
    StaticObject() {};
};