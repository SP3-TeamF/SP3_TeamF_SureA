#ifndef CHASE_H_
#define CHASE_H_

#include "Strategy.h"
#include <queue>
#include "Vector3.h"
using std::queue;

class Enemy;

class Chase : public Strategy
{
public:
    Chase();
    virtual ~Chase();

    virtual void Update(double dt);

    //Setter
    void SetCurrentEnemy(Enemy& targetEnemy);

private:
    Enemy* currentEnemy;
};

#endif CHASE_H_