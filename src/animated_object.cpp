#include "animated_object.h"
#include <filesystem>

void AnimatedObject::init() {
	m_animation_brush.fill_opacity = 1.0f;
	m_animation_brush.outline_opacity = 0.0f;

	timer = 0.0f;  // Keeps track of elapsed time
	frame_index = 0;

}
void AnimatedObject::loadPlayerAssets() {
	m_animation_brush.texture = "assets/player/idle/idle00.png";
	fillVector(walk, "assets/player/walk");
	fillVector(idle, "assets/player/idle");
}

void AnimatedObject::loadMovingEnemyAssets() {
	m_animation_brush.texture = "assets/fireWorm/idle/tile (1).png";
	fillVector(walk, "assets/fireWorm/walk");
	fillVector(idle, "assets/fireWorm/idle");
}

void AnimatedObject::loadProjectileEnemyAssets() {
	m_animation_brush.texture = "assets/projectileEnemy/idle/idle (1).png";
	fillVector(idle, "assets/projectileEnemy/idle");
}

void AnimatedObject::loadCoinAssets() {
	m_animation_brush.texture = "assets/coins/tile000.png";
	fillVector(m_rotation, "assets/coins");
}

void AnimatedObject::fillVector(std::vector<std::string>& vector, std::string asset_folder) {
	

	try {
		for (const auto& entry : std::filesystem::directory_iterator(asset_folder)) {
			// Convert std::filesystem::path to std::string
			std::string filename = entry.path().string();
			vector.push_back(filename);
			std::cout << "Pushing: " << filename << std::endl;
		}
	}

	catch (const std::filesystem::filesystem_error& ex) {
		std::cerr << "Error accessing the directory: " << ex.what() << std::endl;
	}

}

void AnimatedObject::animate(float pos_x, float pos_y, AnimationType current_animation) {
	switch (current_animation) {

	// Walk & ProjectileAttack both call animateAction()
	case WalkRight:
		// setScale changes the direction the player looks (1 right, -1 left)
		graphics::setScale(1.0f, 1.0f); 
		animateAction(walk, pos_x);
		break;

	case WalkLeft:
		graphics::setScale(-1.0f, 1.0f); 
		animateAction(walk, pos_x);
		break;
	case IdleRight:
		graphics::setScale(1.0f, 1.0f); 
		animateIdle(idle);
		break;
	case IdleLeft:
		graphics::setScale(-1.0f, 1.0f);
		animateIdle(idle);
		break;
	case Rotation:
		graphics::setScale(-1.0f, 1.0f);
		animateIdle(m_rotation);
		break;
	}
}

void AnimatedObject::animateAction(const std::vector<std::string>& vector, float pos_x) {
	if (!vector.empty()) {
		// Calculate the raw index
		int rawIndex = (int)fmod(100.0f - pos_x * 9.0f, vector.size());

		// Use modulo to wrap the index within the bounds of m_sprites
		int spriteIndex = (rawIndex + vector.size()) % vector.size();
		m_animation_brush.texture = vector[spriteIndex];
	}

}

void AnimatedObject::animateIdle(const std::vector<std::string>& vector) {
	float time_unit = 0.1f;  // added to the timer every time the function is called to delay the display of the next frame
	float total_frame_duration = 0.5f; // variable to display each frame every time the timer reaches 0.5f

	if (!vector.empty()) { // checks if the vector is empty
		
		timer += time_unit; // adds the time unit (0.1f) to the timer
		
		// checks if the timer is greater or equal to the set frame duration ensuring that each frame is displayed every time the timer reaches 0.5f
		if (timer >= total_frame_duration) {

			// Increment the index for the next frame and then use modulo to reset it back to zero when the index exceeds the size of the vector
			frame_index = (frame_index + 1) % vector.size();

			// Display the current frame 
			m_animation_brush.texture = vector[frame_index];

			// Resets the timer by subtracting the total frame duration
			timer -= total_frame_duration;
		}
	}
}