#include "Patrol.h"
#include "GlobalDatas.h"
#include "Enemy.h"


Patrol::Patrol()
{
}

Patrol::~Patrol()
{
}

void Patrol::Update(double dt)
{
    if (currentEnemy)
    {
        if (!currentEnemy->patrolPoints.empty())
        {
            Vector3 dir = (currentEnemy->patrolPoints.front() * m_TileMap->GetTileSize()) - currentEnemy->Get_cPosition();

            if (dir.LengthSquared() < 2 * 2)
            {
                Vector3 tempVector = Vector3(currentEnemy->patrolPoints.front());
                currentEnemy->Set_cPosition(tempVector * m_TileMap->GetTileSize());
                currentEnemy->patrolPoints.pop();
                currentEnemy->patrolPoints.push(tempVector);
                return;
            }

            dir.Normalize();

            Vector3 nextPosition = currentEnemy->Get_cPosition() + (dir * currentEnemy->Get_cMoveSpeed() * dt);

            currentEnemy->Set_cPosition(nextPosition);
        }
    }
}