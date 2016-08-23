#ifndef BASIC_ENEMY_H_
#define BASIC_ENEMY_H_

#include "Idle.h"
#include "Enemy.h"
#include "Chase.h"
#include "Attack.h"

class BasicEnemy :public Enemy
{
public:
    BasicEnemy();
    virtual ~BasicEnemy();
    virtual void Update(double dt);

private:   
    Idle* idleStrategy;
    Chase* chaseStrategy;
    Attack* attackStrategy;
};

#endif BASIC_ENEMY_H_