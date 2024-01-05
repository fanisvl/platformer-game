#include "level.h"
#include <graphics.h>
#include "player.h"
#include "block.h"

void Level::checkCollisions()
{
    // Static Objects
    // Intersect Down
    for (auto& p_box : m_static_objects) {
        // If the object pointed to by pGob is a derived type of 'Box' (e.g. 'Block' or 'Player')
        // the cast returns a pointer of type Box*, necessary for the intersect method.
        // otherwise it returns a nullptr and the if-statement isn't executed.
            float offset = 0.0f;
            if (offset = m_state->getPlayer()->intersectDown(*p_box))
            {
                m_state->getPlayer()->m_pos_y += offset;
                // Add sound event
                if (m_state->getPlayer()->m_vy > 1.0f)
                    graphics::playSound(m_state->getFullAssetPath("Metal2.wav"), 1.0f);
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

	checkCollisions();

	GameObject::update(dt);
}

void Level::draw()
{
//	float w = CANVAS_WIDTH;
//	float h = CANVAS_HEIGHT;
//	float offset_x = m_state->m_global_offset_x / 2.0f + w/2.0f;
//	float offset_y = m_state->m_global_offset_y / 2.0f + h/2.0f;

	//Draw Background
//	graphics::drawRect(offset_x, offset_y, 2.0f*w, 4.0f*w, m_brush_background);
    if (m_background) m_background->draw();

	// Draw Player
	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->draw();

    // Draw Static & Dynamic Objects
    for (auto& p_go : m_static_objects)
        p_go->draw();
    for (auto& p_go : m_dynamic_objects)
        p_go->draw();
}

void Level::init()
{
    if (m_background) m_background->init();

    // Add Static & Dynamic Objects to Level
    // TODO:
    m_static_objects.push_back(new Block(5, 6, 1, 1, "block8.png"));
    m_static_objects.push_back(new Block(4, 6, 1, 1, "block1.png"));
    m_static_objects.push_back(new Block(3, 6, 1, 1, "block7.png"));
    m_static_objects.push_back(new Block(2, 5, 1, 1, "block6.png"));
    m_static_objects.push_back(new Block(6, 6, 1, 1, "block10.png"));
    m_static_objects.push_back(new Block(7, 6, 1, 1, "block1.png"));
    m_static_objects.push_back(new Block(7, 5, 1, 1, "block2.png"));
    m_static_objects.push_back(new Block(3, 2, 1, 1, "block8.png"));
    m_static_objects.push_back(new Block(4, 3, 1, 1, "block3.png"));

    // Stage 1
	for (auto& p_gob : m_static_objects)
		if (p_gob) p_gob->init();
	
	for (auto& p_gob : m_dynamic_objects)
		if (p_gob) p_gob->init();

}

Level::Level(const std::string & name)
	: GameObject(name)
{
//	m_brush_background.outline_opacity = 0.0f;
//	m_brush_background.texture = m_state->getFullAssetPath("background.png");
    if (m_background == nullptr) {
        m_background = new Background();
    }


}

Level::~Level()
{
    delete m_background;
	for (auto p_go : m_static_objects)
		delete p_go;
	for (auto p_go : m_dynamic_objects)
		delete p_go;
}
