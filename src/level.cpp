#include "level.h"
#include <sgg/graphics.h>
#include "player.h"
#include "spikes.h"
#include "dynamic_object.h"
#include "moving_enemy.h"
#include "box.h"
#include "projectile_enemy.h"
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
    //graphics::playMusic("assets\\music.mp3", 0.1f, true, 0);  

    // Create background
    if (m_background == nullptr) {
        m_background = new Background("background/cave_background.png");
    }
    if (m_background) m_background->init();
  
  LoadLevel(m_level_path);
  
  // Add Static & Dynamic Objects to Level
	for (auto& p_gob : m_static_objects)
		if (p_gob) p_gob->init();
	   
	for (auto& p_gob : m_dynamic_objects)
		if (p_gob) p_gob->init();

}

Level::Level(){}

Level::Level(std::string level_path) {
    m_level_path = level_path;
}

Level::~Level()
{
    delete m_background;
	for (auto p_go : m_static_objects)
		delete p_go;
	for (auto p_go : m_dynamic_objects)
		delete p_go;
}

void Level::LoadLevel(std::string levelName) {
    
    std::ifstream inputFile("levels\\" + levelName);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }
    std::string line;
    while (std::getline(inputFile, line)) {

        std::istringstream iss(line);
        std::string Type;
        float x;
        float y;
        float width;
        float height;
        std::string assetName;
        float left_boundary = 0.0f;  // Default value
        float right_boundary = 0.0f; // Default value

        if (iss >> std::quoted(Type) >> x >> y >> width >> height >> std::quoted(assetName)) {
            if (Type == "Player") {
                if (m_state->getPlayer() != nullptr) {
                    m_state->getPlayer()->setInitialPosition(x, y);
                    m_state->getPlayer()->goToInitialPosition();
                }
            }

            else if (Type == "MovingEnemy") {
                // Check if there are additional parameters for MovingEnemy
                if (iss >> left_boundary >> right_boundary) {
                    m_dynamic_objects.push_back(new MovingEnemy(x, y, width, height, assetName, left_boundary, right_boundary));
                }
                else {
                    // Handle case where boundaries are not provided
                    std::cerr << "Error: MovingEnemy must have left and right boundary values." << std::endl;
                }
            }
            else if (Type == "Spikes") {
                m_static_objects.push_back(new Spikes(x, y, width, height, assetName));
            }
            else if (Type == "StaticObject") {
                m_static_objects.push_back(new StaticObject(x, y, width, height, assetName));
            }
            else if (Type == "ProjectileEnemy") {
                    m_dynamic_objects.push_back(new ProjectileEnemy(x, y, width, height, assetName));
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
