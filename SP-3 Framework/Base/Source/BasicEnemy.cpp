#include "BasicEnemy.h"
#include "Player.h"

#include <iostream>
using std::cout;
using std::endl;

BasicEnemy::BasicEnemy()
{
    idleStrategy = new Idle();
    chaseStrategy = new Chase();
    attackStrategy = new Attack();

    idleStrategy->SetCurrentEnemy(dynamic_cast<Enemy*>(this));
	chaseStrategy->SetCurrentEnemy(dynamic_cast<Enemy*>(this));
	attackStrategy->SetCurrentEnemy(dynamic_cast<Enemy*>(this));

    CURRENT_STATE = IDLE_STATE;

    currentStrategy = idleStrategy;
	enemyHitbox.Set(this->c_Position, 32, 32);
	Hitpoint = 100;
}

BasicEnemy::~BasicEnemy()
{
}

void BasicEnemy::collisionCheck()
{
	if (enemyHitbox.AABBtoAABB(player->playerHitbox) == true)
	{
		player->Add_cHealth(-10);
	}

	vector<CBulletInfo*> temp = BulletFactory->GetBulletList();
	for (auto bulletIt : temp)
	{
		if (bulletIt->GetStatus())
		{
			if (enemyHitbox.PointToAABB(bulletIt->GetPosition()) == true)
			{
				Hitpoint -= 10;
				bulletIt->SetStatus(false);
				break;
			}
		}
	}
}

void BasicEnemy::Update(double dt)
{
    Enemy::Update(dt);

	enemyHitbox.SetPosition(this->c_Position + Vector3(+m_TileMap->GetTileSize() * 0.5, +m_TileMap->GetTileSize() * 0.5, 0));

	collisionCheck();

    switch (CURRENT_STATE)
    {
        case Enemy::IDLE_STATE:
        {
            if (idleStrategy->ScanTarget())
            {
                this->pathStartPosition = this->c_Position / m_TileMap->GetTileSize();
                this->pathEndPosition = (player->Get_cPosition() + Vector3(GlobalData.world_X_offset, GlobalData.world_Y_offset))/ m_TileMap->GetTileSize();
                CURRENT_STATE = SCANNING_STATE;
            }
            break;
        }
        case Enemy::SCANNING_STATE:
        {
            if (idleStrategy->pathFinder.m_FoundGoal || idleStrategy->pathFinder.m_PathUnable)
            {
                this->SetWaypoints(idleStrategy->pathFinder.GetWayPoints());
                CURRENT_STATE = CHASE_STATE;
                currentStrategy = chaseStrategy;
            }
            else
            {
                idleStrategy->FindPath();
            }
            break;
        }
        case Enemy::CHASE_STATE:
        {
            if (wayPoints.empty())
            {
                idleStrategy->pathFinder.ResetSearch();
                CURRENT_STATE = IDLE_STATE;
            }
            break;
        }
        case Enemy::ATTACK_STATE:
        {
            break;
        }
        case Enemy::DEAD_STATE:
        {
            break;
        }
        default:
        {
            break;
        }
    }
}

void BasicEnemy::Reset(){

}