#include "Node.h"
#include "MyMath.h"
#include "GlobalDatas.h"

Node::Node(Vector3 pos, Node* parent)
{
    this->position = pos;
    this->parentNode = parent;
    this->nodeID = pos.y * m_TileMap->GetNumScreenTile_Width() +  pos.x;
    this->gValue = 0;
    this->heuristic = 0;
}

Node::~Node()
{
}

//Getter
int Node::GetF()
{
    return this->gValue + this->heuristic;
}

int Node::GetManhattanDistance(Vector3 endPos)
{
    return (
        (abs(endPos.x - this->position.x) +
        abs(endPos.y - this->position.y))
		* 10
        );
}
