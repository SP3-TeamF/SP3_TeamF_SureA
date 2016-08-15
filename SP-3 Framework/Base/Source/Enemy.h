#ifndef ENEMY_H_
#define ENEMY_H_

#include "Character.h"

class Enemy : public Character
{
public:
    Enemy();
    ~Enemy();

    virtual void Update(double dt);
};

#endif // !ENEMY_H_