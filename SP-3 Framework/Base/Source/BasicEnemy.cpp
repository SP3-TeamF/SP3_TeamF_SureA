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
}

BasicEnemy::~BasicEnemy()
{
    delete this->idleStrategy;
    delete this->chaseStrategy;
    delete this->attackStrategy;
}

void BasicEnemy::Update(double dt)
{
    Enemy::Update(dt);
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
            if (wayPoints.empty() || idleStrategy->pathFinder.m_PathUnable)
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

void BasicEnemy::Reset()
{
    CURRENT_STATE = IDLE_STATE;
    currentStrategy = idleStrategy;

    while (!wayPoints.empty())
    {
        wayPoints.pop();
    }
    
    while (!patrolPoints.empty())
    {
        patrolPoints.pop();
    }

    idleStrategy->pathFinder.ResetSearch();
    pathStartPosition = Vector3(0, 0, 0);
    pathEndPosition = Vector3(0, 0, 0);
}