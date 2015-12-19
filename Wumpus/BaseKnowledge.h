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
typedef std::map<std::string, bool> PerceptionMap;
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
    Coordinate* getProbablySafe();
    Coordinate* getPossiblySafe();
    Coordinate* getSafe();
    Coordinate* genRandomMove();
    Maze getMaze();
private:
    void resolve();
    void infer(const std::string& perception, const std::string& known);
    void checkCoordinateCorner(const std::string& perception, const std::string& known, int x, int y);
    void insert(const std::string &perception, Coordinate* location, bool value);
    bool coordinateExistsForPerception(const std::string &perception, Coordinate *location);

    bool isCoordinateVisited(Coordinate* current);
    Coordinate* getSafe(bool (BaseKnowledge::*isCoordinateSafe)(Coordinate*));
    Coordinate* getSafeCoordinateForReference(bool (BaseKnowledge::*isCoordinateSafe)(Coordinate*), const std::string& reference);
    bool isCoordinateProbablySafe(Coordinate* current);
    bool isCoordinatePossiblySafe(Coordinate* current);
    bool isCoordinateSafe(Coordinate* current);
    void markAsEmpty(Coordinate* current);
    void resolveNeighborhoodByReferenceWhenEmpty(Coordinate* current, const std::string &reference);
    std::set<Coordinate*> getAllCoordinatesInBc();

    int size_;
    std::map<std::string, CoordinateMap> bc_;
    std::map<Coordinate*, PerceptionMap> bcPerCoordinate_;
    Coordinate* current_;

};


#endif //AGENT_BASEKNOWLEDGE_H
