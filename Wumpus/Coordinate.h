//
// Created by lchavarr on 12/13/15.
//

#ifndef WUMPUS_COORDINATE_H
#define WUMPUS_COORDINATE_H

#include <string>
#include <vector>

class Coordinate
{
public:
    const static std::string north;
    const static std::string east;
    const static std::string south;
    const static std::string west;
    const static std::string invalid;
    static int size;

    static Coordinate* getCoordinate(int x, int y);
    static Coordinate* getInvalid();

    Coordinate(int x = -1, int y = -1);
    bool operator==(const Coordinate& a) const;
    bool operator<(const Coordinate& a) const;
    bool isValid();
    std::string getReference(Coordinate* coordinate) const;
    Coordinate* getNeighborhoodByReference(const std::string &reference) const;
    std::string to_string();

    int x;
    int y;
private:
    static std::vector<Coordinate*> coordinates_;
};

#endif //WUMPUS_COORDINATE_H
