#include "Chase.h"
#include "Player.h"
#include "Enemy.h"
#include "GlobalDatas.h"

Chase::Chase()
{

}

Chase::~Chase()
{
}

void Chase::Update(double dt)
{
    if (currentEnemy)
    {
        if (!currentEnemy->wayPoints.empty())
        {
            Vector3 dir = (currentEnemy->wayPoints.front() * m_TileMap->GetTileSize())  - currentEnemy->Get_cPosition();

            if (dir.LengthSquared() < 2 * 2)
            {
                currentEnemy->Set_cPosition(currentEnemy->wayPoints.front() * m_TileMap->GetTileSize());
                currentEnemy->wayPoints.pop();  
                return;
            }

            dir.Normalize();

            Vector3 nextPosition = currentEnemy->Get_cPosition() + (dir * currentEnemy->Get_cMoveSpeed() * dt);

            currentEnemy->Set_cPosition(nextPosition);
        }
    }
}