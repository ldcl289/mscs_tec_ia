//
// Created by lchavarr on 12/13/15.
//

#ifndef AGENT_BASEKNOWLEDGE_H
#define AGENT_BASEKNOWLEDGE_H

#include <string>
#include <map>
#include <vector>
#include "Coordinate.h"
#include "Space.h"

typedef std::map<Coordinate*, bool> CoordinateMap;
class BaseKnowledge
{
public:
    const static std::string wumpus;
    const static std::string stink;
    const static std::string pit;
    const static std::string wind;
    const static std::string gold;
    const static std::string visited;
    const static std::string safe;
    const static std::vector<std::string> perceptions;

    BaseKnowledge(int size);
    void tell(const Space& current);
    Coordinate getProbablySafeNeighborhood(const Coordinate& current);
    Coordinate getPossiblySafeNeighborhood(const Coordinate& current);
    Coordinate getSafeNeighborhood(const Coordinate& current);
private:
    void resolve(const Coordinate& current);
    void insert(const std::string& perception, const Coordinate& location, bool value);
    bool coordinateExistsForPerception(const std::string& perception, const Coordinate& location);
    Coordinate* getCoordinatePointerForPerception(const std::string& perception, const Coordinate& location);
    bool isCoordinateVisited(const Coordinate& current);
    Coordinate getSafeNeighborhood(const Coordinate& current, bool (BaseKnowledge::*isCoordinateSafe)(const Coordinate&));
    bool isCoordinateProbablySafe(const Coordinate& current);
    bool isCoordinatePossiblySafe(const Coordinate& current);
    bool isCoordinateSafe(const Coordinate& current);
    void markAsEmpty(const Coordinate& current);

    int size_;
    std::map<std::string, CoordinateMap> bc_;

};


#endif //AGENT_BASEKNOWLEDGE_H
