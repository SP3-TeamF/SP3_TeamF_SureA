#include "Idle.h"
#include "Player.h"
#include"Enemy.h"

Idle::Idle()
{
    currentEnemy = nullptr;
}

Idle::~Idle()
{
}

void Idle::Update(double dt)
{
    FindPath();
}

//Finds the path between the start and end point
void Idle::FindPath()
{
    if (currentEnemy)
    {
        if (!pathFinder.m_FoundGoal && !pathFinder.m_PathUnable)
        {
            pathFinder.Findpath(currentEnemy->GetPathStartPosition(), currentEnemy->GetPathEndPosition());
        }
    }
}

bool Idle::ScanTarget()
{
    float distanceSquared = (player->Get_cPosition() - this->currentEnemy->Get_cPosition()).LengthSquared();

    if (distanceSquared < this->currentEnemy->GetScanRadius() * this->currentEnemy->GetScanRadius())
    {
        return true;
    }
    return false;
}

void Idle::SetCurrentEnemy(Enemy& targetEnemy)
{
    this->currentEnemy = &targetEnemy;
}