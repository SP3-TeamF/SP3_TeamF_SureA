#ifndef BASIC_ENEMY_H_
#define BASIC_ENEMY_H_

#include "Enemy.h"

class BasicEnemy :public Enemy
{
public:
    BasicEnemy();
    virtual ~BasicEnemy();
    virtual void Update(double dt);
private:
};

#endif BASIC_ENEMY_H_