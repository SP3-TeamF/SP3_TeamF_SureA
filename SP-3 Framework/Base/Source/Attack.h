#ifndef ATTACK_H_
#define ATTACK_H_

#include "Strategy.h"

class Enemy;

class Attack : public Strategy
{
public:
    Attack();
    virtual ~Attack();

    virtual void Update(double dt);

    //Setters
    void AttackPlayer();

    //Other
    bool InAttackRadius();

private:


};

#endif ATTACK_H_;