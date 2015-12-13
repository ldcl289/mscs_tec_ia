//
// Created by lchavarr on 12/13/15.
//

#include "BaseKnowledge.h"
#include <algorithm>
#include <iostream>

std::string BaseKnowledge::wumpus = "WUMPUS";
std::string BaseKnowledge::stink = "STINK";
std::string BaseKnowledge::pit = "PIT";
std::string BaseKnowledge::wind = "WIND";
std::string BaseKnowledge::gold = "GOLD";
std::string BaseKnowledge::visited = "VISITED";
std::string BaseKnowledge::safe = "SAFE";
std::vector<std::string> BaseKnowledge::perceptions = {BaseKnowledge::wumpus, BaseKnowledge::stink, BaseKnowledge::pit, BaseKnowledge::wind, BaseKnowledge::gold};

BaseKnowledge::BaseKnowledge(int size) : size_(size)
{
    bc_[wumpus] = CoordinateMap();
    bc_[stink] = CoordinateMap();
    bc_[pit] = CoordinateMap();
    bc_[wind] = CoordinateMap();
    bc_[gold] = CoordinateMap();
    bc_[visited] = CoordinateMap();
    bc_[safe] = CoordinateMap();
}

void BaseKnowledge::tell(const Space& current)
{
    if(!current.perceptions.empty())
    {
        for(int i = 0 ; i < perceptions.size() ; ++i)
        {
            auto j = current.perceptions.find(perceptions[i]);
            if(current.perceptions.cend() == j)
                insert(perceptions[i], current.location, false);
            else
                insert(perceptions[i], current.location, j->second);
        }
        insert(safe, current.location, false);
    }
    insert(visited, current.location, true);
    resolve(current.location);
}

void BaseKnowledge::insert(const std::string& perception, const Coordinate& location, bool value)
{
    Coordinate* pointer = getCoordinatePointerForPerception(perception, location);
    if(nullptr == pointer)
    {
        pointer = new Coordinate(location);
    }
    bc_[perception][pointer] = value;
    std::cout<< perception << ": " << bc_[perception].size() << std::endl;
}

bool BaseKnowledge::coordinateExistsForPerception(const std::string& perception, const Coordinate& location)
{
    return getCoordinatePointerForPerception(perception, location) != nullptr;
}

bool BaseKnowledge::isCoordinateVisited(const Coordinate& current)
{
    return coordinateExistsForPerception(visited, current);
}

Coordinate BaseKnowledge::getProbablySafeNeighborhood(const Coordinate& current)
{
    return getSafeNeighborhood(current, &BaseKnowledge::isCoordinateProbablySafe);
}

Coordinate BaseKnowledge::getPossiblySafeNeighborhood(const Coordinate& current)
{
    return getSafeNeighborhood(current, &BaseKnowledge::isCoordinatePossiblySafe);
}

bool BaseKnowledge::isCoordinateProbablySafe(const Coordinate& current)
{
    return !coordinateExistsForPerception(BaseKnowledge::pit, current)
           && !coordinateExistsForPerception(BaseKnowledge::wumpus, current);
}

bool BaseKnowledge::isCoordinatePossiblySafe(const Coordinate& current)
{
    return coordinateExistsForPerception(BaseKnowledge::pit, current)
           || coordinateExistsForPerception(BaseKnowledge::wumpus, current);
}

Coordinate BaseKnowledge::getSafeNeighborhood(const Coordinate& current, bool (BaseKnowledge::*isCoordinateSafe)(const Coordinate& current))
{
    Coordinate safeCoordinate = current;
    if(--safeCoordinate.x >= 0 && !isCoordinateVisited(safeCoordinate))
    {
        if((this->*isCoordinateSafe)(safeCoordinate))
            return safeCoordinate;
    }
    safeCoordinate = current;
    if(++safeCoordinate.x < size_ && !isCoordinateVisited(safeCoordinate))
    {
        if((this->*isCoordinateSafe)(safeCoordinate))
            return safeCoordinate;
    }
    safeCoordinate = current;
    if(--safeCoordinate.y >= 0 && !isCoordinateVisited(safeCoordinate))
    {
        if((this->*isCoordinateSafe)(safeCoordinate))
            return safeCoordinate;
    }
    safeCoordinate = current;
    if(++safeCoordinate.y < size_ && !isCoordinateVisited(safeCoordinate))
    {
        if((this->*isCoordinateSafe)(safeCoordinate))
            return safeCoordinate;
    }
    safeCoordinate.x = -1;
    safeCoordinate.y = -1;
    return safeCoordinate;
}

void BaseKnowledge::resolve(const Coordinate& location)
{
    if(!coordinateExistsForPerception(wumpus, location) && !coordinateExistsForPerception(stink, location)
        && !coordinateExistsForPerception(pit, location) && !coordinateExistsForPerception(wind, location))
        markAsEmpty(location);
}

void BaseKnowledge::markAsEmpty(const Coordinate& current)
{
    insert(safe, current, true);
    Coordinate safeCoordinateWest(current);
    if(--safeCoordinateWest.x >= 0)
    {
        insert(safe, safeCoordinateWest, true);
    }
    Coordinate safeCoordinateEast(current);
    if(++safeCoordinateEast.x < size_)
    {
        insert(safe, safeCoordinateEast, true);
    }
    Coordinate safeCoordinateSouth(current);
    if(--safeCoordinateSouth.y >= 0)
    {
        insert(safe, safeCoordinateSouth, true);
    }
    Coordinate safeCoordinateNorth(current);
    if(++safeCoordinateNorth.y < size_)
    {
        insert(safe, safeCoordinateNorth, true);
    }
}

Coordinate* BaseKnowledge::getCoordinatePointerForPerception(const std::string& perception, const Coordinate& location)
{
    auto coordinate = std::find_if(bc_[perception].cbegin(), bc_[perception].cend(), [&location] (const std::pair<Coordinate*, bool>& i)
    {
        return i.first->x == location.x && i.first->y == location.y;
    });
    if(bc_[perception].cend() != coordinate)
        return coordinate->first;
    return nullptr;
}
