#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"
#include "AABB.h"

class GameObject
{
public:
	AABB* Hitbox;

	Vector3 pos;
	Vector3 view;
    Vector3 scale;
   
	bool active;

	GameObject();
	GameObject(Vector3 position, Vector3 scale);
	~GameObject();
};

#endif