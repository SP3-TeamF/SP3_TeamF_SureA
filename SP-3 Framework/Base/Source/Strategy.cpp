#include "Strategy.h"

Strategy::Strategy()
{
}

Strategy::~Strategy()
{
}

void Strategy::ClearWaypoints()
{
    while (!wayPoints.empty())
    {
        delete wayPoints.front();
        wayPoints.pop();
    }
}

void Strategy::AddWaypoint(Vector3 pos)
{
    Vector3* newPosition = &pos;
    wayPoints.push(newPosition);
}

void Strategy::SetPosition(Vector3 pos)
{
    this->position = pos;
}



