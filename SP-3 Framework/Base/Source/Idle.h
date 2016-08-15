#ifndef IDLE_H
#define IDLE_H

#include "Strategy.h"
class Idle : public Strategy
{
public:
    Idle();
    virtual ~Idle();

    virtual void Update(double dt);
private:

};

#endif IDLE_H