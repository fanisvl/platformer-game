#include "level.h"
#include "level.h"
#include <sgg/graphics.h>
#include "player.h"
#include "spikes.h"
#include "coin.h"
#include "dynamic_object.h"
#include "moving_enemy.h"
#include "box.h"
#include "projectile_enemy.h"
#include "rotating_trap.h"
#include "falling_platform.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>>
#include <iomanip>


void Level::checkCollisions()
{
    // Static Objects - Player - Sideways
    for (auto& p_sob : m_static_objects) {
        float offset = 0.0f;
        if (offset = m_state->getPlayer()->intersectSideways(*p_sob)) {
            p_sob->handleCollision(SIDEWAYS);
            m_state->getPlayer()->handleCollision(SIDEWAYS, offset);
        }
    }

    // Static Objects - Player - Downwards
    for (auto& p_sob : m_static_objects) {
        float offset = 0.0f;
        if (offset = m_state->getPlayer()->intersectDown(*p_sob)) {
            p_sob->handleCollision(DOWNWARDS);
            m_state->getPlayer()->handleCollision(DOWNWARDS, offset);
        }
    }

    // Static Objects - Player - Upwards
    for (auto& p_sob : m_static_objects) { 
        float offset = 0.0f;
        if (offset = m_state->getPlayer()->intersectUp(*p_sob)) {
            p_sob->handleCollision(UPWARDS);
            m_state->getPlayer()->handleCollision(UPWARDS, offset);
        }
    }

    // Dynamic Objects - Player - Sideways
    for (auto& p_dob : m_dynamic_objects) {
        float offset = 0.0f;
        if (m_state->getPlayer()->intersectSideways(*p_dob)) {
            p_dob->handleCollision(SIDEWAYS);
            checkCollusionPlatform(p_dob, offset,SIDEWAYS);
        }
    }

    // Dynamic Objects - Player - Downwards
    for (auto& p_dob : m_dynamic_objects) {
        float offset = 0.0f;
        if (m_state->getPlayer()->intersectDown(*p_dob)) {
            p_dob->handleCollision(DOWNWARDS);
            checkCollusionPlatform(p_dob, offset,DOWNWARDS);
        }
    }

    // Dynamic Objects - Player - Upwards
    for (auto& p_dob : m_dynamic_objects) {
        float offset = 0.0f;
        if (m_state->getPlayer()->intersectDown(*p_dob)) {
            p_dob->handleCollision(UPWARDS);
            checkCollusionPlatform(p_dob, offset, UPWARDS);
        }
    }
   

}


void Level::checkCollusionPlatform(DynamicObject* ob, float offset, CollisionType type){
    // checkPlatform
    if (FallingPlatform* ptr = dynamic_cast<FallingPlatform*>(ob) ){
        if (!ptr->isHidden()) {
            m_state->getPlayer()->handleCollision(type, offset);
        }
        
    }
}

void Level::update(float dt)
{

    for (auto& p_dob: m_dynamic_objects)
        p_dob->update(dt);

    for (auto& p_sob : m_static_objects)
        p_sob->update(dt);

	checkCollisions();
    resetIfPlayerOutOfBounds();

}

void Level::resetIfPlayerOutOfBounds() {
    // Get player position
    std::pair<float, float> player_xy = { GameObject::m_state->getPlayer()->getPositionXY() };
    float player_x = player_xy.first;
    float player_y = player_xy.second;

    if (player_y < -1.0f || player_y > 10.0f) resetLevel();
    if (player_x < 0.0f || player_y > 17.0f) resetLevel();

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

void Level::setPlayerSpawn(float x, float y) {
    player_spawn_x = x; 
    player_spawn_y = y;
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
        float rotatingTrapRad = 0.0f;
        float rotatingTrapSpeed = 0.0f;

        if (iss >> std::quoted(Type) >> x >> y >> width >> height >> std::quoted(assetName)) {
            if (Type == "Player") {
                player_spawn_x = x;
                player_spawn_y = y;
                std::cout << "Level setting initial position for player" << std::endl;
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

            else if (Type == "RotatingTrap") {
                if (iss >> left_boundary >> right_boundary >> rotatingTrapRad >> rotatingTrapSpeed ) {
                    m_static_objects.push_back(new RotatingTrap(x, y, width, height, assetName, left_boundary, right_boundary, rotatingTrapRad, rotatingTrapSpeed));
                }
                
                else {
                    std::cerr << "Error: RotatingTrap must have boundaries, radius and speed values." << std::endl;
                    // Handle where boundaries, rad and speed are not provided
                }
            }

            else if (Type == "StaticObject") {
                m_static_objects.push_back(new StaticObject(x, y, width, height, assetName));
            }
            else if (Type == "Spikes") {
                m_static_objects.push_back(new Spikes(x, y, width, height, assetName));
            }


            else if (Type == "FallingPlatform") {
                m_dynamic_objects.push_back(new FallingPlatform(x, y, width, height, assetName));
            }
            else if (Type == "ProjectileEnemy") {
                    m_dynamic_objects.push_back(new ProjectileEnemy(x, y, width, height, assetName));
            }
            else if (Type == "Coin") {
                m_dynamic_objects.push_back(new Coin(x, y, width, height, assetName));
            }

        }
    }
}

void Level::resetLevel() {
    // Resets level to initial state (player spawn, points, dynamic objects)

    m_state->getPlayer()->goToPosition(player_spawn_x, player_spawn_y);
    m_state->getPlayer()->resetPoints();
    std::cout << "Level sending player to original position by RESET_LEVEL" << std::endl;
    for (auto p_dob : m_dynamic_objects)
        p_dob->reset();
}
