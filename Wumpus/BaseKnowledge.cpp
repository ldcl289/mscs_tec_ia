//
// Created by lchavarr on 12/13/15.
//

#include "BaseKnowledge.h"
#include <algorithm>
#include <iostream>

const std::string BaseKnowledge::wumpus = "WUMPUS";
const std::string BaseKnowledge::stink = "STINK";
const std::string BaseKnowledge::pit = "PIT";
const std::string BaseKnowledge::wind = "WIND";
const std::string BaseKnowledge::gold = "GOLD";
const std::string BaseKnowledge::visited = "VISITED";
const std::string BaseKnowledge::safe = "SAFE";
const std::vector<std::string> BaseKnowledge::perceptions = {BaseKnowledge::wumpus, BaseKnowledge::stink, BaseKnowledge::pit, BaseKnowledge::wind, BaseKnowledge::gold};

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
    current_ = current.location;
    const std::map<Coordinate*, bool>::iterator &itr = bc_[visited].find(current_);
    if(bc_[visited].cend() == itr || !itr->second)
    {
        if(!current.perceptions.empty())
        {
            for(int i = 0 ; i < perceptions.size() ; ++i)
            {
                auto j = current.perceptions.find(perceptions[i]);
                if(current.perceptions.cend() == j)
                    insert(perceptions[i], current_, false);
                else
                    insert(perceptions[i], current_, j->second);
            }
            insert(safe, current_, false);
        }
        insert(visited, current_, true);
        resolve();
    }
}

void BaseKnowledge::insert(const std::string &perception, Coordinate* location, bool value)
{
    bc_[perception][location] = value;
    if(bcPerCoordinate_.cend() == bcPerCoordinate_.find(location))
        bcPerCoordinate_[location] = PerceptionMap();
    bcPerCoordinate_[location][perception] = value;
}

bool BaseKnowledge::coordinateExistsForPerception(const std::string &perception, Coordinate *location)
{
    auto i = bc_.find(perception);
    if(bc_.cend() == i)
        return false;
    auto j = i->second.find(location);
    return i->second.cend() != j;
}

bool BaseKnowledge::isCoordinateVisited(Coordinate* current)
{
    return coordinateExistsForPerception(visited, current) && bc_[visited][current];
}

Coordinate* BaseKnowledge::getProbablySafe()
{
    return getSafe(&BaseKnowledge::isCoordinateProbablySafe);
}

Coordinate* BaseKnowledge::getPossiblySafe()
{
    return getSafe(&BaseKnowledge::isCoordinatePossiblySafe);
}

Coordinate* BaseKnowledge::getSafe()
{
    return getSafe(&BaseKnowledge::isCoordinateSafe);
}

bool BaseKnowledge::isCoordinateProbablySafe(Coordinate* current)
{
    bool noHasWumpus = coordinateExistsForPerception(BaseKnowledge::wumpus, current) && !bc_[wumpus][current];
    bool noHasPit = coordinateExistsForPerception(BaseKnowledge::pit, current) && !bc_[pit][current];
    return noHasPit && noHasWumpus;
}

bool BaseKnowledge::isCoordinatePossiblySafe(Coordinate* current)
{
    bool hasWumpus = coordinateExistsForPerception(BaseKnowledge::wumpus, current) && bc_[wumpus][current];
    bool hasPit = coordinateExistsForPerception(BaseKnowledge::pit, current) && bc_[pit][current];
    return !(hasPit || hasWumpus);
}

bool BaseKnowledge::isCoordinateSafe(Coordinate* current)
{
    return coordinateExistsForPerception(BaseKnowledge::safe, current) && bc_[safe][current];;
}

Coordinate* BaseKnowledge::getSafe(bool (BaseKnowledge::*isCoordinateSafe)(Coordinate*))
{
    Coordinate* safeCoordinate = getSafeCoordinateForReference(isCoordinateSafe, Coordinate::east);
    if(nullptr != safeCoordinate)
        return safeCoordinate;
    safeCoordinate = getSafeCoordinateForReference(isCoordinateSafe, Coordinate::west);
    if(nullptr != safeCoordinate)
        return safeCoordinate;
    safeCoordinate = getSafeCoordinateForReference(isCoordinateSafe, Coordinate::north);
    if(nullptr != safeCoordinate)
        return safeCoordinate;
    safeCoordinate = getSafeCoordinateForReference(isCoordinateSafe, Coordinate::south);
    if(nullptr != safeCoordinate)
        return safeCoordinate;
    std::set<Coordinate*> coordinates = getAllCoordinatesInBc();
    for(auto i = coordinates.cbegin(); i != coordinates.cend() ; ++i)
    {
        if((*i)->isValid() && !isCoordinateVisited(*i))
        {
            if((this->*isCoordinateSafe)(*i))
                return *i;
        }
    }
    return Coordinate::getInvalid();
}

