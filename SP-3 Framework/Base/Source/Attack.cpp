#include "Attack.h"
#include "Player.h"
#include "Enemy.h"


Attack::Attack()
{
}

Attack::~Attack()
{
}

void Attack::Update(double dt)
{

}

bool Attack::InAttackRadius()
{
    float distanceSquared = (player->Get_cPosition() - currentEnemy->Get_cPosition()).LengthSquared();

    if (distanceSquared < currentEnemy->GetAttackRadius() *currentEnemy->GetAttackRadius())
    {
        return true;
    }

    return false;
}

void Attack::AttackPlayer()
{

}
