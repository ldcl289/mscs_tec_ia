//
// Created by lchavarr on 12/19/15.
//

#ifndef AGENT_ASTAR_H
#define AGENT_ASTAR_H

#include <queue>
#include <set>
#include <string>
#include "Tree.h"

class AStar
{
public:
    AStar();
    ~AStar();
    Tree* get(Tree* current);
private:
    std::priority_queue<Tree*, std::vector<Tree*>, TreeComparator> queue_;
    std::set<std::string> visited_;
};


#endif //AGENT_ASTAR_H
