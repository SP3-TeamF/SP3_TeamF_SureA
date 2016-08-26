#include "Enemy.h"
#include <iostream>
using std::cout;
using std::endl;

Enemy::Enemy()
{
    currentStrategy = nullptr;

    scanRadius = 0;
    attackRadius = 0;

    pathEndPosition = Vector3(0, 0, 0);
    pathStartPosition = Vector3(0, 0, 0);

    CURRENT_STATE = IDLE_STATE;
}

Enemy::~Enemy()
{
}

void Enemy::Update(double dt)
{
    if (currentStrategy)
    {
        currentStrategy->Update(dt);
    }
}

//Getters
float Enemy::GetScanRadius()
{
    return this->scanRadius;
}

float Enemy::GetAttackRadius()
{
    return this->attackRadius;
}

Vector3 Enemy::GetPathEndPosition()
{
    return this->pathEndPosition;
}

Vector3 Enemy::GetPathStartPosition()
{
    return this->pathStartPosition;
}

//Setter
void Enemy::SetScanRadius(float scanRad)
{
    this->scanRadius = scanRad;
}

void Enemy::SetAttackRadius(float attackRad)
{
    this->attackRadius = attackRad;
}

void Enemy::SetWaypoints(queue<Vector3> queueWaypoints)
{
    this->wayPoints = queueWaypoints;
}

void Enemy::SetWaypoints(queue<Vector3*> queueWaypoints)
{
    while (!queueWaypoints.empty())
    {
        wayPoints.push(Vector3(*queueWaypoints.front()));
        queueWaypoints.pop();
    }
}

void Enemy::AddPatrolpoints(Vector3 position)
{
    this->patrolPoints.push(position);
}