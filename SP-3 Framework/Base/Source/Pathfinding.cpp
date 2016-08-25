#include "Pathfinding.h"
#include <iostream>

Pathfinding::Pathfinding()
{
    m_InitialisedStartGoal = false;
    m_FoundGoal = false;
    m_PathUnable = false;
}

Pathfinding::~Pathfinding()
{

}

//Clear the list
void Pathfinding::ClearOpenList()
{
    for (int i = 0; i < openList.size(); ++i)
    {
        delete openList[i];
    }
    openList.clear();
}

void Pathfinding::ClearVisitedList()
{
    for (int i = 0; i < visitedList.size(); ++i)
    {
        delete visitedList[i];
    }
    visitedList.clear();
}

void Pathfinding::ClearShortestPath()
{
    while (!shortestPath.empty())
    {
        Vector3* temp = shortestPath.back();
        shortestPath.pop_back();
        delete temp;
    }
}

void Pathfinding::ClearWaypoints()
{
    while (!wayPoints.empty())
    {
        wayPoints.pop();
    }
}

//Setters
void Pathfinding::SetStartAndEnd(Node* startNode, Node* lastNode)
{
    this->startNode = new Node(startNode->position, nullptr);
    this->endNode = new Node(lastNode->position, nullptr);
    
    this->startNode->gValue = 0;
    this->startNode->heuristic = this->startNode->GetManhattanDistance(endNode->position);
    this->startNode->parentNode = nullptr;
    
    openList.push_back(this->startNode);
}

//Getters
Vector3 Pathfinding::NextPathPos(Vector3 position)
{
    int nodeIndex = 1;

    Vector3 nextPos;
    nextPos.x = shortestPath[shortestPath.size() - nodeIndex]->x;
    nextPos.y = shortestPath[shortestPath.size() - nodeIndex]->y;

    Vector3 distance = nextPos - position;

    if (nodeIndex < shortestPath.size())
    {
        if (distance.LengthSquared() < 2 * 2)
        {
            shortestPath.erase(shortestPath.end() - nodeIndex);
        }
    }

    return nextPos;
}

queue<Vector3*> Pathfinding::GetWayPoints()
{
    for (int i = shortestPath.size() - 1; i >= 0; --i)
    {
        wayPoints.push(shortestPath[i]);
    }

    return wayPoints;
}

//Others
void Pathfinding::Findpath(Vector3 startPos, Vector3 endPos)
{
    startPos = Vector3((int)startPos.x, (int)startPos.y, (int)startPos.z);
    endPos = Vector3((int)endPos.x, (int)endPos.y, (int)endPos.z);

    if (!m_PathUnable)
    {
        if (m_TileMap->GetTileType(endPos.x, endPos.y) != 237)
        {
            m_PathUnable = true;
        }

        else
        {
            if (m_TileMap->GetTileType(endPos.x + 1, endPos.y) != 237 &&
                m_TileMap->GetTileType(endPos.x - 1, endPos.y) != 237 &&
                m_TileMap->GetTileType(endPos.x, endPos.y + 1) != 237 &&
                m_TileMap->GetTileType(endPos.x, endPos.y - 1) != 237
                )
            {
                m_PathUnable = true;
            }
        }

        if (!m_InitialisedStartGoal)
        {
            ClearOpenList();
            ClearVisitedList();
            ClearShortestPath();

            Node start;
            start.position = startPos;

            Node end;
            end.position = endPos;

            SetStartAndEnd(&start, &end);
            m_InitialisedStartGoal = true;
        }
        else
        {
            ContinuePath();
        }
    }
  
}

Node* Pathfinding::GetNextNode()
{
    int bestF = INT_MAX;
    int nodeIndex = -1;
    Node* nextNode = nullptr;
    for (int i = 0; i < openList.size(); ++i) 
    {
        if (openList[i]->GetF() < bestF)
        {
            bestF = openList[i]->GetF();
            nodeIndex = i;
        }
    }

    if (nodeIndex >= 0)
    {
        nextNode = openList[nodeIndex];
		bool shouldPush = true;
		for (auto test : visitedList)
		{
			if (test->nodeID == nextNode->nodeID)
			{
				shouldPush = false;
				break;
			}
		}
		if (shouldPush)
		{
			visitedList.push_back(nextNode);
		}
		else
		{
			delete nextNode;
		}
        openList.erase(openList.begin() + nodeIndex);
    }

    return nextNode;
}

