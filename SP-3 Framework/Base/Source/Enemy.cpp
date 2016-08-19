#include "Enemy.h"

Enemy::Enemy()
{
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