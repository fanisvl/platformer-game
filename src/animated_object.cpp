#include "animated_object.h"
#include <filesystem>

void AnimatedObject::init() {
	m_animation_brush.fill_opacity = 1.0f;
	m_animation_brush.outline_opacity = 0.0f;

}
void AnimatedObject::loadPlayerAssets() {
	fillVector(walk_right, "assets/player/walk_right/");
	fillVector(walk_left, "assets/player/walk_left/");
	fillVector(idle_right, "assets/player/idle_right/");
	fillVector(idle_left, "assets/player/idle_left/");
}

void AnimatedObject::loadMovingEnemyAssets() {

}

void AnimatedObject::fillVector(std::vector<std::string>& vector, std::string asset_folder) {
	

	try {
		for (const auto& entry : std::filesystem::directory_iterator(asset_folder)) {
			// Convert std::filesystem::path to std::string
			std::string filename = entry.path().string();
			std::cout << "Pushing to animation vector: " + filename << std::endl;
			vector.push_back(filename);
		}
	}

	catch (const std::filesystem::filesystem_error& ex) {
		std::cerr << "Error accessing the directory: " << ex.what() << std::endl;
	}

}

void AnimatedObject::animate(float pos_x, float pos_y, AnimationType current_animation) {
	switch (current_animation) {
	case Right:
		animateWalk(walk_right, pos_x);
		break;
	case Left:
		animateWalk(walk_left, pos_x);
		break;
	case IdleRight:
		animateIdle(idle_right);
		break;
	case IdleLeft:
		animateIdle(idle_left);
		break;
	}
}

void AnimatedObject::animateWalk(std::vector<std::string> vector_name,float pos_x) {
	if (!vector_name.empty()) {
		// Calculate the raw index
		int rawIndex = (int)fmod(100.0f - pos_x * 9.0f, vector_name.size());

		// Use modulo to wrap the index within the bounds of m_sprites
		int spriteIndex = (rawIndex + vector_name.size()) % vector_name.size();
		m_animation_brush.texture = vector_name[spriteIndex];
	}

}

#include <iostream>
void AnimatedObject::animateIdle(std::vector<std::string>& vector_name) {
	static float timer = 0.0f;  // Keeps track of elapsed time
	static int frame_index = 0; // Keeps track of the index
	float time_unit = 0.1f;  // is added to the timer every time the function is called to delay the display of the next frame
	float frame_duration = 0.5f; // variable to display each frame every time the timer reaches 0.5f
	// is added to the timer every time the function is called to delay the display of the next frame
	if (!vector_name.empty()) { // checks if the vector is empty
		
		timer += time_unit; //adds the time unit (0.1f) to the timer
		
		// checks if the timer is greater or equal to the set frame duration ensuring that each frame is displayed every time the timer reaches 0.5f
		if (timer >= frame_duration) {
			// display the current frame 
			m_animation_brush.texture = vector_name[frame_index];
			//increment the index for the next frame and then use modulo to reset it back to zero when the index exceeds the size of the vector
			frame_index = (frame_index + 1) % vector_name.size();
			// Resets the timer by subtracting the frame duration
			timer -= frame_duration;
		}
	}
}
AnimatedObject::AnimatedObject() {

}