void Pathfinding::PathOpened(int x, int y, float newCost, Node* parent)
{
    if (m_TileMap->GetTileType(x, y) != 237)
    {
        return;
    }

    int nodeId = y * m_TileMap->GetNumWorldTile_Width() + x;

    for (int i = 0; i < visitedList.size(); ++i)
    {
        if (nodeId == visitedList[i]->nodeID)
        {
            return;
        }
    }

    Node* newNode = new Node(Vector3(x, y), parent);
    newNode->gValue = newCost;
    newNode->heuristic = parent->GetManhattanDistance(endNode->position);

    for (int i = 0; i < openList.size(); ++i)
    {
        if (nodeId == openList[i]->nodeID)
        {
            float newF = newNode->gValue + newCost + openList[i]->heuristic;

            if (openList[i]->GetF() > newF)
            {
                openList[i]->gValue = newNode->gValue;
                openList[i]->parentNode = newNode;
            }
            else
            {
                delete newNode;
                return;
            }
        }
    }

    openList.push_back(newNode);
}

void Pathfinding::ContinuePath()
{
    for (int repeat = 0; repeat < 10; ++repeat)
    {
        if (openList.empty())
        {
            m_PathUnable = true;
            return;
        }

        Node* currentNode = GetNextNode();

        if (currentNode->nodeID == endNode->nodeID)
        {
            endNode->parentNode = currentNode->parentNode;

            Node* getPath;

            for (getPath = endNode; getPath != nullptr; getPath = getPath->parentNode)
            {
                shortestPath.push_back(new Vector3(getPath->position.x, getPath->position.y));
                m_FoundGoal = true;
            }
            return;
        }
        else
        {
            //Top 
            {
                //Left
                if (m_TileMap->GetTileType(currentNode->position.x - 1, currentNode->position.y) == 237 &&
                    m_TileMap->GetTileType(currentNode->position.x, currentNode->position.y + 1) == 237
                    )
                {
                    PathOpened(currentNode->position.x - 1, currentNode->position.y + 1, currentNode->gValue + 14, currentNode);
                }

                //Middle
                PathOpened(currentNode->position.x, currentNode->position.y + 1, currentNode->gValue + 10, currentNode);

                //Right
                if (m_TileMap->GetTileType(currentNode->position.x + 1, currentNode->position.y) == 237 &&
                    m_TileMap->GetTileType(currentNode->position.x, currentNode->position.y + 1) == 237
                    )
                {
                    PathOpened(currentNode->position.x + 1, currentNode->position.y + 1, currentNode->gValue + 14, currentNode);
                }
            }

            //Middle 
            {
                //Left
                PathOpened(currentNode->position.x - 1, currentNode->position.y, currentNode->gValue + 10, currentNode);

                //Right
                PathOpened(currentNode->position.x + 1, currentNode->position.y, currentNode->gValue + 10, currentNode);
            }

            //Bottom 
            {
                //Left
                if (m_TileMap->GetTileType(currentNode->position.x - 1, currentNode->position.y) == 237 &&
                    m_TileMap->GetTileType(currentNode->position.x, currentNode->position.y - 1) == 237
                    )
                {
                    PathOpened(currentNode->position.x - 1, currentNode->position.y - 1, currentNode->gValue + 14, currentNode);
                }
              
                //Middle
                PathOpened(currentNode->position.x, currentNode->position.y - 1, currentNode->gValue + 10, currentNode);

                //Right
                if (m_TileMap->GetTileType(currentNode->position.x + 1, currentNode->position.y) == 237 &&
                    m_TileMap->GetTileType(currentNode->position.x, currentNode->position.y - 1) == 237
                    )
                {
                    PathOpened(currentNode->position.x + 1, currentNode->position.y - 1, currentNode->gValue + 14, currentNode);
                }
            }

            for (int i = 0; i < openList.size(); ++i)
            {
                if (currentNode->nodeID == openList[i]->nodeID)
                {
                    openList.erase(openList.begin() + i);
                }
            }
        }
    }
}

void Pathfinding::ResetSearch()
{
    ClearOpenList();
    ClearVisitedList();
    ClearShortestPath();
    ClearWaypoints();
    m_InitialisedStartGoal = false;
    m_FoundGoal = false;
    m_PathUnable = false;
}
