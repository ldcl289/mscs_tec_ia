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

Action::Action(Coordinate* coordinate, Coordinate* finalDestiny, std::string direction)
        : location_(coordinate), destiny_(finalDestiny), isFinished_(false), direction_(direction)
{

}

std::string Action::to_string()
{
    return "Direction=[" + direction_ + "], Coordinate=[" + location_->to_string() + "] Destiny=[" + destiny_->to_string() + "].";
}
