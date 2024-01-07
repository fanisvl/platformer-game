#pragma once
#include "gameobject.h"
#include "box.h"

class Enemy : public GameObject, public Box {
	
	std::string asset_path;
};