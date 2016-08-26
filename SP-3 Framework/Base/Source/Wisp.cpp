#include "Wisp.h"

Wisp::Wisp()
{
    patrolStrategy = new Patrol();
    currentStrategy = patrolStrategy;
    wispType = WISP_FIRE;
    patrolStrategy->SetCurrentEnemy(dynamic_cast<Enemy*>(this));
}

Wisp::~Wisp()
{
}

void Wisp::Update(double dt)
{
    Enemy::Update(dt);
}

void Wisp::Reset()
{
    while (!wayPoints.empty())
    {
        wayPoints.pop();
    }

    while (!patrolPoints.empty())
    {
        patrolPoints.pop();
    }
    wispType = WISP_FIRE;
}