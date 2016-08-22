#include "Idle.h"
#include "Player.h"

Idle::Idle()
{
    this->scanRadius = 0;
    this->startPosition = nullptr;
    this->targetPosition = nullptr;
}

Idle::~Idle()
{
}

void Idle::Update(double dt)
{
}

//Finds the path between the start and end point
void Idle::FindPath()
{
    if (!pathFinder.m_FoundGoal && !pathFinder.m_PathUnable)
    {
        if (this->startPosition && this->targetPosition)
        {
            pathFinder.Findpath(*startPosition, *targetPosition);
        }
    }
}

void Idle::SetPath(Vector3 targetPosition)
{
    if (this->targetPosition)
    {
        delete this->targetPosition;
        Vector3* newPosition = new Vector3(targetPosition);
        this->targetPosition = newPosition;
    }

    if (this->startPosition)
    {
        delete this->startPosition;
        Vector3* newPosition = new Vector3(this->position);
        this->startPosition = newPosition;
    }

    this->scanRadius = scanRadius;
}

void Idle::SetScanRadius(float scanRadius)
{
    this->scanRadius = scanRadius;
}

bool Idle::ScanTarget()
{
    float distanceSquared = (player->Get_cPosition() - position).LengthSquared();

    if (distanceSquared < this->scanRadius)
    {
        return true;
    }
    return false;
}