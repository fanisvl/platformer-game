#include "moving_enemy.h"
#include "player.h"
#include <utility>
#include <sstream>

void MovingEnemy::init() {
	DynamicObject::init();	
}

void MovingEnemy::update(float dt) {
	chasePlayer();
}

void MovingEnemy::draw() {
	if (!hidden) {
		AnimatedObject::animate(m_pos_x, m_pos_y, current_animation);
	}
	DynamicObject::draw();
}

void MovingEnemy::handleCollision(CollisionType type) {
	if (!hidden) {
		switch (type) {
		case SIDEWAYS:
			// kill player
			GameObject::m_state->playerDeath();
			break;
		case DOWNWARDS:
			// kill self
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
	if (player_y >= (m_pos_y - verticalThreshold) && player_y <= (m_pos_y + verticalThreshold)) {
		if (m_pos_x < player_x && withinRightBoundary()) m_pos_x += 0.05f;
		if (m_pos_x > player_x && withinLeftBoundary()) m_pos_x -= 0.05f;
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