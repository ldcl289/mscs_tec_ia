//
// Created by lchavarr on 12/13/15.
//

#include <algorithm>
#include "Coordinate.h"

const std::string Coordinate::north = "NORTH";
const std::string Coordinate::east = "EAST";
const std::string Coordinate::south = "SOUTH";
const std::string Coordinate::west = "WEST";
const std::string Coordinate::invalid = "INVALID";
int Coordinate::size = 0;
std::vector<Coordinate*> Coordinate::coordinates_;

Coordinate::Coordinate(int x, int y) : x(x), y(y)
{
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

std::string Coordinate::getReference(Coordinate* coordinate) const
{
    std::string relativity = invalid;
    if(coordinate->x == x)
        relativity = (coordinate->y > y) ? north : south;
    if(coordinate->y == y)
        relativity = (coordinate->x > x) ? east : west;
    return relativity;
}

Coordinate* Coordinate::getNeighborhoodByReference(const std::string &reference) const
{
    Coordinate* neighborhood = getCoordinate(-1, -1);;
    if(reference == north)
        neighborhood = getCoordinate(x, y + 1);
    else if(reference == south)
        neighborhood = getCoordinate(x, y - 1);
    else if(reference == east)
        neighborhood = getCoordinate(x + 1, y);
    else if(reference == west)
        neighborhood = getCoordinate(x - 1, y);
    return neighborhood;
}

std::string Coordinate::to_string() {
    return "[" + std::to_string(x) + ", " + std::to_string(y) + "]";
}

Coordinate* Coordinate::getCoordinate(int x, int y)
{
    auto coordinate = std::find_if(coordinates_.begin(), coordinates_.end(), [&x, &y] (Coordinate* i)
    {
        return i->x == x && i->y == y;
    });
    if(coordinates_.end() != coordinate)
        return *coordinate;
    coordinates_.push_back(new Coordinate(x, y));
    return coordinates_.back();
}

Coordinate* Coordinate::getInvalid()
{
    return getCoordinate(-1, -1);
}
