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

Coordinate* Action::getLocation()
{
    return location_;
}

Action::Action(Coordinate* coordinate) : location_(coordinate), isFinished_(false)
{

}

Action::Action(Coordinate* coordinate, std::string direction) : location_(coordinate), isFinished_(false), direction_(direction)
{

}

std::string Action::to_string()
{
    return "Direction=[" + direction_ + "], Coordinate=[" + location_->to_string() + "].";

}
