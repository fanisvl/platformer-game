#include "level.h"
#include <sgg/graphics.h>
#include "player.h"
#include "spikes.h"
#include "dynamic_object.h"
#include "enemy.h"
#include "box.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>>
#include <iomanip>


void Level::checkCollisions()
{
    // Static Objects
    // Intersect Sideways
    for (auto& p_sob : m_static_objects) {
        float offset = 0.0f;
        if (offset = m_state->getPlayer()->intersectSideways(*p_sob)) {
            p_sob->handleCollision(SIDEWAYS);
            m_state->getPlayer()->handleCollision(SIDEWAYS, offset);
            break;
        }
    }

    // Intersect Down
    for (auto& p_sob : m_static_objects) {
        float offset = 0.0f;
        if (offset = m_state->getPlayer()->intersectDown(*p_sob)) {
            p_sob->handleCollision(DOWNWARDS);
            m_state->getPlayer()->handleCollision(DOWNWARDS, offset);
            break;
        }
    }

    // Dynamic Objects
    // TODO: Change to match all dynamic objects.
    // Coins for example get "killed" when the player intersects in any direction.
    // Enemies get killed when the player intersects down, and kill the player when they intersect sideways.
    for (auto& p_dob : m_dynamic_objects) {
        float offset = 0.0f;
        if (offset = m_state->getPlayer()->intersectSideways(*p_dob)) {
            // Dynamic objects should know if an intersection kills them, and what to do.
            // We can add a method like handleCollision(SIDEWAYS) to all dynamic objects that kills (hides) the object based on the direction of the collision.
            p_dob->handleCollision(SIDEWAYS);
            break;
        }
    }

    for (auto& p_dob : m_dynamic_objects) {
        float offset = 0.0f;
        if (offset = m_state->getPlayer()->intersectDown(*p_dob)) {
            p_dob->handleCollision(DOWNWARDS);
            break;
        }
    }
}

void Level::update(float dt)
{
	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->update(dt);

    for (auto& p_go : m_dynamic_objects)
        p_go->update(dt);

	checkCollisions();

}

void Level::draw()
{
    if (m_background) m_background->draw();

    // Draw Static & Dynamic Objects
    for (auto& p_go : m_static_objects)
        p_go->draw();
    for (auto& p_go : m_dynamic_objects)
        p_go->draw();
}

void Level::init()
{
    // Create background
    if (m_background == nullptr) {
        m_background = new Background();
    }
    if (m_background) m_background->init();

    // Add Static & Dynamic Objects to Level
    // TODO: Load level by reading file.
    // Add Static & Dynamic Objects to Level
  
    m_state->getPlayer()->setInitialPosition(10.0f, 6.0f);
    m_state->getPlayer()->goToInitialPosition();
    LoadLevel("levels\\level1.txt");  
	for (auto& p_gob : m_static_objects)
		if (p_gob) p_gob->init();
	
	for (auto& p_gob : m_dynamic_objects)
		if (p_gob) p_gob->init();

}

Level::Level()
{

}

Level::~Level()
{
    delete m_background;
	for (auto p_go : m_static_objects)
		delete p_go;
	for (auto p_go : m_dynamic_objects)
		delete p_go;
}

void Level::LoadLevel(std::string filepath) {
    
    std::ifstream inputFile(filepath);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);

        std::string Type;
        float x_value;
        float y_value;
        float w_value;
        float h_value;
        std::string pngImage;

        if (iss >> std::quoted(Type) >> x_value >> y_value >> w_value >> h_value >> std::quoted(pngImage)) {
            if (Type == "Enemy") {
                m_dynamic_objects.push_back(new Enemy(x_value, y_value, w_value, h_value, pngImage));
            }
            else if (Type == "Spikes") {
                m_static_objects.push_back(new Spikes(x_value, y_value, w_value, h_value, pngImage));
            }
            else if (Type == "StaticBlock") {
                m_static_objects.push_back(new StaticObject(x_value, y_value, w_value, h_value, pngImage));
            }
        }
    }
}

void Level::resetLevel() {
    // Hide dynamic objects instead of destroying and re-creating them.
    // Add a hide()/die() method to dynamic objects
    // init() will undo the effects of hide()

    // TODO: Add die method to player that plays death animation
    // TODO: Count deaths OR Add timer / Highscore??
    m_state->getPlayer()->goToInitialPosition();
    for (auto p_dob : m_dynamic_objects)
        p_dob->init();
}
