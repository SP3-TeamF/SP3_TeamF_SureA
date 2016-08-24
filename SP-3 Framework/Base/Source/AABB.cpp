#include "AABB.h"

AABB::AABB()
{

}

AABB::AABB(Vector3 pos, float radius)
{
    this->position = pos;

    this->width = 0;
    this->height = 0;
    this->radius = radius;
    HITBOX_TYPE = HB_CIRCLE;
}

AABB::AABB(Vector3 pos, float width, float height)
{
    this->radius = 0;
    this->width = width;
    this->position = pos;
    this->height = height;
    HITBOX_TYPE = HB_BOX;
}

void AABB::SetPosition(Vector3 pos)
{
    this->position = pos;
}

AABB::~AABB()
{
}

void AABB::Set(Vector3 pos, float radius)
{
    this->position = pos;

    this->width = 0;
    this->height = 0;
    this->radius = radius;

    HITBOX_TYPE = HB_CIRCLE;
}

void AABB::Set(Vector3 pos, float width, float height)
{
    this->position = pos;
    this->radius = 0;
    this->width = width;
    this->height = height;
	this->position.z = 0;

	HITBOX_TYPE = HB_BOX;
  
}

bool AABB::AABBtoAABB(const AABB& other)
{
    if (this->HITBOX_TYPE == HB_BOX && other.HITBOX_TYPE == HB_BOX)
    {
        return BOXtoBOX(other);
    }
    else if (this->HITBOX_TYPE == HB_CIRCLE && other.HITBOX_TYPE == HB_CIRCLE)
    {
        return CIRCLEtoCIRCLE(other);
    }
    else
    {
        return BOXtoCIRCLE(other);
    }

    return false;
}

bool AABB::BOXtoBOX(const AABB& other)
{
    Vector3 thisMIN = this->position - Vector3(width * 0.5f, height * 0.5f, width * 0.5f);
    Vector3 thisMAX = this->position + Vector3(width * 0.5f, height * 0.5f, width * 0.5f);

    Vector3 otherMIN = other.position - Vector3(width * 0.5f, height * 0.5f, width * 0.5f);
    Vector3 otherMAX = other.position + Vector3(width * 0.5f, height * 0.5f, width * 0.5f);

    if (
        thisMAX.x > otherMIN.x &&
        thisMIN.x < otherMAX.x && 
        thisMAX.y > otherMIN.y &&
        thisMIN.y < otherMAX.y &&
        thisMAX.z > otherMIN.z &&
        thisMIN.z < otherMAX.z
        )
    {
        return true;
    }
    return false;
}

bool AABB::BOXtoCIRCLE(const AABB& other)
{
    if (this->HITBOX_TYPE == HB_CIRCLE)
    {
        Vector3 Dir = other.position - this->position;
        Dir.Normalize();

        Vector3 finalPos = this->position + Dir * this->radius;
		return PointToAABB(finalPos);
    }
    else
    {
        Vector3 Dir = this->position - other.radius;
        Dir.Normalize();

        Vector3 finalPos = this->position + Dir * other.radius;
        return PointToAABB(other);
    }
    return false;
}

bool AABB::CIRCLEtoCIRCLE(const AABB& other)
{
    float totalRadiusLengthSquared = this->radius + other.radius;
    float distanceBetweenCenterSquared = (this->position - other.position).LengthSquared();

    if (distanceBetweenCenterSquared <= totalRadiusLengthSquared)
    {
        return true;
    }
    
    return false;
}

bool AABB::PointToAABB(Vector3 pos)
{
    Vector3 thisMIN = this->position - Vector3(width * 0.5f, height * 0.5f,0);
    Vector3 thisMAX = this->position + Vector3(width * 0.5f, height * 0.5f,0);

	if (
        pos.x >= thisMIN.x && pos.x <= thisMAX.x &&
        pos.y >= thisMIN.y && pos.y <= thisMAX.y &&
        pos.z >= thisMIN.z && pos.z <= thisMAX.z
        )
	{
		return true;
	}

	return false;
}

bool AABB::PointToAABB(const AABB& other)
{
    Vector3 thisMIN = other.position - Vector3(width * 0.5f, height * 0.5f, width * 0.5f);
    Vector3 thisMAX = other.position + Vector3(width * 0.5f, height * 0.5f, width * 0.5f);

    if (
        this->position.x >= thisMIN.x && this->position.x <= thisMAX.x &&
        this->position.y >= thisMIN.y && this->position.y <= thisMAX.y && 
        this->position.z >= thisMIN.z &&  this->position.y <= thisMAX.z
        )
    {
        return true;
    }

    return false;
}

bool AABB::CIRCLEtoPOINT(Vector3 point)
{
    if ((point - this->position).LengthSquared() < radius * radius)
    {
        return true;
    }

    return false;
}
