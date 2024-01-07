#include "spikes.h"

void Spikes::update(float dt) {

}

void Spikes::draw() {

}

void Spikes::init() {

}

Spikes::Spikes(float x, float y, float w, float h, std::string asset) {
	Box(x, y, w, h);
	m_asset_path = asset;
}