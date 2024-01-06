#pragma once
#include <string>
#include "gameobject.h"
#include "sgg/graphics.h"

class Background : public GameObject {
    std::string m_ground_path;
    std::string m_background_path;
    graphics::Brush m_brush_background;
public:
    void update(float dt) override;
    void init() override;
    void draw() override;

};