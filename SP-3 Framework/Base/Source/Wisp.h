#ifndef WISP_H_
#define WISP_H_

#include "Enemy.h"
#include "Patrol.h"

enum WISP_TYPE
{
    WISP_FIRE,
    WISP_WATER,
    WISP_AIR,
};

class Wisp : public Enemy
{
public:
    Wisp();
    ~Wisp();

    virtual void Update(double dt);
    virtual void Reset();
    

protected:
    Patrol* patrolStrategy;
    WISP_TYPE wispType;
};

#endif WISP_H_