#ifndef STRATEGY_H_
#define STRATEGY_H_

#include <vector>
#include "Player.h"
#include "Character.h"
#include <queue>
using std::vector;
using std::queue;

class Strategy
{
public:
    Strategy();
    ~Strategy();

    virtual void Update(double dt) = 0;

    void ClearWaypoints();
    void AddWaypoint(Vector3 pos);
    void SetPosition(Vector3 pos);
    
    
protected:
    Vector3 position;
    queue<Vector3*> wayPoints;
    
};

#endif // !STRATEGY_H_
