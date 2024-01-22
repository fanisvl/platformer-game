#include "menu.h"
#include <iostream>
#pragma once

void Menu::init() {
	m_brush.fill_opacity = 1.0f;
	graphics::setFont("assets\\Roboto-Bold.ttf");

	if (m_background == nullptr) m_background = new Background("background/cave_background.png");
}

void Menu::update(float dt) {

	if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
		std::cout << "SPACE pressed" << std::endl;
		m_state->startNewGame();
	}
	else if (graphics::getKeyState(graphics::SCANCODE_M))  {
		std::cout << "M pressed" << std::endl;
		m_state->enterLevelMaker();
	}

}

void Menu::draw() {
	m_background->draw();
	showTextMenu();
}

void Menu::showTextMenu() {
	SETCOLOR(m_brush.fill_color, 255, 255, 255);
	graphics::drawText(6.0f, CANVAS_HEIGHT / 2.0f, 0.5f, "Press SPACE to play", m_brush);
	graphics::drawText(5.0f, 8.0f, 0.4, "Press   M   to   activate   Level   Maker", m_brush);
}
