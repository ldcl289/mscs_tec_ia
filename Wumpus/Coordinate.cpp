//
// Created by lchavarr on 12/13/15.
//

#include "Coordinate.h"

std::string Coordinate::north = "NORTH";
std::string Coordinate::east = "EAST";
std::string Coordinate::south = "SOUTH";
std::string Coordinate::west = "WEST";
std::string Coordinate::invalid = "INVALID";

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
    return x >= 0 && y >= 0;
}

std::string Coordinate::getRelativity(const Coordinate& coordinate)
{
    std::string relativity = invalid;
    if(coordinate.x == x)
        relativity = (coordinate.y > y) ? north : south;
    if(coordinate.y == y)
        relativity = (coordinate.x > x) ? east : west;
    return relativity;
}
