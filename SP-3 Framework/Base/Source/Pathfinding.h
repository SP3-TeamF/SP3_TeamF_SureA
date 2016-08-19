#ifndef PATHFINDING_H_
#define PATHFINDING_H_
#include "Vector3.h"
#include "TileMap.h"
#include "GlobalDatas.h"
#include <vector>
#include "Node.h"
#include <stack>

using std::vector;
using std::stack;

class Pathfinding
{
public:
    Pathfinding();
    virtual ~Pathfinding();

    //Clear the list
    void ClearOpenList();
    void ClearVisitedList();
    void ClearShortestPath();

    //Getters
    Vector3 NextPathPos(Vector3 position);

    //Reset function
    void ResetSearch();

    //Others
    void Findpath(Vector3 startPos, Vector3 endPos);

    //Reached end goal
    bool m_FoundGoal;

    //Started the path finding
    bool m_InitialisedStartGoal;

    //Unable to find path
    bool m_PathUnable;

private:
    //Starting Node
    Node* startNode;

    //End Node
	Node* endNode;

    //List that had not been eliminated
	vector<Node*> openList;

    //List that has not been eliminated
    vector<Node*> visitedList;

    //Current shortest path
    vector<Vector3*> shortestPath;

    //Set the next start and end
    void SetStartAndEnd(Node* startNode, Node* lastNode);

    //Check if node is in open list
    void PathOpened(int x, int y, float newCost, Node* parent);

    //Gets the next node
    Node* GetNextNode();

    //Continues the search
    void ContinuePath();
};

#endif PATHFINDING_H_