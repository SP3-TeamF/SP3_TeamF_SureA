#ifndef PATROL_H_
#define PATROL_H_

#include "Strategy.h"
#include <queue>
#include "Vector3.h"
using std::queue;

class Patrol : public Strategy
{
public:
    Patrol();
    virtual ~Patrol();

    virtual void Update(double dt);

private:
    
};

#endif PATROL_H_