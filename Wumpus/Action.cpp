//
// Created by lchavarr on 12/12/15.
//

#include "Action.h"

Action::Action() : location_(), isFinished_(false)
{

}

bool Action::isGameFinished() const
{
    return isFinished_;
}

Coordinate Action::getLocation()
{
    return location_;
}

Action::Action(Coordinate coordinate) : location_(coordinate), isFinished_(false)
{

}
