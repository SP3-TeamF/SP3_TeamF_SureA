#ifndef AABB_H
#define AABB_H

#include "Vector3.h"
#include <vector>

using std::vector;

class AABB
{
public:
    enum HITBOX_TYPE
    {
        HB_BOX,
        HB_CIRCLE,
        HB_TOTAL
    };

    float width;
    float height;
    float radius;
    Vector3 position;
    HITBOX_TYPE HITBOX_TYPE;

	AABB();
    AABB(Vector3 pos, float radius);
    AABB(Vector3 pos, float width, float height);
	
	~AABB();

    void SetPosition(Vector3 pos);
    void Set(Vector3 pos, float radius);
    void Set(Vector3 pos, float width, float height);

    bool BOXtoBOX(const AABB& other);
    bool AABBtoAABB(const AABB& other);
    bool BOXtoCIRCLE(const AABB& other);
    bool CIRCLEtoCIRCLE(const AABB& other);
    bool CIRCLEtoPOINT(Vector3 point);

    bool PointToAABB(Vector3 position);
    bool PointToAABB(const AABB& other);
	
	

};

#endif