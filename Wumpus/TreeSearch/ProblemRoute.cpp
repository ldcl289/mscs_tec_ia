//
// Created by lchavarr on 12/19/15.
//

#include <algorithm>
#include "ProblemRoute.h"

ProblemRoute::ProblemRoute(const Maze &maze) : size_(static_cast<int>(maze.size()))
{
    for(int i = 0 ; i < size_ ; ++i)
    {
        matrix.push_back(std::vector<Node*>());
        for (int j = 0; j < size_; ++j)
            matrix[i].push_back((maze[i][j]) ? new Node(i, j) : new Node());
    }
}

ProblemRoute::~ProblemRoute()
{
    for(int i = 0 ; i < size_ ; ++i)
        for (int j = 0; j < size_; ++j)
            delete matrix[i][j];
    matrix.clear();
}

bool ProblemRoute::isNodeEndPoint(Node *node)
{
    auto itr = std::find_if(endPoints_.begin(), endPoints_.end(), [&node] (Node* i)
    {
        return i->x == node->x && i->y == node->y;
    });
    return endPoints_.cend() != itr;
}

void ProblemRoute::addEndPoint(Node *node)
{
    endPoints_.push_back(node);
}

std::vector<Node *> ProblemRoute::getAdjacentNodes(Node *node)
{
    std::vector<Node*> nodes;
    if(node->y + 1 < size_ && matrix[node->x][node->y + 1]->isValid())
        nodes.push_back(matrix[node->x][node->y + 1]);
    if(node->y - 1 >= 0 && matrix[node->x][node->y - 1]->isValid())
        nodes.push_back(matrix[node->x][node->y - 1]);
    if(node->x + 1 < size_ && matrix[node->x + 1][node->y]->isValid())
        nodes.push_back(matrix[node->x + 1][node->y]);
    if(node->x - 1 >= 0 && matrix[node->x - 1][node->y]->isValid())
        nodes.push_back(matrix[node->x - 1][node->y]);
    return nodes;
}
