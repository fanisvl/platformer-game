#include "player.h"
#include "util.h"
#include <cmath>
#include <iomanip>
#include <sstream>

void Player::update(float dt)
{
	float delta_time = dt / 1000.0f;

	movePlayer(dt);
	// update offset for other game objects
	GameObject::update(dt);

	if (graphics::getKeyState(graphics::SCANCODE_8)) {
		m_points++;
		std::cout << "Points: " << m_points << std::endl;
	}

}

void Player::init()
{
	AnimatedObject::loadPlayerAssets();
	AnimatedObject::init();
	current_animation = IdleRight;
	// Adjust width for finer collision detections
	m_width = 0.5f;
	m_points = 0;
}

void Player::draw()
{
	AnimatedObject::animate(m_pos_x, m_pos_y, current_animation);
	graphics::drawRect(m_pos_x, m_pos_y, 2.0f, 2.0f, m_animation_brush);
    if (GameObject::m_state->m_debugging)
        debugDraw();
}

void Player::debugDraw()
{
	graphics::setScale(1.0f, 1.0f);
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 1, 0.1f, 0);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, debug_brush);
	
	char s[20];
	sprintf(s,"(%5.2f, %5.2f)", m_pos_x, m_pos_y);
	SETCOLOR(debug_brush.fill_color, 1, 0, 0);
	debug_brush.fill_opacity = 1.0f;
	graphics::drawText(m_pos_x - 0.4f, m_pos_y - 0.6f, 0.15f, s, debug_brush);
}

void Player::movePlayer(float dt)
{
	float delta_time = dt / 1000.0f;
	
	// Acceleration-based velocity
	float move_direction = 0.0f;
	if (graphics::getKeyState(graphics::SCANCODE_A)) {
		current_animation = WalkLeft;
		move_direction -= 1.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_D)) {
		current_animation = WalkRight;
		move_direction = 1.0f;
	}
	if (!graphics::getKeyState(graphics::SCANCODE_A) && !graphics::getKeyState(graphics::SCANCODE_D)) {
		if (current_animation == WalkRight) {
			current_animation = IdleRight;
		}
		else if(current_animation == WalkLeft){
			current_animation = IdleLeft;
		}
	}
	
	// Ensure that m_vx doesn't exceed m_max_velocity
	m_vx = std::min<float>(m_max_velocity, m_vx + delta_time * move_direction * m_accel_horizontal);
	m_vx = std::max<float>(-m_max_velocity, m_vx);

	// friction
	m_vx -= 0.2f * m_vx / (0.1f + fabs(m_vx));

	// apply static friction threshold
	if (fabs(m_vx) < 0.01f)
		m_vx = 0.0f;

	// adjust horizontal position
	m_pos_x += m_vx * delta_time;

	// jump only when not in flight:
	if (m_vy == 0.0f) {
		float jump_multiplier = 0.02;
		m_vy -= (graphics::getKeyState(graphics::SCANCODE_W) ? m_accel_vertical : 0.0f) * jump_multiplier;
	}

	// add gravity
	m_vy += delta_time * m_gravity;

	// adjust vertical position
	m_pos_y += m_vy * delta_time;

}

void Player::setPosition(float x, float y) {
	m_pos_x = x;
	m_pos_y = y;
}

void Player::handleCollision(CollisionType type, float offset) {

	switch (type) {
	case SIDEWAYS:
		m_pos_x += offset;
		m_vx = 0.0f;
		break;
	case DOWNWARDS:
		m_pos_y += offset;
		m_vy = 0.0f;
		break;
	case UPWARDS:
		m_pos_y -= offset;
		m_vy =	0.01f;
		break;	
	}
}

std::pair<float, float> Player::getPositionXY() {
	return std::make_pair(m_pos_x, m_pos_y);
}

void Player::gainPoint() {
	m_points += 1;
}