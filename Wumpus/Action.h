//
// Created by lchavarr on 12/12/15.
//

#ifndef WUMPUS_ACTION_H
#define WUMPUS_ACTION_H

#include <bits/stl_pair.h>
#include "Space.h"

class Action
{
    friend class Agent;
public:
    Action();
    Action(Coordinate coordinate);
    Action(Coordinate coordinate, std::string direction);
    bool isGameFinished() const;
    Coordinate getLocation();

private:
    Coordinate location_;
    bool isFinished_;
    std::string direction_;
};


#endif //WUMPUS_ACTION_H
