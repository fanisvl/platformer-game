#include "animated_object.h"

void AnimatedObject::init() {
}
void AnimatedObject::LoadAssets(std::string assetName,float fill_opacity,float outline_opacity) {
	m_brush_object.fill_opacity = fill_opacity;
	m_brush_object.outline_opacity = outline_opacity;
	m_brush_object.texture = m_state->getFullAssetPath("player\\walk_right\\WizardWalk00.png");
	for (int i = 0; i <= 9; ++i) {
		m_sprites.push_back(m_state->getFullAssetPath("player\\walk_right\\WizardWalk0" + std::to_string(i) + ".png"));
		b_sprites.push_back(m_state->getFullAssetPath("player\\walk_left\\WizardWalkLeft0" + std::to_string(i) + ".png"));
		std::cout << "Right full" << std::endl;
	}
	for (int i = 0; i <= 9; ++i) {
		std::cout << "left full" << std::endl;
		m_sprites.push_back(m_state->getFullAssetPath("player\\walk_right\\WizardWalk1" + std::to_string(i) + ".png"));
		b_sprites.push_back(m_state->getFullAssetPath("player\\walk_left\\WizardWalkLeft1" + std::to_string(i) + ".png"));
	}
}
void AnimatedObject::draw(float pos_x, float pos_y, AnimationType current_animation) {
	switch (current_animation) {
	case Right:
		if (!m_sprites.empty()) {
			// Calculate the raw index
			int rawIndex = (int)fmod(100.0f - pos_x * 9.0f, m_sprites.size());

			// Use modulo to wrap the index within the bounds of m_sprites
			int spriteIndex = (rawIndex + m_sprites.size()) % m_sprites.size();
			std::cout << "sprite indexRight: " << spriteIndex << std::endl;
			m_brush_object.texture = m_sprites[spriteIndex];
			break;
		}
	
	case Left:
		if (!b_sprites.empty()) {
			// Calculate the raw index
			int rawIndex = (int)fmod(100.0f - pos_x * 9.0f, b_sprites.size());

			// Use modulo to wrap the index within the bounds of m_sprites
			int spriteIndex = (rawIndex + b_sprites.size()) % b_sprites.size();
			std::cout << "sprite indexLeft: " << spriteIndex << std::endl;
			m_brush_object.texture = b_sprites[spriteIndex];
			break;
		}
	}
}

AnimatedObject::AnimatedObject() {

}