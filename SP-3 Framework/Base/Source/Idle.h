#ifndef IDLE_H
#define IDLE_H

#include "Strategy.h"
#include "Pathfinding.h"

class Enemy;

class Idle : public Strategy
{
public:
    Idle();
    virtual ~Idle();
    virtual void Update(double dt);

    //Find a new target
    bool ScanTarget();

    //Pathfinding functions
    void FindPath();

    Pathfinding pathFinder;
private:
    

};

#endif IDLE_H