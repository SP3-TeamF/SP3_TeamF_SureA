#ifndef ENEMY_H_
#define ENEMY_H_

#include "Strategy.h"
#include "Character.h"
#include <queue>

using std::queue;

class Enemy : public Character
{
public:
    Enemy();
    ~Enemy();

    virtual void Update(double dt);

    //Getters
    float GetScanRadius();
    float GetAttackRadius();
    Vector3 GetPathEndPosition();
    Vector3 GetPathStartPosition();

    //Setter
    void SetScanRadius(float scanRad);
    void SetAttackRadius(float attackRad);

    void SetWaypoints(queue<Vector3> queueWaypoints);
    void SetWaypoints(queue<Vector3*> queueWaypoints);

    void AddPatrolpoints(Vector3 position);

    queue<Vector3> wayPoints;
    queue<Vector3> patrolPoints;

    virtual void Reset() = 0;

protected:
    virtual enum ENEMY_STATES
    {
        IDLE_STATE = 0,
        SCANNING_STATE,
        PATROL_STATE,
        ATTACK_STATE,
        CHASE_STATE,
        DEAD_STATE,
    };

    Strategy* currentStrategy;

    float scanRadius;
    float attackRadius;

    Vector3 pathEndPosition;
    Vector3 pathStartPosition;

    ENEMY_STATES CURRENT_STATE;
};

#endif // !ENEMY_H_