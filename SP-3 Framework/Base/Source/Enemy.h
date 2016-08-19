#ifndef ENEMY_H_
#define ENEMY_H_

#include "Strategy.h"
#include "Character.h"

class Enemy : public Character
{
public:
    Enemy();
    ~Enemy();

    virtual void Update(double dt);

protected:
    Strategy* currentStrategy;

};

#endif // !ENEMY_H_