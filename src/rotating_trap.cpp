#pragma once

#include "rotating_trap.h"
#include <sstream>
#include <cmath>
#include <iostream>

void RotatingTrap::update(float dt) {

    StaticObject::update(dt);

    // Increment the rotation angle based on the rotation speed
    current_rotation_angle += rotation_speed * dt;
    std::cout << current_rotation_angle << std::endl;

    if (current_rotation_angle > max_left_rotation_angle) {
        // If it exceeds, start rotating in the opposite direction
        std::cout << "Angle " << current_rotation_angle << "exceeded LEFT rotation angle" << std::endl;
        rotation_speed = -rotation_speed;
    }

    else if (current_rotation_angle < max_right_rotation_angle) {
        // If it exceeds in the opposite direction, reverse again
        std::cout << "Angle " << current_rotation_angle << "exceeded RIGHT direction rotation angle" << std::endl;
        rotation_speed = -rotation_speed;
    }

    rotate(current_rotation_angle);

}

void RotatingTrap::draw() {

    // Draw center
    graphics::Brush br;
    br.fill_opacity = 1.0f;
    graphics::drawRect(center_x, center_y, 0.5f, 0.5f, br);
    graphics::drawLine(center_x, center_y, m_pos_x, m_pos_y, br);
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
    center_x = x;
    center_y = y;

    radius = rad;
    current_rotation_angle = 0.0f;
    rotation_speed = speed;
    max_left_rotation_angle = max_left;
    max_right_rotation_angle = max_right;
}

std::string RotatingTrap::to_string() const {
    std::ostringstream oss;
    oss << "\"Spikes\"" << " " << m_pos_x << " " << m_pos_y << " " << m_width << " " << m_height << " " << m_asset_path;
    return oss.str();
}
