//
// Created by lchavarr on 12/13/15.
//

#ifndef AGENT_BASEKNOWLEDGE_H
#define AGENT_BASEKNOWLEDGE_H

#include <string>
#include <map>
#include <set>
#include <vector>
#include "Coordinate.h"
#include "Space.h"
#include "TreeSearch/ProblemRoute.h"

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
    Coordinate* getProbablySafe(Coordinate* current);
    Coordinate* getPossiblySafe(Coordinate* current);
    Coordinate* getSafe(Coordinate* current);
    Coordinate* genRandomMove(Coordinate* current);
    Maze getMaze();
private:
    void resolve(Coordinate* current);
    void insert(const std::string &perception, Coordinate* location, bool value);
    bool coordinateExistsForPerception(const std::string &perception, Coordinate *location);

    bool isCoordinateVisited(Coordinate* current);
    Coordinate* getSafe(Coordinate* current, bool (BaseKnowledge::*isCoordinateSafe)(Coordinate* ));
    Coordinate* getSafeCoordinateForReference(const Coordinate *current,
                                              bool (BaseKnowledge::*isCoordinateSafe)(Coordinate* ),
                                              const std::string &reference);
    bool isCoordinateProbablySafe(Coordinate* current);
    bool isCoordinatePossiblySafe(Coordinate* current);
    bool isCoordinateSafe(Coordinate* current);
    void markAsEmpty(Coordinate* current);
    void resolveNeighborhoodByReferenceWhenEmpty(Coordinate* current, const std::string &reference);
    std::set<Coordinate*> getAllCoordinatesInBc();

    int size_;
    std::map<std::string, CoordinateMap> bc_;

};


#endif //AGENT_BASEKNOWLEDGE_H
