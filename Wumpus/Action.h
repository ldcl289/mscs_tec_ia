//
// Created by lchavarr on 12/12/15.
//

#ifndef WUMPUS_ACTION_H
#define WUMPUS_ACTION_H

#include "Space.h"

class Action
{
    friend class Agent;
public:
    Action();

    Action(Coordinate* coordinate, Coordinate* finalDestiny, std::string direction);
    bool isGameFinished() const;
    Coordinate* getLocation();

    std::string to_string();

private:
    Coordinate* location_;
    Coordinate* destiny_;
    bool isFinished_;
    std::string direction_;
};


#endif //WUMPUS_ACTION_H
