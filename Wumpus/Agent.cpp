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
    bool isGameFinished = bc_.isGameOver() || bc_.isGameWon();
    if(!isGameFinished)
    {
        if(plan_.empty())
        {
            Coordinate* neighborhood = bc_.getSafe();
            if(!neighborhood->isValid())
            {
                neighborhood = bc_.getProbablySafe();
                if(!neighborhood->isValid())
                {
                    neighborhood = bc_.getPossiblySafe();
                    if(!neighborhood->isValid())
                        neighborhood = bc_.genRandomMove();
                }
            }
            buildActionPlan(currentSpace.location, neighborhood);
        }
        Action nextAction = plan_.front();
        plan_.pop();
        nextAction.isFinished_ = isGameFinished;
        return nextAction;
    }
    Action lastAction;
    lastAction.isFinished_ = isGameFinished;
    lastAction.location_ = currentSpace.location;
    return lastAction;
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
        plan_.push(Action(next, destiny, direction));
        current = next;
    }

    delete problem;
    delete strategy;
}

