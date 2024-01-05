#include "level.h"
#include <graphics.h>
#include "player.h"
#include "util.h"
#include "block.h"


void Level::drawBlock(int i)
{
	Box& box = m_blocks[i];
	std::string& name = m_block_names[i];
	
	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;

	m_block_brush.texture = m_state->getFullAssetPath(name);

	graphics::drawRect(x, y, 1.8f * m_block_size, 1.8f * m_block_size, m_block_brush);

	if (m_state->m_debugging)
		graphics::drawRect(x, y, m_block_size, m_block_size, m_block_brush_debug);

}

void Level::checkCollisions()
{
    // Static Objects
    for (auto p_go : m_static_objects) {

    }


    // TODO: Why 2 for loops?
	for (auto & block : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectDown(block))
		{
			m_state->getPlayer()->m_pos_y += offset;

			// add sound event
			if (m_state->getPlayer()->m_vy > 1.0f)
				graphics::playSound(m_state->getFullAssetPath("Metal2.wav"), 1.0f);
			
			m_state->getPlayer()->m_vy = 0.0f;
	
			break;
		}
	}
	
	for (auto& block : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectSideways(block))
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
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();
	float offset_x = m_state->m_global_offset_x / 2.0f + w/2.0f;
	float offset_y = m_state->m_global_offset_y / 2.0f + h/2.0f;

	//draw background
	graphics::drawRect(offset_x, offset_y, 2.0f*w, 4.0f*w, m_brush_background);

	// draw player
	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->draw();

	// draw blocks
	for (int i = 0; i < m_blocks.size(); i++)
	{
		drawBlock(i);
	}

    // Draw Static & Dynamic Objects
    for (auto p_go : m_static_objects)
        p_go->draw();
    for (auto p_go : m_dynamic_objects)
        p_go->draw();
}

void Level::init()
{

    // Add Static & Dynamic Objects to Level
    m_static_objects.push_back(new Block(5, 6, 2, 2, "block8.png"));

	// Stage 1
	for (auto p_gob : m_static_objects)
		if (p_gob) p_gob->init();
	
	for (auto p_gob : m_dynamic_objects)
		if (p_gob) p_gob->init();



	// initialize some collidable blocks here.
	// normally, you should build a Block class 
	// and automate the process more.
	m_blocks.push_back(Box( 5, 6, 1, 1));
	m_blocks.push_back(Box( 4, 6, 1, 1));
	m_blocks.push_back(Box( 3, 6, 1, 1));
	m_blocks.push_back(Box( 2, 5, 1, 1));
	m_blocks.push_back(Box( 6, 6, 1, 1));
	m_blocks.push_back(Box( 7, 6, 1, 1));
	m_blocks.push_back(Box( 7, 5, 1, 1));
	m_blocks.push_back(Box( 3, 2, 1, 1));
	m_blocks.push_back(Box( 4, 3, 1, 1));

	m_block_names.push_back("block8.png");
	m_block_names.push_back("block1.png");
	m_block_names.push_back("block7.png");
	m_block_names.push_back("block6.png");
	m_block_names.push_back("block10.png");
	m_block_names.push_back("block1.png");
	m_block_names.push_back("block2.png");
	m_block_names.push_back("block8.png");
	m_block_names.push_back("block3.png");

	m_block_brush.outline_opacity = 0.0f;
	m_block_brush_debug.fill_opacity = 0.1f;
	SETCOLOR(m_block_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
	SETCOLOR(m_block_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);
}

Level::Level(const std::string & name)
	: GameObject(name)
{
	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.texture = m_state->getFullAssetPath("background.png");


}

Level::~Level()
{
	for (auto p_go : m_static_objects)
		delete p_go;
	for (auto p_go : m_dynamic_objects)
		delete p_go;
}
