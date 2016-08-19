#include "Strategy.h"

Strategy::Strategy()
{
}

Strategy::~Strategy()
{
}

void Strategy::ClearWaypoints()
{
    this->wayPoints.clear();
}

void Strategy::AddWaypoint(Vector3 pos)
{
    Vector3* newPosition = &pos;
    wayPoints.push_back(*newPosition);
}

void Strategy::SetPosition(Vector3 pos)
{
    this->position = pos;
}

void Strategy::SetAttackTarget(Character* newAttackTarget)
{
    this->attackTarget = attackTarget;
}

