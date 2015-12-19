//
// Created by lchavarr on 12/12/15.
//

#ifndef WUMPUS_SPACE_H
#define WUMPUS_SPACE_H

#include<map>
#include "Coordinate.h"


class Space
{
public:
    std::map<std::string, bool> perceptions;
    Coordinate* location;
    Space()
    {
    }
    Space(int x = -1, int y = -1) : location(Coordinate::getCoordinate(x, y))
    {
    }
};


#endif //WUMPUS_SPACE_H
