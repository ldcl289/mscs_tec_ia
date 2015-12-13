//
// Created by lchavarr on 12/12/15.
//
#include "Agent.h"

Agent::Agent(int size) : size_(size), bc_(size)
{

}

Action Agent::play(Space currentSpace)
{
    bc_.tell(currentSpace);
    if(!plan_.empty())
    {
        Action nextAction;
        nextAction = plan_.front();
        plan_.pop();
        return nextAction;
    }

    Coordinate safeNeighborhood = bc_.getProbablySafeNeighborhood(currentSpace.location);
    if(safeNeighborhood.isValid())
    {
        buildActionPlan(currentSpace.location, safeNeighborhood);
    }
    safeNeighborhood = bc_.getPossiblySafeNeighborhood(currentSpace.location);
    if(!safeNeighborhood.isValid())
    {

    }
    Action nextAction;
    return nextAction;
}


void Agent::buildActionPlan(const Coordinate& current, const Coordinate& destiny)
{

}
