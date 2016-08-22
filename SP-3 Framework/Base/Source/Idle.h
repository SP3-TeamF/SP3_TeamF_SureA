#ifndef IDLE_H
#define IDLE_H

#include "Strategy.h"
#include "Pathfinding.h"
class Idle : public Strategy
{
public:
    Idle();
    virtual ~Idle();
    virtual void Update(double dt);

    //Sets the path for the pathfinder
    void SetPath(Vector3 targetPosition);
    void SetScanRadius(float scanRadius);

    //Find a new target
    bool ScanTarget();

    //Pathfinding functions
    void FindPath();

private:
    float scanRadius;

    Pathfinding pathFinder;

    Vector3* startPosition;
    Vector3* targetPosition; 
};

#endif IDLE_H