#pragma once

#include "rotating_trap.h"
#include <sstream>
#include <cmath>
#include <iostream>
#include "config.h"

void RotatingTrap::update(float dt) {

    StaticObject::update(dt);

    // Increment the rotation angle based on the rotation speed
    current_rotation_angle += rotation_speed * dt;

    if (current_rotation_angle > max_left_rotation_angle) {
        // If it exceeds, start rotating in the opposite direction
        current_rotation_angle = max_left_rotation_angle;
        rotation_speed = -rotation_speed;
    }

    else if (current_rotation_angle < max_right_rotation_angle) {
        // If it exceeds in the opposite direction, reverse again
        current_rotation_angle = max_right_rotation_angle;
        rotation_speed = -rotation_speed;
    }

    rotate(current_rotation_angle);

}

void RotatingTrap::draw() {

    graphics::Brush br;
    br.fill_opacity = 1.0f;
    br.outline_opacity = 1.0f;
    SETCOLOR(br.fill_color, 0.5f, 0.5f, 0.5f);
    SETCOLOR(br.outline_color, 0.5f, 0.5f, 0.5f);

    // Draw base and rope
    graphics::drawRect(center_x, center_y, 0.5f, 0.5f, br);
    graphics::drawLine(center_x, center_y, m_pos_x, m_pos_y, br);

    // Draw spikes
    StaticObject::draw();
}

void RotatingTrap::init() {

    StaticObject::init();


}

void RotatingTrap::handleCollision(CollisionType type) {
    m_state->playerDeath();
}

void RotatingTrap::rotate(float angle) {

    m_pos_x = center_x + radius * std::cos(angle);
    m_pos_y = center_y + radius * std::sin(angle);
}

RotatingTrap::RotatingTrap(float x, float y, float w, float h, const std::string& asset, float max_left, float max_right, float rad, float speed)
    : StaticObject(x, y, w, h, asset)
{
    // Adjust hitbox
    m_width *= 0.9f;
    m_height *= 0.9f;

    center_x = x;
    center_y = y;

    radius = rad;
    rotation_speed = speed;
    max_left_rotation_angle = max_left;
    max_right_rotation_angle = max_right;

    // Initialize the rotation angle randomly
    current_rotation_angle = rand() % int((max_left_rotation_angle - max_right_rotation_angle) + 1) + max_right_rotation_angle;
}

std::string RotatingTrap::to_string() const {
    std::ostringstream oss;
    oss << "\"RotatingTrap\"" << " " << center_x << " " << center_y << " " << m_width << " " << m_height << " " << m_asset_path << " " << max_left_rotation_angle << " " << max_right_rotation_angle << " " << radius << " " << rotation_speed;
    return oss.str();
}
