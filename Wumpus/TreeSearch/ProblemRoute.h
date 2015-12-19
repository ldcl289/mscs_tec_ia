//
// Created by lchavarr on 12/19/15.
//

#ifndef AGENT_PROBLEMROUTE_H
#define AGENT_PROBLEMROUTE_H

#include <vector>
#include "Node.h"

typedef std::vector<std::vector<bool>> Maze;
typedef std::vector<std::vector<Node*>> NodeMatrix;

class ProblemRoute
{
public:
    Node* startPoint;

    ProblemRoute(const Maze &maze);
    ~ProblemRoute();
    bool isNodeEndPoint(Node* node);
    void addEndPoint(Node* node);

    std::vector<Node*> getAdjacentNodes(Node* node);
    NodeMatrix matrix;

private:
    int size_;
    std::vector<Node*> endPoints_;
};


#endif //AGENT_PROBLEMROUTE_H
