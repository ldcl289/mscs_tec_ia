//
// Created by lchavarr on 12/13/15.
//

#include "BaseKnowledge.h"
#include <algorithm>
#include <iostream>

const std::string BaseKnowledge::WUMPUS = "WUMPUS";
const std::string BaseKnowledge::STINK = "STINK";
const std::string BaseKnowledge::PIT = "PIT";
const std::string BaseKnowledge::WIND = "WIND";
const std::string BaseKnowledge::GOLD = "GOLD";
const std::string BaseKnowledge::VISITED = "VISITED";
const std::string BaseKnowledge::SAFE = "SAFE";
const std::vector<std::string> BaseKnowledge::PERCEPTIONS = {BaseKnowledge::WUMPUS, BaseKnowledge::STINK, BaseKnowledge::PIT, BaseKnowledge::WIND, BaseKnowledge::GOLD};

BaseKnowledge::BaseKnowledge(int size) : size_(size), status_(ONGOING)
{
    bc_[WUMPUS] = CoordinateMap();
    bc_[STINK] = CoordinateMap();
    bc_[PIT] = CoordinateMap();
    bc_[WIND] = CoordinateMap();
    bc_[GOLD] = CoordinateMap();
    bc_[VISITED] = CoordinateMap();
    bc_[SAFE] = CoordinateMap();
}

void BaseKnowledge::tell(const Space& current)
{
    current_ = current.location;
    const std::map<Coordinate*, bool>::iterator &itr = bc_[VISITED].find(current_);
    if(bc_[VISITED].cend() == itr || !itr->second)
    {
        if (!current.perceptions.empty())
        {
            for (int i = 0; i < PERCEPTIONS.size(); ++i)
            {
                auto j = current.perceptions.find(PERCEPTIONS[i]);
                if (current.perceptions.cend() == j)
                    insert(PERCEPTIONS[i], current_, false);
                else
                    insert(PERCEPTIONS[i], current_, j->second);
            }
            insert(SAFE, current_, false);
        }
        insert(VISITED, current_, true);
        resolve();
    }
    reviewGameStatus();
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
    return coordinateExistsForPerception(VISITED, current) && bc_[VISITED][current];
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
    bool noHasWumpus = coordinateExistsForPerception(BaseKnowledge::WUMPUS, current) && !bc_[WUMPUS][current];
    bool noHasPit = coordinateExistsForPerception(BaseKnowledge::PIT, current) && !bc_[PIT][current];
    return noHasPit && noHasWumpus;
}

bool BaseKnowledge::isCoordinatePossiblySafe(Coordinate* current)
{
    bool hasWumpus = coordinateExistsForPerception(BaseKnowledge::WUMPUS, current) && bc_[WUMPUS][current];
    bool hasPit = coordinateExistsForPerception(BaseKnowledge::PIT, current) && bc_[PIT][current];
    return !(hasPit || hasWumpus);
}

bool BaseKnowledge::isCoordinateSafe(Coordinate* current)
{
    return coordinateExistsForPerception(BaseKnowledge::SAFE, current) && bc_[SAFE][current];;
}

Coordinate* BaseKnowledge::getSafe(bool (BaseKnowledge::*isCoordinateSafe)(Coordinate*))
{
    Coordinate* safeCoordinate = getSafeCoordinateForReference(isCoordinateSafe, Coordinate::EAST);
    if(nullptr != safeCoordinate)
        return safeCoordinate;
    safeCoordinate = getSafeCoordinateForReference(isCoordinateSafe, Coordinate::WEST);
    if(nullptr != safeCoordinate)
        return safeCoordinate;
    safeCoordinate = getSafeCoordinateForReference(isCoordinateSafe, Coordinate::NORTH);
    if(nullptr != safeCoordinate)
        return safeCoordinate;
    safeCoordinate = getSafeCoordinateForReference(isCoordinateSafe, Coordinate::SOUTH);
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
    if(( !coordinateExistsForPerception(STINK, current_) || !bc_[STINK][current_])
       && ( !coordinateExistsForPerception(WIND, current_) || !bc_[WIND][current_]))
        markAsEmpty(current_);
    infer(STINK, WUMPUS);
    infer(WIND, PIT);
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
                insert(SAFE, verticalAdjacent, false);
            }
            if(verticalSafe)
            {
                insert(known, horizontalAdjacent, true);
                insert(SAFE, verticalAdjacent, false);
            }
        }
    }
}

void BaseKnowledge::markAsEmpty(Coordinate* current)
{
    insert(SAFE, current, true);
    resolveNeighborhoodByReferenceWhenEmpty(current, Coordinate::NORTH);
    resolveNeighborhoodByReferenceWhenEmpty(current, Coordinate::SOUTH);
    resolveNeighborhoodByReferenceWhenEmpty(current, Coordinate::WEST);
    resolveNeighborhoodByReferenceWhenEmpty(current, Coordinate::EAST);
}

void BaseKnowledge::resolveNeighborhoodByReferenceWhenEmpty(Coordinate* current, const std::string &reference)
{
    Coordinate* neighborhood = current->getNeighborhoodByReference(reference);
    if(neighborhood->isValid())
    {
        insert(WUMPUS, neighborhood, false);
        insert(PIT, neighborhood, false);
        insert(VISITED, neighborhood, false);
        insert(SAFE, neighborhood, true);
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
    for(auto i = bc_[VISITED].cbegin() ; i != bc_[VISITED].cend() ; ++i)
        maze[i->first->x][i->first->y] = i->second;
    return maze;
}

void BaseKnowledge::reviewGameStatus()
{
    bool diedByWumpus = coordinateExistsForPerception(WUMPUS, current_) && bc_[WUMPUS][current_];
    bool diedByPit = coordinateExistsForPerception(PIT, current_) && bc_[PIT][current_];
    if(diedByPit || diedByWumpus)
        status_ = OVER;
    else
    {
        bool won = coordinateExistsForPerception(GOLD, current_) && bc_[GOLD][current_];
        if(won)
            status_ = WIN;
    }
}

bool BaseKnowledge::isGameOver()
{
    return status_ == OVER;
}

bool BaseKnowledge::isGameWon()
{
    return status_ == WIN;
}
