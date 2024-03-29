#include "moving_enemy.h"
#include "player.h"
#include <utility>
#include <sstream>

void MovingEnemy::init() {
	AnimatedObject::loadMovingEnemyAssets();
	AnimatedObject::init();
	DynamicObject::init();	
	
}

void MovingEnemy::update(float dt) {
	chasePlayer();
}

void MovingEnemy::draw() {
	if (!hidden) {
		AnimatedObject::animate(m_pos_x, m_pos_y, current_animation);
		m_animation_brush.outline_opacity = 0.0f;
		graphics::drawRect(m_pos_x, m_pos_y, 1.0f, 1.0f, m_animation_brush);
	}

	if (GameObject::m_state->m_debugging) {
		graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_brush_debug);
	}
}

void MovingEnemy::handleCollision(CollisionType type) {
	if (!hidden) {
		switch (type) {
		case SIDEWAYS:
			// kill player
			GameObject::m_state->playerDeath();
			break;

		case DOWNWARDS:
			hide();
			break;
		}
	}
}

void MovingEnemy::chasePlayer() {

	// Get player position
	std::pair<float, float> player_xy = { GameObject::m_state->getPlayer()->getPositionXY() };
	float player_x = player_xy.first;
	float player_y = player_xy.second;

	// Vertical threshold allows the enemy to keep chasing the player even if they're jumping over them.
	float verticalThreshold = 1.5f;

	// If the player is at the same horizontal level
	// The enemy will start moving towards the player's x position.

	float changeDirectionBuffer = 0.05f; // Don't change direction immediately, wait until buffer for better animations
	if (player_y >= (m_pos_y - verticalThreshold) && player_y <= (m_pos_y + verticalThreshold)) {

		float chaseSpeed = 0.025f;

		if (m_pos_x + changeDirectionBuffer < player_x && withinRightBoundary()) {
			m_pos_x += chaseSpeed;
			current_animation = WalkRight;
		}

		else if (m_pos_x - changeDirectionBuffer > player_x && withinLeftBoundary()) {
			m_pos_x -= chaseSpeed;
			current_animation = WalkLeft;
		}
	}

	else if (player_x > m_pos_x) {
		current_animation = IdleRight;
	}

	else if (player_x < m_pos_x) {
		current_animation = IdleLeft;
	}
}	

bool MovingEnemy::withinRightBoundary() {
	if (m_pos_x + 0.05f > m_right_boundary) return false;
	return true;
}

bool MovingEnemy::withinLeftBoundary() {
	if (m_pos_x - 0.05f < m_left_boundary) return false;
	return true;
}

std::string MovingEnemy::to_string() const
{
	std::ostringstream oss;
	oss << "\"MovingEnemy\"" << " " << m_pos_x << " " << m_pos_y << " " << m_width << " " << m_height << " " << m_asset_path << " " << m_left_boundary << " " << m_right_boundary;
	return oss.str();
}

MovingEnemy::MovingEnemy(float x, float y, float w, float h, const std::string& assetName) : DynamicObject(x, y, w, h, assetName) {
	// If no boundaries are defined, the enemy doesn't move from their initial position.
	m_left_boundary = init_x;
	m_right_boundary = init_x;
}

MovingEnemy::MovingEnemy(float x, float y, float w, float h, const std::string& assetName, float left_boundary, float right_boundary) : DynamicObject(x, y, w, h, assetName) {
	m_left_boundary = left_boundary;
	m_right_boundary = right_boundary;
}