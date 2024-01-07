#include "level.h"
#include <sgg/graphics.h>
#include "player.h"
#include "block.h"

void Level::checkCollisions()
{
    // Static Objects
    // Intersect Down
    for (auto& p_box : m_static_objects) {
            float offset = 0.0f;
            if (offset = m_state->getPlayer()->intersectDown(*p_box))
            {
                m_state->getPlayer()->m_pos_y += offset;
                m_state->getPlayer()->m_vy = 0.0f;
                break;
            }
    }
    // Intersect Sideways
    for (auto& p_box : m_static_objects) {
            float offset = 0.0f;
            if (offset = m_state->getPlayer()->intersectSideways(*p_box))
            {
                m_state->getPlayer()->m_pos_x += offset;
                m_state->getPlayer()->m_vx = 0.0f;
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

	GameObject::update(dt);
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
    m_static_objects.push_back(new Block(1, 7, 1, 1, "terrain\\grass_block.png"));
    m_static_objects.push_back(new Block(2, 7, 1, 1, "terrain\\grass_block.png"));
    //vertical blocks
    m_static_objects.push_back(new Block(1, 8, 1, 1, "terrain\\dirt_block2.png"));
    m_static_objects.push_back(new Block(2, 8, 1, 1, "terrain\\dirt_block2.png"));
    m_static_objects.push_back(new Block(1, 9, 1, 1, "terrain\\dirt_block2.png"));
    m_static_objects.push_back(new Block(2, 9, 1, 1, "terrain\\dirt_block2.png"));
    m_static_objects.push_back(new Block(1, 10, 1, 1, "terrain\\dirt_block2.png"));
    m_static_objects.push_back(new Block(2, 10, 1, 1, "terrain\\dirt_block2.png"));
    m_static_objects.push_back(new Block(1, 11, 1, 1, "terrain\\dirt_block2.png"));
    m_static_objects.push_back(new Block(2, 11, 1, 1, "terrain\\dirt_block2.png"));
    //floor
    m_static_objects.push_back(new Block(3, 11.25, 1, 0.5, "terrain\\floor.png"));
    m_static_objects.push_back(new Block(4, 11.25, 1, 0.5, "terrain\\floor.png"));
    // next platforms
    m_static_objects.push_back(new Block(5, 9, 1, 1, "terrain\\grass_block.png"));
    m_static_objects.push_back(new Block(6, 9, 1, 1, "terrain\\grass_block.png"));
    m_static_objects.push_back(new Block(7, 9, 1, 1, "terrain\\grass_block.png"));
    m_static_objects.push_back(new Block(8, 9, 1, 1, "terrain\\grass_block.png"));
    m_static_objects.push_back(new Block(10, 7, 1, 1, "terrain\\grass_block.png"));

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
