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

    void ClearWaypoints();
    void AddWaypoint(Vector3 pos);
    void SetPosition(Vector3 pos);
    virtual void Update(double dt) = 0;
    void SetAttackTarget(Character* newAttackTarget);
    
protected:
    Vector3 position;
    float scanDistance;
    queue<Vector3> wayPoints;
    
};

#endif // !STRATEGY_H_
