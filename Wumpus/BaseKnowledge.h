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
typedef enum
{
    ONGOING,
    WIN,
    OVER
} GameStatus;
class BaseKnowledge
{
public:
    const static std::string WUMPUS;
    const static std::string STINK;
    const static std::string PIT;
    const static std::string WIND;
    const static std::string GOLD;
    const static std::string VISITED;
    const static std::string SAFE;
    const static std::vector<std::string> PERCEPTIONS;

    BaseKnowledge(int size);
    void tell(const Space& current);
    Coordinate* getProbablySafe();
    Coordinate* getPossiblySafe();
    Coordinate* getSafe();
    Coordinate* genRandomMove();
    Maze getMaze();
    bool isGameOver();
    bool isGameWon();
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
    void reviewGameStatus();

    int size_;
    std::map<std::string, CoordinateMap> bc_;
    std::map<Coordinate*, PerceptionMap> bcPerCoordinate_;
    Coordinate* current_;
    GameStatus status_;

};


#endif //AGENT_BASEKNOWLEDGE_H
