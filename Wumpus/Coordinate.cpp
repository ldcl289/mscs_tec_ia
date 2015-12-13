//
// Created by lchavarr on 12/13/15.
//

#include "Coordinate.h"

const std::string Coordinate::north = "NORTH";
const std::string Coordinate::east = "EAST";
const std::string Coordinate::south = "SOUTH";
const std::string Coordinate::west = "WEST";
const std::string Coordinate::invalid = "INVALID";
int Coordinate::size = 0;

Coordinate::Coordinate(int x, int y) : x(x), y(y)
{
}

Coordinate& Coordinate::operator=(const Coordinate& a)
{
    x=a.x;
    y=a.y;
    return *this;
}
Coordinate Coordinate::operator+(const Coordinate& a) const
{
    return Coordinate(a.x+x, a.y+y);
}
bool Coordinate::operator==(const Coordinate& a) const
{
    return x == a.x && y == a.y;
}
bool Coordinate::operator<(const Coordinate& a) const
{
    return x < a.x && y < a.y;
}
bool Coordinate::isValid()
{
    return x >= 0 && y >= 0 && x < Coordinate::size && y < Coordinate::size;
}

std::string Coordinate::getReference(const Coordinate& coordinate) const
{
    std::string relativity = invalid;
    if(coordinate.x == x)
        relativity = (coordinate.y > y) ? north : south;
    if(coordinate.y == y)
        relativity = (coordinate.x > x) ? east : west;
    return relativity;
}

Coordinate::Coordinate(const Coordinate& current) : x(current.x), y(current.y)
{

}

Coordinate::Coordinate(Coordinate* current) : x(current->x), y(current->y)
{

}

Coordinate Coordinate::getNeighborhoodByReference(const std::string& reference) const
{
    Coordinate neighborhood(*this);
    if(reference == north)
        ++neighborhood.y;
    else if(reference == south)
        --neighborhood.y;
    else if(reference == east)
        ++neighborhood.x;
    else if(reference == west)
        --neighborhood.x;
    return neighborhood;
}
