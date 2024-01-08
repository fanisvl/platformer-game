#include "level.h"
#include <sgg/graphics.h>
#include "player.h"
#include "spikes.h"

void Level::checkCollisions()
{
    // Static Objects
    // Intersect Down
    for (auto& p_sob : m_static_objects) {
            float offset = 0.0f;
            if (offset = m_state->getPlayer()->intersectDown(*p_sob))
            {
                // p_sob->resolveCollision() ??
                if (p_sob->isDeadly()) {
                    resetLevel();
                }

                m_state->getPlayer()->m_pos_y += offset;
                m_state->getPlayer()->m_vy = 0.0f;
            }
    }
    // Intersect Sideways
    for (auto& p_sob : m_static_objects) {
            float offset = 0.0f;
            if (offset = m_state->getPlayer()->intersectSideways(*p_sob))
            {
                if (p_sob->isDeadly()) {
                    resetLevel();
                }
                m_state->getPlayer()->m_pos_x += offset;
                m_state->getPlayer()->m_vx = 0.0f;
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
  
    m_state->getPlayer()->setInitialPosition(2.0f, 6.0f);
    m_state->getPlayer()->goToInitialPosition();
  
  // Starting Platform
    m_static_objects.push_back(new Block(0.75, 6.225, 0.55, 0.55, "terrain\\block_with_triangles.png"));
    m_static_objects.push_back(new Block(1, 7, 1, 1, "terrain\\moss_block.png"));
    m_static_objects.push_back(new Block(2, 7, 1, 1, "terrain\\moss_block.png"));
  
  //vertical blocks
    m_static_objects.push_back(new Block(1, 8, 1, 1, "terrain\\dirt_block1.png"));
    m_static_objects.push_back(new Block(2, 8, 1, 1, "terrain\\dirt_block1.png"));
    m_static_objects.push_back(new Block(1, 9, 1, 1, "terrain\\dirt_block1.png"));
    m_static_objects.push_back(new Block(2, 9, 1, 1, "terrain\\dirt_block1.png"));
    m_static_objects.push_back(new Block(1, 10, 1, 1, "terrain\\dirt_block1.png"));
    m_static_objects.push_back(new Block(0.75, 10.25, 0.55, 0.55, "terrain\\block_with_triangles.png"));
    m_static_objects.push_back(new Block(2, 10, 1, 1, "terrain\\dirt_block1.png"));
    m_static_objects.push_back(new Block(1, 11, 1, 1, "terrain\\block_with_triangles.png"));
    m_static_objects.push_back(new Block(2, 11, 1, 1, "terrain\\dirt_block1.png"));
  
  //floor_blocks
    //main floor
    m_static_objects.push_back(new Block(2.775, 10.52, 0.55, 0.55, "terrain\\block_with_triangles.png"));
    m_static_objects.push_back(new Block(3, 11.3, 1, 1, "terrain\\floor_block_left_side.png"));
    m_static_objects.push_back(new Block(2.75, 11.75, 0.55, 0.55, "terrain\\floor_left_edge.png"));
    m_static_objects.push_back(new Block(4, 11.3, 1, 1, "terrain\\floor_block.png"));
    m_static_objects.push_back(new Block(5, 11.3, 1, 1, "terrain\\floor_block.png"));
    m_static_objects.push_back(new Block(6, 11.3, 1, 1, "terrain\\floor_block.png"));
    m_static_objects.push_back(new Block(7, 11.3, 1, 1, "terrain\\floor_block.png"));
    m_static_objects.push_back(new Block(8, 11.3, 1, 1, "terrain\\floor_block.png"));
    m_static_objects.push_back(new Block(9, 11.3, 1, 1, "terrain\\floor_block.png"));
    m_static_objects.push_back(new Block(10, 11.3, 1, 1,"terrain\\floor_block.png"));
    m_static_objects.push_back(new Block(11, 11.3, 1, 1,"terrain\\floor_block.png"));
    m_static_objects.push_back(new Block(12, 11.3, 1, 1,"terrain\\floor_block.png"));
    m_static_objects.push_back(new Block(13, 11.3, 1, 1,"terrain\\floor_block.png"));
    m_static_objects.push_back(new Block(14, 11.3, 1, 1,"terrain\\floor_block.png"));
    m_static_objects.push_back(new Block(15, 11.3, 1, 1, "terrain\\floor_block.png"));
    m_static_objects.push_back(new Block(15.79, 11.07, 0.55, 0.55, "terrain\\floor_left_edge.png"));
  
    // spikes
    m_static_objects.push_back(new Spikes(14, 10.3, 1, 1, "spikes.png"));
 
  
    //walls and ceiling
    m_static_objects.push_back(new Block(0.25, 11.75, 0.55, 0.55, "terrain\\floor_edge.png"));
    m_static_objects.push_back(new Block(1, 12, 1, 1, "terrain\\floor_block.png"));
    m_static_objects.push_back(new Block(2, 12, 1, 1, "terrain\\floor_block.png"));
  
     // left wall
    m_static_objects.push_back(new Block(0, 11, 1, 1, "terrain\\brick_outline.png"));
    m_static_objects.push_back(new Block(0, 10, 1, 1, "terrain\\brick_outline.png"));
    m_static_objects.push_back(new Block(0, 9, 1, 1, "terrain\\brick_outline.png"));
    m_static_objects.push_back(new Block(0, 8, 1, 1, "terrain\\brick_outline.png"));
    m_static_objects.push_back(new Block(0, 7, 1, 1, "terrain\\brick_outline.png"));
    m_static_objects.push_back(new Block(0, 6, 1, 1, "terrain\\brick_outline.png"));
    m_static_objects.push_back(new Block(0, 5, 1, 1, "terrain\\brick_outline.png"));
    m_static_objects.push_back(new Block(0, 4, 1, 1, "terrain\\brick_outline.png"));
    m_static_objects.push_back(new Block(0, 3, 1, 1, "terrain\\brick_outline.png"));
  
    //right wall
    m_static_objects.push_back(new Block(16, 10.3, 1, 1, "terrain\\right_wall.png"));
    m_static_objects.push_back(new Block(16, 9.3, 1, 1, "terrain\\right_wall.png"));
    m_static_objects.push_back(new Block(16, 8.3, 1, 1, "terrain\\floor_block_left_side.png"));


  // next platforms
    m_static_objects.push_back(new Block(7.5, 7.3, 1, 1, "terrain\\moss_block.png"));
    m_static_objects.push_back(new Block(8.5, 7.3, 1, 1, "terrain\\moss_block.png"));
    m_static_objects.push_back(new Block(9.5, 7.3, 1, 1, "terrain\\moss_block.png"));
    m_static_objects.push_back(new Block(10.5, 7.3, 1, 1,"terrain\\moss_block.png"));
    m_static_objects.push_back(new Block(11.5, 7.3, 1, 1, "terrain\\moss_block.png"));
    m_static_objects.push_back(new Block(12.5, 7.3, 1, 1, "terrain\\moss_block.png"));
    m_static_objects.push_back(new Block(13.5, 7.3, 1, 1, "terrain\\moss_block.png"));
    m_static_objects.push_back(new Block(14.5, 7.3, 1, 1, "terrain\\moss_block.png"));
    m_static_objects.push_back(new Block(15.5, 7.3, 1, 1, "terrain\\block_with_triangles.png"));
  
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
