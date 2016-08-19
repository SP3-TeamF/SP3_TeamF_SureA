#ifndef NODE_H_
#define NODE_H_
#include <vector>
#include "TileMap.h"
#include "MyMath.h"
#include "Vector3.h"

using std::vector;

struct Node
{
public:
    Node(Vector3 pos = Vector3(0, 0), Node* parent = nullptr);
    virtual ~Node();

    //Getter
    int GetF();
    int GetManhattanDistance(Vector3 endPos);

    //Position
    Vector3 position;

    //Distance Variables
    int gValue;
    int heuristic;
    int nodeID;

    Node* parentNode;
};

#endif NODE_H_