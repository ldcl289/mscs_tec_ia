//
// Created by lchavarr on 12/12/15.
//

#ifndef WUMPUS_WUMPUS_H
#define WUMPUS_WUMPUS_H


#include <string>
#include <map>
#include <set>
#include <queue>
#include "Action.h"
#include "BaseKnowledge.h"


class Agent
{
public:
    Agent(int size);
    Action play(Space currentSpace);

private:
    void buildActionPlan(const Coordinate& current, const Coordinate& destiny);

    int size_;
    BaseKnowledge bc_;
    std::queue<Action> plan_;
};


#endif //WUMPUS_WUMPUS_H
