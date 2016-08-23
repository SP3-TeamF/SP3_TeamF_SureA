#ifndef STRATEGY_H_
#define STRATEGY_H_

#include <vector>
#include "Character.h"
#include <queue>
using std::vector;
using std::queue;

class Enemy;

class Strategy
{
public:
    Strategy();
    ~Strategy();

    virtual void Update(double dt) = 0;

    //Setter
    void SetCurrentEnemy(Enemy* currentEnemy);
    
protected:    
    Enemy* currentEnemy;
    
};

#endif // !STRATEGY_H_