Coordinate* BaseKnowledge::getSafeCoordinateForReference(bool (BaseKnowledge::*isCoordinateSafe)(Coordinate*), const std::string& reference)
{
    Coordinate* safeCoordinate = current_->getNeighborhoodByReference(reference);
    if(safeCoordinate->isValid() && !isCoordinateVisited(safeCoordinate))
    {
        if((this->*isCoordinateSafe)(safeCoordinate))
            return safeCoordinate;
    }
    return nullptr;
}

void BaseKnowledge::resolve()
{
    if((!coordinateExistsForPerception(stink, current_) || !bc_[stink][current_])
       && (!coordinateExistsForPerception(wind, current_) || !bc_[wind][current_]))
        markAsEmpty(current_);
    infer(stink, wumpus);
    infer(wind, pit);
}

void BaseKnowledge::infer(const std::string& perception, const std::string& known)
{
    if(coordinateExistsForPerception(perception, current_) && bc_[perception][current_])
    {
        checkCoordinateCorner(perception, known, 1, 1);
        checkCoordinateCorner(perception, known, 1, -1);
        checkCoordinateCorner(perception, known, -1, 1);
        checkCoordinateCorner(perception, known, -1, -1);
    }
}

void BaseKnowledge::checkCoordinateCorner(const std::string& perception, const std::string& known, int x, int y)
{
    Coordinate* corner = Coordinate::getCoordinate(current_->x + x, current_->y + y);
    if(corner->isValid() && coordinateExistsForPerception(perception, corner) && bc_[perception][corner])
    {
        Coordinate* horizontalAdjacent = Coordinate::getCoordinate(current_->x + x, current_->y);
        Coordinate* verticalAdjacent = Coordinate::getCoordinate(current_->x, current_->y + y);
        bool horizontalSafe = isCoordinateSafe(horizontalAdjacent);
        bool verticalSafe = isCoordinateSafe(verticalAdjacent);
        if (horizontalSafe ^ verticalSafe)
        {
            if(horizontalSafe)
            {
                insert(known, verticalAdjacent, true);
                insert(safe, verticalAdjacent, false);
            }
            if(verticalSafe)
            {
                insert(known, horizontalAdjacent, true);
                insert(safe, verticalAdjacent, false);
            }
        }
    }
}

void BaseKnowledge::markAsEmpty(Coordinate* current)
{
    insert(safe, current, true);
    resolveNeighborhoodByReferenceWhenEmpty(current, Coordinate::north);
    resolveNeighborhoodByReferenceWhenEmpty(current, Coordinate::south);
    resolveNeighborhoodByReferenceWhenEmpty(current, Coordinate::west);
    resolveNeighborhoodByReferenceWhenEmpty(current, Coordinate::east);
}

void BaseKnowledge::resolveNeighborhoodByReferenceWhenEmpty(Coordinate* current, const std::string &reference)
{
    Coordinate* neighborhood = current->getNeighborhoodByReference(reference);
    if(neighborhood->isValid())
    {
        insert(wumpus, neighborhood, false);
        insert(pit, neighborhood, false);
        insert(visited, neighborhood, false);
        insert(safe, neighborhood, true);
    }
}

Coordinate*  BaseKnowledge::genRandomMove()
{
    throw std::exception();
}

std::set<Coordinate* > BaseKnowledge::getAllCoordinatesInBc()
{
    std::set<Coordinate*> coordinates;
    for(auto i = bc_.cbegin() ; i != bc_.cend() ; ++i)
    {
        for(auto j = i->second.cbegin() ; j != i->second.cend() ; ++j)
        {
            coordinates.insert(j->first);
        }
    }
    return coordinates;
}

Maze BaseKnowledge::getMaze()
{
    Maze maze;
    for(int i = 0 ; i < size_ ; ++i)
    {
        maze.push_back(std::vector<bool>());
        for(int j = 0 ; j < size_ ; ++j)
            maze[i].push_back(false);
    }
    for(auto i = bc_[visited].cbegin() ; i != bc_[visited].cend() ; ++i)
        maze[i->first->x][i->first->y] = i->second;
    return maze;
}
