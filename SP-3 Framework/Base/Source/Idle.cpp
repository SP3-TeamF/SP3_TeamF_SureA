#include "Idle.h"
#include "Player.h"
#include"Enemy.h"

Idle::Idle()
{
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
    Vector3 playerPos = player->Get_cPosition() + Vector3(GlobalData.world_X_offset, GlobalData.world_Y_offset);

    float distanceSquared = (playerPos - this->currentEnemy->Get_cPosition()).LengthSquared();
    cout << distanceSquared - this->currentEnemy->GetScanRadius() * this->currentEnemy->GetScanRadius() << endl;

    if (distanceSquared < this->currentEnemy->GetScanRadius() * this->currentEnemy->GetScanRadius())
    {
        return true;
    }

    return false;
}
