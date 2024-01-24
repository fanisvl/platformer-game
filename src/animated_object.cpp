#include "animated_object.h"

void AnimatedObject::init() {
}
void AnimatedObject::LoadAssets(std::string assetName,float fill_opacity,float outline_opacity) {
	m_brush_object.fill_opacity = fill_opacity;
	m_brush_object.outline_opacity = outline_opacity;
	m_brush_object.texture = m_state->getFullAssetPath("player\\walk_right\\WizardWalk00.png");
	FillVector(walk_right, "player\\walk_right\\WizardWalk");
	FillVector(walk_left, "player\\walk_left\\WizardWalkLeft");
	FillVector(idle_right, "player\\idle_right\\idleright");
	FillVector(idle_left, "player\\idle_left\\idleleft");
}

void AnimatedObject::draw(float pos_x, float pos_y, AnimationType current_animation) {
	switch (current_animation) {
	case Right:
		animate(walk_right, pos_x);
		break;
	case Left:
		animate(walk_left, pos_x);
		break;
	case IdleRight:
		animateIdle(idle_right);
		break;
	case IdleLeft:
		animateIdle(idle_left);
		break;
	}
}

void AnimatedObject::animate(std::vector<std::string> vector_name,float pos_x) {
	if (!vector_name.empty()) {
		// Calculate the raw index
		int rawIndex = (int)fmod(100.0f - pos_x * 9.0f, vector_name.size());

		// Use modulo to wrap the index within the bounds of m_sprites
		int spriteIndex = (rawIndex + vector_name.size()) % vector_name.size();
		m_brush_object.texture = vector_name[spriteIndex];
	}
}
void AnimatedObject::FillVector(std::vector<std::string>& vector, std::string asset) {
	for (int i = 0; i <= 9; ++i) {
		vector.push_back(m_state->getFullAssetPath(asset + std::to_string(0) + std::to_string(i) + ".png"));
	}
	for (int i = 0; i <= 9; ++i) {
		vector.push_back(m_state->getFullAssetPath(asset + std::to_string(1) + std::to_string(i) + ".png"));
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
			m_brush_object.texture = vector_name[frame_index];
			//increment the index for the next frame and then use modulo to reset it back to zero when the index exceeds the size of the vector
			frame_index = (frame_index + 1) % vector_name.size();
			// Resets the timer by subtracting the frame duration
			timer -= frame_duration;
		}
	}
}
AnimatedObject::AnimatedObject() {

}