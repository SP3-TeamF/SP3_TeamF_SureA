#include "GameObject.h"

GameObject::GameObject() :
pos(Vector3(0, 0, 0)),
scale(Vector3(1, 1, 1)),
Hitbox(nullptr)
{

}

GameObject::GameObject(Vector3 position, Vector3 scale)
{
    this->pos.Set(position.x, position.y, position.z);
    this->scale.Set(scale.x, scale.y, scale.z);
    this->Hitbox = new AABB(position, scale.x, scale.y);
}

GameObject::~GameObject()
{

}