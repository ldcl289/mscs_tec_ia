//
// Created by lchavarr on 12/12/15.
//
#include "Agent.h"
#include "TreeSearch/AStar.h"
#include "TreeSearch/TreeSearch.h"

Agent::Agent(int size) : size_(size), bc_(size)
{
    Coordinate::size = size;
}

Action Agent::play(Space currentSpace)
{
    bc_.tell(currentSpace);
    if(plan_.empty())
    {
        Coordinate* safeNeighborhood = bc_.getSafe(currentSpace.location);
        if(safeNeighborhood->isValid())
            buildActionPlan(currentSpace.location, safeNeighborhood);
        else
        {
            safeNeighborhood = bc_.getProbablySafe(currentSpace.location);
            if(safeNeighborhood->isValid())
                buildActionPlan(currentSpace.location, safeNeighborhood);
            else
            {
                safeNeighborhood = bc_.getPossiblySafe(currentSpace.location);
                if(safeNeighborhood->isValid())
                    buildActionPlan(currentSpace.location, safeNeighborhood);
                else
                {
                    Coordinate* randomMove = bc_.genRandomMove(currentSpace.location);
                    buildActionPlan(currentSpace.location, randomMove);
                }
            }
        }
    }
    Action nextAction;
    nextAction = plan_.front();
    plan_.pop();
    return nextAction;
}


void Agent::buildActionPlan(Coordinate* current, Coordinate* destiny)
{
    Maze maze = bc_.getMaze();
    maze[destiny->x][destiny->y] = true;
    Coordinate* next;

    ProblemRoute* problem = new ProblemRoute(maze);
    problem->startPoint = problem->matrix[current->x][current->y];
    problem->addEndPoint(problem->matrix[destiny->x][destiny->y]);
    AStar* strategy = new AStar();
    TreeSearch search(problem, strategy);

    std::vector<Node*> path = search.getFinalPath();
    for(int i  = 0 ; i < path.size() ; ++i)
    {
        next = Coordinate::getCoordinate(path[i]->x, path[i]->y);
        std::string direction = current->getReference(next);
        plan_.push(Action(next, direction));
        current = next;
    }

    delete problem;
    delete strategy;
}

