#include "menu.h"
#pragma once

void Menu::init() {
	m_brush.fill_opacity = 1.0f;
	graphics::setFont("assets\\Roboto-Bold.ttf");

	if (m_background == nullptr) m_background = new Background("/background/forrest2.png");
}

void Menu::update(float dt) {

}

void Menu::draw() {
	m_background->draw();
}

void Menu::showTextMenu() {
	graphics::drawText(CANVAS_WIDTH / 2.0f, CANVAS_HEIGHT / 2.0f, 1.0f, "Press SPACE to play", m_brush);
	graphics::drawText(CANVAS_WIDTH / 2.0f, CANVAS_HEIGHT / 2.0f - 5.0f, 1.0f, "Press M to activate Level Maker", m_brush);
}
